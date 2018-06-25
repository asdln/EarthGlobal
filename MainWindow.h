#ifndef EARTHGLOBAL_H
#define EARTHGLOBAL_H

#include <osgEarthQt/AnnotationToolbar>
#include <osgEarthQt/Common>
#include <osgEarthQt/DataManager>
#include <osgEarthQt/MapCatalogWidget>
#include <osgEarthQt/TerrainProfileWidget>
#include <osgEarthQt/ViewerWidget>

#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/GeoData>
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
#include <osgEarthAnnotation/LocalGeometryNode>
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

#include <osgEarthDrivers/bing/bingoptions>

#include <QtWidgets/QTextEdit>
#include <QAction>
#include <QDockWidget>
#include <QtGui>
#include <QMainWindow>
#include <QToolBar>

#include <QtWidgets/QMainWindow>
#include "ui_earthglobal.h"

#include "RibbonWindow.h"
#include "CameraPostionDlg.h"

class Heat : public QObject
{
	Q_OBJECT

public:
	Heat(osgViewer::Viewer* viewer)
	{
		v = viewer;

		bool bRes = connect(&timer, SIGNAL(timeout()), this, SLOT(Do()));
		timer.start(10);
	}



	~Heat(){}

	osgViewer::Viewer* v;

	QTimer timer;

	public slots:

	void Do()
	{
		v->frame();
	}
};


class MainWindow : public RibbonWindow
{
	Q_OBJECT

public:

	MainWindow(osgEarth::QtGui::DataManager* manager, osgEarth::MapNode* mapNode, osg::Group* annotationRoot);
	~MainWindow();

public:

	void setViewerWidget(osgEarth::QtGui::ViewerWidget* viewerWidget);

	void setTerrainProfileWidget(osgEarth::QtGui::TerrainProfileWidget* widget);

	void InitCameraDlg();

protected:

	void createMenuFile();

	void createRibbon();

	void createGroupDataManager(Qtitan::RibbonPage* page);
	void createGroupRadioData(Qtitan::RibbonPage* page);
	void createGroupTemperatureData(Qtitan::RibbonPage* page);
	void createGroupAirData(Qtitan::RibbonPage* page);
	void createGroupRenderPara(Qtitan::RibbonPage* page);
	void createGroupTool(Qtitan::RibbonPage* page);

	void createGroupAnnotation(Qtitan::RibbonPage* page);

	void createGroupSky(Qtitan::RibbonPage* page);

	void createGroupAnimation(Qtitan::RibbonPage* page);

	void createGroupDocumentViews(Qtitan::RibbonGroup* group);

	void createGroupDataTranslate(Qtitan::RibbonPage* page);

	void createGroupTarget(Qtitan::RibbonPage* page);


protected Q_SLOTS:

	void fullScreen(bool checked);

	void OpenProject();

	void NewProject();

	void SaveAsProject();

	void slotEscPressed();

	void slotAnnoAdding();

	void slotAnnoAddFinished();

	void slotDataTimeChanged(const QDateTime& dataTime);

	void slotSliderHourChanged(int nValue);

	void slotSetCameraPos();

	void slotRefresh();

	void slotDetectTool();

	//////////////////////////////////////////////////////////////////////////

private slots:

	void slotTest();

	void loadCameraPath();

	void slotDirectManipulator();

	void loadTargetPath();

	void startAnmiation();

	void StopAnimation();

	void OutputAnimation();

	void slotSavePicAsTxt();

	void MakeAnimation();

	void AnimationSettings();

	void addModisRadioLayer();

	void addModisTemperatureLayer();

	void addModelLayer();

	void addAnnotation();

	void addTargetData();

	void addAirData();

	void slotSetJetthreshold();

//	void addTargetDataJet();

	void Target2plt();

	void LoadPlt();

//	void UnloadAirData();

	void terrainProfileToggled(bool checked);

	void slotSetRenderMode();

	void slotDataTranslateToRadio();

	void slotFixedAngleMode(bool checked);

	void slotRefreshTargetData();

	void slotRefreshAirData();

protected:

	//osgEarth::Features::Feature* GetAirFeature();

public:

	//void setTransparent(osgEarth::Annotation::FeatureNode* node, double dTrans);

protected:

	void closeEvent(QCloseEvent *event)
	{
		if (_viewerWidget)
		{
			_viewerWidget->getViewer()->setDone(true);
		}

		event->accept();
	}

	void changeEvent(QEvent* e);

protected:

	std::vector<QAction*> m_vecAnnoAction;

	QAction* m_actionFileNew;
	QAction* m_actionOpenFile;
	QAction* m_actionSaveFile;

	QAction* m_actionFullScreen;

	//QAction *_addRemoveLayerAction;
	QAction* m_pActionAddModisRadioLayer;

	QAction* m_pActionAddTargetData;
	QAction* m_pActionAddAirData;

	QAction *_addAnnotationAction;
	QAction *_terrainProfileAction;

	Qtitan::RibbonPage* m_pageHome;
	Qtitan::RibbonPage* m_pageLayout;

	Qt::WindowStates m_stateWindow;

	CameraPostionDlg* m_pCameraPosDlg;

	QTimer* m_pSynTimer;

public:

	QDockWidget* m_pDockWidgetLayers;
	QDockWidget* m_pDockWidgetImageLayers;
	QDockWidget* m_pDockWidgetAnno;
	QDockWidget* m_pDockWidgetViewPoints;

	QDockWidget* m_pDockWidgetEagleEye;

	QWidget* m_pOutputWidget;

private:

	osg::ref_ptr<osgEarth::QtGui::DataManager> _manager;
	osg::ref_ptr<osgEarth::MapNode> _mapNode;
	osg::ref_ptr<osg::Group> _annoRoot;
	osg::ref_ptr<osgEarth::ImageLayer> _testLayer;
	osgEarth::QtGui::ViewerWidget* _viewerWidget;
	osgEarth::QtGui::AnnotationToolbar* _annotationToolbar;
	osgEarth::QtGui::ViewVector _views;
	bool _layerAdded;

	QDockWidget *_terrainProfileDock;
};

#endif // EARTHGLOBAL_H
