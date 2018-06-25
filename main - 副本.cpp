#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <QtnRibbonStyle.h>

#include <osg/Notify>
#include <osg/Version>
#include <osgEarth/ImageUtils>
#include <osgEarth/MapNode>
#include <osgEarth/Registry>
#include <osgEarthAnnotation/AnnotationData>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthAnnotation/TrackNode>
#include <osgEarthQt/ViewerWidget>
#include <osgEarthQt/LayerManagerWidget>
#include <osgEarthQt/MapCatalogWidget>
#include <osgEarthQt/DataManager>
#include <osgEarthQt/AnnotationListWidget>
#include <osgEarthQt/LOSControlWidget>
#include <osgEarthQt/TerrainProfileWidget>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/Ocean>
#include <osgViewer/CompositeViewer>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/MultiTouchTrackballManipulator>

#include <osgGA/StateSetManipulator>

#include <DemoMainWindow>
#include <ModelLayerReader.h>

#include <gdal_priv.h>
#include <gdalwarper.h>
#include <ogr_spatialref.h>

#include "TargetDataReader.h"
#include "EagleEyeEarthManipulator.h"
#include "KeyPressEater.h"
#include "ViewPointSyn.h"
#include "MouseMoveFilter.h"
#include "CompositeViewerWidget.h"

using namespace osgEarth::Util;

#define TRACK_ICON_URL    "../data/m2525_air.png"
#define TRACK_ICON_SIZE   24
#define TRACK_FIELD_NAME  "name"



osg::ref_ptr<osg::Group> s_annoGroup;
osgEarth::Util::SkyNode* s_sky = 0L;
static osgEarth::Util::OceanNode* s_ocean = 0L;

osgViewer::Viewer* g_viewerEagleEye = NULL;
osgViewer::Viewer* g_viewerMain = NULL;
osgEarth::QtGui::DataManager* g_DataManager = NULL;



/**
* Event handler that processes events fired from the
* AnnotationEventCallback
*/
struct MyAnnoEventHandler : public osgEarth::Util::AnnotationEventHandler
{
	MyAnnoEventHandler(osgEarth::QtGui::DataManager* manager) : _manager(manager) {}

	void onClick(osgEarth::Annotation::AnnotationNode* node, const osgEarth::Util::AnnotationEventHandler::EventArgs& details)
	{
		if (_manager.valid() && details.buttons == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			if (details.modkeys & osgGA::GUIEventAdapter::MODKEY_CTRL)
			{
				if (_manager->isSelected(node))
					_manager->removeSelectedAnnotation(node);
				else
					_manager->addSelectedAnnotation(node);
			}
			else
			{
				_manager->clearSelectedAnnotations();
				_manager->addSelectedAnnotation(node);
			}
		}
	}


	osg::ref_ptr<osgEarth::QtGui::DataManager> _manager;
};

//------------------------------------------------------------------
// Methods for demo track simulation

struct TrackSim : public osg::Referenced
{
	TrackSim(TrackNode* track, const osg::Vec3d& center, float radius, double time, osgEarth::MapNode* mapNode)
	: _track(track), _mapNode(mapNode), _radius(radius), _time(time)
	{
		//Get the center point in geocentric
		GeoPoint centerMap(mapNode->getMapSRS(), center, ALTMODE_ABSOLUTE);
		centerMap.toWorld(_center, mapNode->getTerrain());
		//mapNode->getMap()->toWorldPoint( centerMap, _center );

		_up = _center;
		_up.normalize();

		//Get the "side" vector
		_side = _up ^ osg::Vec3d(0, 0, 1);
	}

	void update(double time)
	{
		double angle = (time / _time);
		angle = (angle - (int)angle) * osg::PI * 2.0;

		osg::Quat quat(angle, _up);
		osg::Vec3d spoke = quat * (_side * _radius);
		osg::Vec3d end = _center + spoke;

		GeoPoint mapPos;
		mapPos.fromWorld(_mapNode->getMapSRS(), end);
		//_mapNode->getMap()->worldPointToMapPoint(end, mapPos);

		_track->setPosition(mapPos);
	}

