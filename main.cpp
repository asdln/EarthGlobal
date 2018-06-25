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

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QDialog>

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
#include "RangeFeatureGenerator.h"

#include "SetParaDockWidget.h"
#include "CentralWidget.h"

#include "osgEarth/DataParaManager.h"

#include "ScreenCapture.h"

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

RangeFeatureGenerator* g_pRangerFeatureGenerator = NULL;

QMdiSubWindow* g_pMdiSubWindow = NULL;
Qtitan::RibbonStatusBar* g_pStatusBar = NULL;
osgEarth::QtGui::ViewerWidget* g_viewerWidget = NULL;
QMdiArea* g_pMdiArea = NULL;

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


class PickHandler : public osgGA::GUIEventHandler {
public:

    PickHandler(osgText::Text* updateText):
        _updateText(updateText) {}

    ~PickHandler() {}

    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

    virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);

protected:

    osg::ref_ptr<osgText::Text>  _updateText;
};

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
    switch(ea.getEventType())
    {
        case(osgGA::GUIEventAdapter::PUSH):
        {
            osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
            if (view) pick(view,ea);
            return false;
        }
        case(osgGA::GUIEventAdapter::KEYDOWN):
        {
            if (ea.getKey()=='c')
            {
                osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
                osg::ref_ptr<osgGA::GUIEventAdapter> event = new osgGA::GUIEventAdapter(ea);
                event->setX((ea.getXmin()+ea.getXmax())*0.5);
                event->setY((ea.getYmin()+ea.getYmax())*0.5);
                if (view) pick(view,*event);
            }
            return false;
        }
        default:
            return false;
    }
}