	TrackNode* _track;
	osgEarth::MapNode* _mapNode;
	osg::Vec3d _center, _side, _up;
	float _radius;
	double _time;
};
typedef std::vector< osg::ref_ptr<TrackSim> > TrackSimVector;

/** Update operation that runs the simulators. */
struct TrackSimUpdate : public osg::Operation
{
	TrackSimUpdate(TrackSimVector& sims) : osg::Operation("tracksim", true), _sims(sims) { }

	void operator()(osg::Object* obj)
	{
		osg::View* view = dynamic_cast<osg::View*>(obj);
		double t = view->getFrameStamp()->getSimulationTime();

		for (TrackSimVector::iterator i = _sims.begin(); i != _sims.end(); ++i)
			i->get()->update(t);
	}

	TrackSimVector& _sims;
};

TrackNode* createTrack(TrackNodeFieldSchema& schema, osg::Image* image, const std::string& name, MapNode* mapNode, const osg::Vec3d& center, double radius, double time, TrackSimVector& trackSims)
{
	TrackNode* track = new TrackNode(mapNode, GeoPoint(mapNode->getMapSRS(), center, ALTMODE_ABSOLUTE), image, schema);
	track->setFieldValue(TRACK_FIELD_NAME, name);

	AnnotationData* data = new AnnotationData();
	data->setName(name);
	data->setViewpoint(osgEarth::Viewpoint(0L, center.x(), center.y(), center.z(), 0.0, -90.0, 1e5));
	track->setAnnotationData(data);

	trackSims.push_back(new TrackSim(track, center, radius, time, mapNode));

	return track;
}

void createTrackSchema(TrackNodeFieldSchema& schema)
{
	// draw the track name above the icon:
	TextSymbol* nameSymbol = new TextSymbol();
	nameSymbol->pixelOffset()->set(0, 2 + TRACK_ICON_SIZE / 2);
	nameSymbol->alignment() = TextSymbol::ALIGN_CENTER_BOTTOM;
	nameSymbol->halo()->color() = Color::Black;
	schema[TRACK_FIELD_NAME] = TrackNodeField(nameSymbol, false);
}

osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setStyle(new Qtitan::RibbonStyle());
	a.setApplicationName("QtitanRibbon Office Sample");
	a.setOrganizationName("Developer Machines");

	QString strResPath = QApplication::applicationFilePath();
	strResPath = QFileInfo(strResPath).absolutePath();
	strResPath += "/data/";

	strResPath += "base.earth";
	QByteArray arrayTemp = strResPath.toUtf8();
	char* pPath = arrayTemp.data();
	int nSize = strlen(pPath);

	int nArgC = 2;
	char** pArg = new char*[nArgC];
	pArg[0] = "abc.exe";
	pArg[1] = new char[nSize + 1];
	memcpy(pArg[1], pPath, nSize);
	pArg[1][nSize] = 0;

	osg::ArgumentParser arguments(&nArgC, pArg);
	osg::DisplaySettings::instance()->setMinimumNumStencilBits(8);

	bool on_demand = arguments.read("--run-on-demand");

	bool trackData = arguments.read("--tracks");

	// load the .earth file from the command line.
	osg::Node* earthNode = osgDB::readNodeFiles(arguments);
	if (!earthNode)
		return 0;

	osg::Group* root = new osg::Group();
	root->addChild(earthNode);

	s_annoGroup = new osg::Group();
	root->addChild(s_annoGroup);

#ifdef Q_WS_X11
	XInitThreads();
#endif

	osg::ref_ptr<osgEarth::MapNode> mapNode = osgEarth::MapNode::findMapNode(earthNode);
	osg::ref_ptr<osgEarth::QtGui::DataManager> dataManager = new osgEarth::QtGui::DataManager(mapNode.get());
	g_DataManager = dataManager.get();
	/*DemoMainWindow*/MainWindow appWin(dataManager.get(), mapNode.get(), s_annoGroup);

	// install an event handler for picking and selection
	AnnotationEventCallback* cb = new AnnotationEventCallback();
	cb->addHandler(new MyAnnoEventHandler(dataManager.get()));
	s_annoGroup->addEventCallback(cb);

	osgEarth::QtGui::ViewVector views;
	osg::ref_ptr<osgViewer::ViewerBase> viewer;

	osgEarth::QtGui::ViewerWidget* viewerWidget = 0L;
	QVector<osgEarth::QtGui::ViewerWidget*> vecViewer;

	if (0)
	{
		for (int j = 0; j < 5; j++)
		{
			osgViewer::Viewer* v = new osgViewer::Viewer();

			if (0/*j == 0*/)
			{
				osg::ref_ptr<osgEarth::MapNode> mapNode = new osgEarth::MapNode();

				QString strFilePath = QApplication::applicationFilePath();
				strFilePath = QFileInfo(strFilePath).absolutePath();

				QString fileName = "C:/OSG_OSGEarth/gwaldron-osgearth-2.7-0-g25ce0e1/bin/Debug/data/GLOBE_1km_dem.tif";

				osgEarth::Drivers::GDALOptions layerOpt;
				layerOpt.url() = osgEarth::URI(fileName.toUtf8().data());
				osg::ref_ptr<osgEarth::ImageLayer> ptrImageLayer = new osgEarth::ImageLayer("ttttest", layerOpt);

				if (ptrImageLayer == NULL)
					return 0;

				mapNode->getMap()->addImageLayer(ptrImageLayer.get());

				v->setSceneData(mapNode);
			}
			else
			{
				v->setSceneData(root);
			}
			
			v->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
			v->setCameraManipulator(new osgEarth::Util::EarthManipulator());
			osgEarth::QtGui::ViewerWidget* viewerWidgetTemp = new osgEarth::QtGui::ViewerWidget(v);

			KeyPressEater* pEventFilter = new KeyPressEater();
			viewerWidgetTemp->installEventFilter(pEventFilter);

			QObject::connect(pEventFilter, SIGNAL(sigEscPressed()), &appWin, SLOT(slotEscPressed()));

#if OSG_MIN_VERSION_REQUIRED(3,3,2)
			// Enable touch events on the viewer
			viewerWidgetTemp->getGraphicsWindow()->setTouchEventsEnabled(true);
#endif
			osgEarth::QtGui::ViewVector viewsTemp;
			viewerWidgetTemp->getViews(viewsTemp);
			for (osgEarth::QtGui::ViewVector::iterator i = viewsTemp.begin(); i != viewsTemp.end(); ++i)
			{
				i->get()->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));
				views.push_back(*i);
			}

			vecViewer.push_back(viewerWidgetTemp);
		}

		viewerWidget = vecViewer[0];

		CompositeViewerWidget* pCompositeViewerWidget = new CompositeViewerWidget(vecViewer);

		{
			osgEarth::QtGui::ViewVector views;
			vecViewer[4]->getViews(views);
			pCompositeViewerWidget->addView(views[0]);
		}


		//QWidget* pWidgetEagleEye = vecViewer[4];
		QWidget* pWidgetEagleEye = pCompositeViewerWidget->addViewWidget(createGraphicsWindow(900, 100, 320, 240, "Popup window", true), osgDB::readNodeFile("dumptruck.osgt"));