QString g_strAirTarget;
extern QDialog* g_pDetectToolDlg;
void PickHandler::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea)
{
    osgUtil::LineSegmentIntersector::Intersections intersections;

	g_strAirTarget.clear();

	QString strTarget;
	QString strAir;

	if (g_pDetectToolDlg && g_pDetectToolDlg->isHidden())
		return;

    if (view->computeIntersections(ea,intersections))
    {
		int nWid, nHei;
		DataParaManager::Instance()->GetSize(nWid, nHei);

        for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
            hitr != intersections.end();
            ++hitr)
        {
            std::ostringstream os;
            if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
            {
                // the geodes are identified by name.
                os<<"Object \""<<hitr->nodePath.back()->getName()<<"\""<<std::endl;
            }
            else if (hitr->drawable.valid())
            {
                os<<"Object \""<<hitr->drawable->className()<<"\""<<std::endl;
				std::string name = hitr->drawable->getName();

				if (!name.empty())
				{
					if (name[0] == 't' && strTarget.isEmpty())
					{
						strTarget = name.c_str();
						strTarget = strTarget.right(strTarget.size() - 2);

						strTarget = QString::fromLocal8Bit("目标, ") + strTarget;
					}
					else if (name[0] == 'a')
					{
						osg::Drawable* pDrawable = hitr->drawable.get();

						bool bRes = pDrawable->getSupportsDisplayList();
						bRes = pDrawable->getUseDisplayList();
// 						osg::NodePath nodePath = hitr->nodePath;
// 
// 						for (int i = 0; i < nodePath.size(); i ++)
// 						{
// 							osg::Node* pNode = nodePath.at(i);
// 							QString nameTemp = pNode->getName().c_str();
// 							int x = 0;
// 						}

						strAir = name.c_str();
						strAir = strAir.right(strAir.size() - 2);
						int nIndex = strAir.toInt();

						int nRows = nIndex / nWid;
						int nCols = nIndex % nWid;

						int nTest = nRows * nWid + nCols;

						double dRatio = 0.0;
						double dTrans = 1.0;
						DataParaManager::Instance()->GetValue(nCols, nRows, dRatio, dTrans);

						strAir = QString::fromLocal8Bit("大气，辐射: ") + QString::number(dRatio) + QString::fromLocal8Bit("，透过率: ")
							+ QString::number(dTrans) + " cols: " + QString::number(nCols) + " rows: " + QString::number(nRows);
					}
				}
            }

//             os<<"        local coords vertex("<< hitr->getLocalIntersectPoint()<<")"<<"  normal("<<hitr->getLocalIntersectNormal()<<")"<<std::endl;
//             os<<"        world coords vertex("<< hitr->getWorldIntersectPoint()<<")"<<"  normal("<<hitr->getWorldIntersectNormal()<<")"<<std::endl;
//             const osgUtil::LineSegmentIntersector::Intersection::IndexList& vil = hitr->indexList;
//             for(unsigned int i=0;i<vil.size();++i)
//             {
//                 os<<"        vertex indices ["<<i<<"] = "<<vil[i]<<std::endl;
//             }
// 
//             gdlist += os.str();
        }
    }

	g_strAirTarget = strAir + "\r\n" + strTarget;
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
	mapNode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

	//设置线框模式
	if (0)
	{
		osg::StateSet* stateset = mapNode->getOrCreateStateSet();
		osg::ref_ptr<osg::PolygonMode> polygonMode = new osg::PolygonMode();
		polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		stateset->setAttribute(polygonMode.get(), osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
	}

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
	}
	else
	{
		g_viewerMain = new osgViewer::Viewer();
		g_viewerMain->setSceneData(root);
		g_viewerMain->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
		g_viewerMain->setCameraManipulator(new osgEarth::Util::EarthManipulator());
		viewerWidget = new CentralWidget(g_viewerMain);
		g_viewerWidget = viewerWidget;

		{
// 			osgEarth::QtGui::ViewVector viewsTemp;
// 			viewerWidget->getViews(viewsTemp);

// 			osg::Camera* camera = viewsTemp[0]->getCamera();
// 
// 			camera->setProjectionMatrixAsPerspective(
// 				60.0, camera->getViewport()->width() / camera->getViewport()->height(), 1.0f, 10000.0f);
		}

		if (0)
		{
			double height = osg::DisplaySettings::instance()->getScreenHeight();
			double width = osg::DisplaySettings::instance()->getScreenWidth();
			double distance = osg::DisplaySettings::instance()->getScreenDistance();
			double vfov = osg::RadiansToDegrees(atan2(height /*/ 2.0f*/, distance)*2.0);

			osg::Camera* camera = g_viewerMain->getCamera();
			camera->setProjectionMatrixAsPerspective(120.0, camera->getViewport()->width() / camera->getViewport()->height(), 1.0f, 10000.0f);
		}

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
			i->get()->addEventHandler(new PickHandler(0));
			views.push_back(*i);
		}

		viewerWidget->setMinimumWidth(100);
		viewerWidget->setMinimumHeight(100);

		QMdiArea* pMdiArea = new QMdiArea;
		g_pMdiArea = pMdiArea;
		QMdiSubWindow* pSubWindow = pMdiArea->addSubWindow(viewerWidget);
		pSubWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
		g_pMdiSubWindow = pSubWindow;
		pSubWindow->setGeometry(QRect(0, 0, 800, 600));

		appWin.setCentralWidget(pMdiArea/*viewerWidget*/);
		appWin.setViewerWidget(viewerWidget);
		appWin.InitCameraDlg();

		//鹰眼图
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

			osg::Group* rootEagleEye = new osg::Group();
			rootEagleEye->addChild(mapNodeEagleEye);

			g_viewerEagleEye = new osgViewer::Viewer();
			g_viewerEagleEye->setSceneData(rootEagleEye);
			g_viewerEagleEye->setThreadingModel(osgViewer::ViewerBase::SingleThreaded/*osgViewer::Viewer::DrawThreadPerContext*/);
			g_viewerEagleEye->setCameraManipulator(new EagleEyeEarthManipulator());

			osgEarth::QtGui::ViewerWidget* viewerWidgetTemp = new CentralWidget(g_viewerEagleEye);
			viewerWidgetTemp->getGraphicsWindow()->setTouchEventsEnabled(true);

			MouseMoveFilter* pEventFilter = new MouseMoveFilter();
			viewerWidgetTemp->installEventFilter(pEventFilter);

			ViewPointSyn* pSyn = new ViewPointSyn;
			QTimer* pSynTimer = new QTimer(&appWin);
			QObject::connect(pSynTimer, SIGNAL(timeout()), pSyn, SLOT(slotDoSyn()));
			pSynTimer->start(200);

			g_pRangerFeatureGenerator = new RangeFeatureGenerator(viewerWidget, root, rootEagleEye, mapNode, mapNodeEagleEye);
			QObject::connect(pSynTimer, SIGNAL(timeout()), g_pRangerFeatureGenerator, SLOT(RefreshRangeFeature()));