//		pWidgetEagleEye->show();
		QDockWidget* pDockWidgetEagelEye = new QDockWidget(QString::fromLocal8Bit("”•—€Õº"));
		pDockWidgetEagelEye->setWidget(pWidgetEagleEye);

		if (0)
		{
			osgViewer::Viewer* v = new osgViewer::Viewer();
			v->setSceneData(root);
			v->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
			v->setCameraManipulator(new osgEarth::Util::EarthManipulator());
			osgEarth::QtGui::ViewerWidget* viewerWidgetEagle = new osgEarth::QtGui::ViewerWidget(v);

			KeyPressEater* pEventFilter = new KeyPressEater();
			viewerWidgetEagle->installEventFilter(pEventFilter);

			QObject::connect(pEventFilter, SIGNAL(sigEscPressed()), &appWin, SLOT(slotEscPressed()));

#if OSG_MIN_VERSION_REQUIRED(3,3,2)
			// Enable touch events on the viewer
			viewerWidgetEagle->getGraphicsWindow()->setTouchEventsEnabled(true);
#endif

			osgEarth::QtGui::ViewVector viewsTemp;
			viewerWidgetEagle->getViews(viewsTemp);
			for (osgEarth::QtGui::ViewVector::iterator i = viewsTemp.begin(); i != viewsTemp.end(); ++i)
			{
				i->get()->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));
			}

			pCompositeViewerWidget->addView(viewsTemp[0]);
			views.push_back(viewsTemp[0]);
			viewerWidgetEagle->show();
			//vecViewer.push_back(viewerWidget);
		}

		appWin.setCentralWidget(pCompositeViewerWidget);
		appWin.setViewerWidget(viewerWidget);
		appWin.addDockWidget(Qt::RightDockWidgetArea, pDockWidgetEagelEye);
	}
	else
	{
		g_viewerMain = new osgViewer::Viewer();
		g_viewerMain->setSceneData(root);
		g_viewerMain->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
		g_viewerMain->setCameraManipulator(new osgEarth::Util::EarthManipulator());
		viewerWidget = new osgEarth::QtGui::ViewerWidget(g_viewerMain);

		KeyPressEater* pEventFilter = new KeyPressEater();
		viewerWidget->installEventFilter(pEventFilter);

		QObject::connect(pEventFilter, SIGNAL(sigEscPressed()), &appWin, SLOT(slotEscPressed()));

#if OSG_MIN_VERSION_REQUIRED(3,3,2)
		// Enable touch events on the viewer
		viewerWidget->getGraphicsWindow()->setTouchEventsEnabled(true);
#endif
		osgEarth::QtGui::ViewVector viewsTemp;
		viewerWidget->getViews(viewsTemp);
		for (osgEarth::QtGui::ViewVector::iterator i = viewsTemp.begin(); i != viewsTemp.end(); ++i)
		{
			i->get()->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));
			views.push_back(*i);
		}

		viewerWidget->setMinimumWidth(100);
		viewerWidget->setMinimumHeight(100);

		appWin.setCentralWidget(viewerWidget);
		appWin.setViewerWidget(viewerWidget);

		//”•—€Õº
		{
			osg::ref_ptr<osgEarth::MapNode> mapNodeEagleEye = new osgEarth::MapNode();

			QString strFilePath = QApplication::applicationFilePath();
			strFilePath = QFileInfo(strFilePath).absolutePath();

			QString fileName = strFilePath + "/Data/World.tif";

			osgEarth::Drivers::GDALOptions layerOpt;
			layerOpt.url() = osgEarth::URI(fileName.toUtf8().data());
			osg::ref_ptr<osgEarth::ImageLayer> ptrImageLayer = new osgEarth::ImageLayer("eagle eye", layerOpt);

			if (ptrImageLayer == NULL)
				return 0;

			mapNodeEagleEye->getMap()->addImageLayer(ptrImageLayer.get());

			g_viewerEagleEye = new osgViewer::Viewer();
			g_viewerEagleEye->setSceneData(mapNodeEagleEye);
			g_viewerEagleEye->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
			g_viewerEagleEye->setCameraManipulator(new EagleEyeEarthManipulator());

			osgEarth::QtGui::ViewerWidget* viewerWidgetTemp = new osgEarth::QtGui::ViewerWidget(g_viewerEagleEye);
			viewerWidgetTemp->getGraphicsWindow()->setTouchEventsEnabled(true);

			MouseMoveFilter* pEventFilter = new MouseMoveFilter();
			viewerWidgetTemp->installEventFilter(pEventFilter);

			ViewPointSyn* pSyn = new ViewPointSyn;
			QTimer* pSynTimer = new QTimer(&appWin);
			QObject::connect(pSynTimer, SIGNAL(timeout()), pSyn, SLOT(slotDoSyn()));
			pSynTimer->start(100);

// 			osgEarth::QtGui::ViewVector viewsTemp;
// 			viewerWidgetTemp->getViews(viewsTemp);
// 			for (osgEarth::QtGui::ViewVector::iterator i = viewsTemp.begin(); i != viewsTemp.end(); ++i)
// 			{
// 				i->get()->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNodeEagleEye));
// 				views.push_back(*i);
// 			}

			QDockWidget* pDockWidgetEagelEye = new QDockWidget(QString::fromLocal8Bit("”•—€Õº"));
			pDockWidgetEagelEye->setWidget(viewerWidgetTemp);
			pDockWidgetEagelEye->setMinimumWidth(100);
			pDockWidgetEagelEye->setMinimumHeight(100);
			appWin.addDockWidget(Qt::LeftDockWidgetArea, pDockWidgetEagelEye);
			appWin.m_pDockWidgetEagleEye = pDockWidgetEagelEye;

			//viewerWidgetTemp->show();
		}
	}

	if (mapNode.valid())
	{
		const Config& externals = mapNode->externalConfig();

		if (mapNode->getMap()->isGeocentric())
		{
			// Sky model.
			Config skyConf = externals.child("sky");

			double hours = skyConf.value("hours", 12.0);
			SkyOptions options;
			//options.setDriver("gl");
			s_sky = osgEarth::Util::SkyNode::create(options, mapNode);

			QDateTime dataTime = QDateTime::currentDateTime();
			double dHour = dataTime.time().hour() + dataTime.time().minute() / 60.0 + dataTime.time().second() / 60.0 / 60.0;
			s_sky->setDateTime(osgEarth::DateTime(dataTime.date().year(), dataTime.date().month(), dataTime.date().day(), dHour));

			s_sky->setMoonVisible(true);
			for (osgEarth::QtGui::ViewVector::iterator i = views.begin(); i != views.end(); ++i)
				s_sky->attach(*i, 0);
			root->addChild(s_sky);

			// Ocean surface.
			if (externals.hasChild("ocean"))
			{
				s_ocean = osgEarth::Util::OceanNode::create(
					osgEarth::Util::OceanOptions(externals.child("ocean")),
					mapNode.get());

				if (s_ocean)
					root->addChild(s_ocean);
			}
		}
	}

	viewer = viewerWidget->getViewer();

	// activate "on demand" rendering if requested:
	if (on_demand)
	{
		viewer->setRunFrameScheme(osgViewer::ViewerBase::ON_DEMAND);
		OE_NOTICE << "On-demand rendering activated" << std::endl;
	}

	//ln_debug 2016/07/13 20:13
	if (0)
	{
		const Config& externals = mapNode->externalConfig();
		const Config& annoConf = externals.child("annotations");

		osg::ref_ptr<osgDB::Options> dbOptions = Registry::instance()->cloneOrCreateOptions();

		osg::Group* annotations = 0L;
		AnnotationRegistry::instance()->create(mapNode, annoConf, dbOptions.get(), annotations);

		if (annotations)
		{
			int nCount = annotations->getNumChildren();
			for(int i = 0; i < nCount; i++)
			{
				AnnotationNode* pAnno = dynamic_cast<AnnotationNode*>(annotations->getChild(i));
				dataManager->addAnnotation(pAnno, s_annoGroup);
			}
		}
	}

	//ln_debug 2016/07/30 0:10 Feature Test
	{
// 		osgEarth::Symbology::Style lineStyle;
// // 		lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// // 			->stroke()->color() = osgEarth::Symbology::Color::Yellow;
// 		lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// 			->stroke()->width() = 2.0;
// 
// 		lineStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
// 			->fill()->color() = osgEarth::Symbology::Color::Red;
// 
// 		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(new osgEarth::Annotation::LineString,
// 			dataManager->MapNode()->getMapSRS(), lineStyle);
// 
// 		pFeature->getGeometry()->push_back(osg::Vec3d(-120.37, 34.039, 50000.0));
// 		pFeature->getGeometry()->push_back(osg::Vec3d(-120.09, 33.96, 50000.0));
// 		pFeature->getGeometry()->push_back(osg::Vec3d(-119.75, 34 ,50000.0));
	}

	TrackSimVector trackSims;
	if (trackData)
	{
		// create demo tracks
		osg::ref_ptr<osg::Image> srcImage = osgDB::readImageFile(/*TRACK_ICON_URL*/"C:/OSG_OSGEarth/gwaldron-osgearth-2.7-0-g25ce0e1/data/m2525_air.png");
		osg::ref_ptr<osg::Image> image;
		ImageUtils::resizeImage(srcImage.get(), TRACK_ICON_SIZE, TRACK_ICON_SIZE, image);

		TrackNodeFieldSchema schema;
		createTrackSchema(schema);
		dataManager->addAnnotation(createTrack(schema, image, "Plane 1", mapNode.get(), osg::Vec3d(-121.463, 46.3548, 1500.71), 10000, 24, trackSims), s_annoGroup);
		dataManager->addAnnotation(createTrack(schema, image, "Plane 2", mapNode.get(), osg::Vec3d(-121.656, 46.0935, 4133.06), 10000, 8, trackSims), s_annoGroup);
		dataManager->addAnnotation(createTrack(schema, image, "Plane 3", mapNode.get(), osg::Vec3d(-121.321, 46.2589, 1390.09), 10000, 12, trackSims), s_annoGroup);

		viewer->addUpdateOperation(new TrackSimUpdate(trackSims));
	}

	if (viewer.valid())
		viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);


	// create catalog widget and add as a docked widget to the main window
	QDockWidget *catalogDock = new QDockWidget(QString::fromLocal8Bit("Õº≤„"));
	catalogDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::MapCatalogWidget* layerCatalog = new osgEarth::QtGui::MapCatalogWidget(dataManager.get(), osgEarth::QtGui::MapCatalogWidget::ALL_LAYERS);
	layerCatalog->setActiveViews(views);
	layerCatalog->setHideEmptyGroups(true);
	catalogDock->setWidget(layerCatalog);
	appWin.addDockWidget(Qt::LeftDockWidgetArea, catalogDock);
	appWin.m_pDockWidgetLayers = catalogDock;


	// create layer manager widget and add as a docked widget on the right
	QDockWidget *layersDock = new QDockWidget(QString::fromLocal8Bit("Õ∏√˜∂»µ˜’˚"));
	layersDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::LayerManagerWidget* layerManager = new osgEarth::QtGui::LayerManagerWidget(dataManager.get(), osgEarth::QtGui::LayerManagerWidget::IMAGE_LAYERS);
	layerManager->setActiveViews(views);
	layersDock->setWidget(layerManager);
	appWin.addDockWidget(Qt::LeftDockWidgetArea, layersDock);
	appWin.m_pDockWidgetImageLayers = layersDock;


	// create and dock an annotation list widget
	QDockWidget *annoDock = new QDockWidget(QString::fromLocal8Bit("±Í◊¢"));
	annoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::AnnotationListWidget* annoList = new osgEarth::QtGui::AnnotationListWidget(dataManager.get());
	annoList->setActiveViews(views);
	annoDock->setWidget(annoList);
	//annoDock->hide();
	appWin.addDockWidget(Qt::RightDockWidgetArea, annoDock);
	appWin.m_pDockWidgetAnno = annoDock;


	// create a second catalog widget for viewpoints
	QDockWidget *vpDock = new QDockWidget(QString::fromLocal8Bit(" ”µ„"));
	vpDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::MapCatalogWidget* vpCatalog = new osgEarth::QtGui::MapCatalogWidget(dataManager.get(), osgEarth::QtGui::MapCatalogWidget::VIEWPOINTS);
	vpCatalog->setActiveViews(views);
	vpDock->setWidget(vpCatalog);
	vpDock->hide();
	appWin.addDockWidget(Qt::RightDockWidgetArea, vpDock);
	appWin.m_pDockWidgetViewPoints = vpDock;

	//////////////////////////////////////////////////////////////////////////
// 	osg::Group* sceneroot = new osg::Group;
// 
// 	sceneroot->addChild(osgDB::readNodeFile("cow.osg"));
// 	osg::ref_ptr<osgViewer::Viewer> viewerEagle = new osgViewer::Viewer;
// 	viewerEagle->addEventHandler(new osgGA::StateSetManipulator(viewerEagle->getCamera()->getOrCreateStateSet()));
// 	viewerEagle->addEventHandler(new osgViewer::StatsHandler);
// 
// 
// 	viewerEagle->setSceneData(sceneroot);
// 	viewerEagle->setCameraManipulator(new osgGA::TrackballManipulator);
// 	viewerEagle->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
// 
// 	//osgQt::setViewer(viewer.get());
// 
// 
// 	osgQt::GLWidget* glw = new osgQt::GLWidget;
// 	osgQt::GraphicsWindowQt* graphicswin = new osgQt::GraphicsWindowQt(glw);
// 
// 	viewerEagle->getCamera()->setViewport(new osg::Viewport(0, 0, glw->width(), glw->height()));
// 	viewerEagle->getCamera()->setGraphicsContext(graphicswin);
// 
// 	QDockWidget* pDockWidget = new QDockWidget("EagleEye");
// 	pDockWidget->setWidget(glw);
// 
// 	appWin.addDockWidget(Qt::RightDockWidgetArea, pDockWidget);
	//////////////////////////////////////////////////////////////////////////

	// create and dock a LOSControlWidget