// 			osgEarth::QtGui::ViewVector viewsTemp;
// 			viewerWidgetTemp->getViews(viewsTemp);
// 			for (osgEarth::QtGui::ViewVector::iterator i = viewsTemp.begin(); i != viewsTemp.end(); ++i)
// 			{
// 				i->get()->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNodeEagleEye));
// 				views.push_back(*i);
// 			}

			QDockWidget* pDockWidgetEagelEye = new QDockWidget(QString::fromLocal8Bit("鹰眼图"));
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
			if (0)
			{
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
			}

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

	if (viewer.valid())
		viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);


	// create catalog widget and add as a docked widget to the main window
	QDockWidget *catalogDock = new QDockWidget(QString::fromLocal8Bit("图层"));
	catalogDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::MapCatalogWidget* layerCatalog = new osgEarth::QtGui::MapCatalogWidget(dataManager.get(), osgEarth::QtGui::MapCatalogWidget::ALL_LAYERS);
	layerCatalog->setActiveViews(views);
	layerCatalog->setHideEmptyGroups(true);
	catalogDock->setWidget(layerCatalog);
	appWin.addDockWidget(Qt::LeftDockWidgetArea, catalogDock);
	appWin.m_pDockWidgetLayers = catalogDock;


	// create layer manager widget and add as a docked widget on the right
	QDockWidget *layersDock = new QDockWidget(QString::fromLocal8Bit("透明度调整"));
	layersDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::LayerManagerWidget* layerManager = new osgEarth::QtGui::LayerManagerWidget(dataManager.get(), osgEarth::QtGui::LayerManagerWidget::IMAGE_LAYERS);
	layerManager->setActiveViews(views);
	layersDock->setWidget(layerManager);
	appWin.addDockWidget(Qt::LeftDockWidgetArea, layersDock);
	appWin.m_pDockWidgetImageLayers = layersDock;


	QDockWidget *pTargetDataDock = new SetParaDockWidget(QString::fromLocal8Bit("参数"));
	pTargetDataDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	//pTargetDataDock->setWidget(pTabWidget/*pTargetPositionWidget*/);
	pTargetDataDock->setMinimumHeight(240);
	
	appWin.addDockWidget(Qt::RightDockWidgetArea, pTargetDataDock);

	// create and dock an annotation list widget
	QDockWidget *annoDock = new QDockWidget(QString::fromLocal8Bit("标注"));
	annoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	osgEarth::QtGui::AnnotationListWidget* annoList = new osgEarth::QtGui::AnnotationListWidget(dataManager.get());
	annoList->setActiveViews(views);
	annoDock->setWidget(annoList);
	//annoDock->hide();
	appWin.addDockWidget(Qt::RightDockWidgetArea, annoDock);
	appWin.m_pDockWidgetAnno = annoDock;




	// create a second catalog widget for viewpoints
	QDockWidget *vpDock = new QDockWidget(QString::fromLocal8Bit("视点"));
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