// 	QDockWidget *losDock = new QDockWidget;
// 	losDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
// 	osgEarth::QtGui::LOSControlWidget* losControl = new osgEarth::QtGui::LOSControlWidget(root, mapNode.get(), dataManager.get());
// 	losControl->setActiveViews(views);
// 	losDock->setWidget(losControl);
// 	appWin.addDockWidget(Qt::RightDockWidgetArea, losDock);

	// create terrain profile widget
	osgEarth::QtGui::TerrainProfileWidget* terrainProfiler = new osgEarth::QtGui::TerrainProfileWidget(root, mapNode.get());
	terrainProfiler->setActiveViews(views);
	appWin.setTerrainProfileWidget(terrainProfiler);

	QString strStyleSheet = "#oeFrameContainer, #oeFrameContainer * { background-color: rgba(255, 255, 255, 100%) } #oeItemHeader, #oeItemHeader * { background-color: rgba(17, 88, 160, 100%); color: white; }";

	// attempt to load .qss stylesheet if one was provided
	if (1)
	{
		QString qstylesheet = strStyleSheet;
		//a.setStyleSheet(qstylesheet);
		layerManager->setStyleSheet(qstylesheet);
 		annoList->setStyleSheet(qstylesheet);
// 		losControl->setStyleSheet(qstylesheet);
	}

//	appWin.SetNoFrame();

//	appWin.setGeometry(0, 0, 1024, 600);
	appWin.showMaximized();
	appWin.show();

//	Heat hae1(viewerEagle.get());
	return a.exec();
}
