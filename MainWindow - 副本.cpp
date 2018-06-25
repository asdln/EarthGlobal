#include "MainWindow.h"
#include "ribbonimages.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>
#include <QClipboard>
#include <QDesktopServices>
#include <QTextEdit>
#include <QTextCodec>
#include <QLineEdit>
#include <QTextDocumentWriter>
#include <QAbstractTextDocumentLayout>
#include <QFileDialog>
#include <QFile>
//#include <QPrinter>
#include <QSpinBox>
//#include <QPrintDialog>
#include <QFontComboBox>
#include <QTextDocument>
#include <QLabel>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
//#include <QPrintPreviewDialog>
#include <QTextList>
#include <QColorDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QDockWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QListWidget>
#include <QBuffer>
#include <QUrl>
#include <QtCore/QTextCodec>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QHBoxLayout>

#include <QtnRibbonStyle.h>
#include <QtnRibbonCustomizePage.h>

#include <osgEarthQt/Common>

#include "aboutdialog.h"
//#include "ribbonpopularpage.h"
#include "RibbonWindow.h"
#include "mainwindow.h"
#include "ModelLayerReader.h"

#include <QtWidgets/QDateEdit>
#include <QtWidgets/QCalendarWidget>

#include <osgEarthFeatures/GeometryUtils>
#include <osgEarthFeatures/OgrUtils>
#include <osgEarthQt/GuiActions>

#include "TargetDataReader.h"
#include "AirDataReader.h"
#include "osgEarth/DataParaManager.h"
#include "RenderModeDlg.h"
#include "AirDataDlg.h"
#include "Target2PltDlg.h"
#include "Targetfile2tecplot.h"
#include "OutputDlg.h"

#include "RangeFeatureGenerator.h"
#include "targetdatadlg.h"
#include "osgEarth/ColorTransform.h"
#include "SysUtility.h"

extern osg::ref_ptr<osg::Group> s_annoGroup;
QAction* g_pActionDetectTool = NULL;

bool g_bIsFixedAngldMode = false;
extern osgEarth::Features::Feature* GetAirFeature(double dTransparent);

using namespace Qtitan;

MainWindow::MainWindow(osgEarth::QtGui::DataManager* manager, osgEarth::MapNode* mapNode, osg::Group* annotationRoot)
: _manager(manager), _mapNode(mapNode), _annoRoot(annotationRoot), _layerAdded(false), _terrainProfileDock(0L), _viewerWidget(0L)
{
	setWindowTitle(tr("Earth Global"));

	createMenuFile();
	//createQuickAccessBar();
	createRibbon();

 	ribbonBar()->setFrameThemeEnabled();
	//setWindowFlags(/*Qt::FramelessWindowHint*/ /*Qt::WindowSystemMenuHint |*/windowFlags() & ~Qt::WindowMinimizeButtonHint);
 	m_stateWindow = windowState();

	QString strFilePath = QApplication::applicationFilePath();
	strFilePath = QFileInfo(strFilePath).absolutePath();

	osgEarth::Drivers::BingOptions bing;
	bing.key() = QString(strFilePath + "/data/1").toUtf8().data();
	_manager->map()->addImageLayer(new osgEarth::ImageLayer("TileImage", bing));

	m_pCameraPosDlg = NULL;

	m_pSynTimer = new QTimer(this);
	m_pSynTimer->start(200);

	m_pOutputWidget = NULL;

//	resize(1600, 900);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitCameraDlg()
{
	m_pCameraPosDlg = new CameraPostionDlg(this);
	QObject::connect(m_pSynTimer, SIGNAL(timeout()), m_pCameraPosDlg, SLOT(slotRefreshInfo()));
}

void MainWindow::changeEvent(QEvent* e)
{
	//使用ribbon界面库后，最小化，主窗口会黑屏。截获消息，resize可以恢复正常。
	if (e->type() == QEvent::WindowStateChange)
	{
		static int s_nTag = 0;
 		if (this->windowState() & Qt::WindowMinimized)
 		{
			s_nTag = 1;
 		}
		else
		{
			if (s_nTag == 1)
			{
				Qt::WindowStates state = this->windowState();
				if (state == 0 || state == 2)
				{
					extern QMdiSubWindow* g_pMdiSubWindow;
					extern QMdiArea* g_pMdiArea;

					g_pMdiArea->resize(QSize(g_pMdiArea->geometry().width(), g_pMdiArea->geometry().height() - 1));
					g_pMdiArea->resize(QSize(g_pMdiArea->geometry().width(), g_pMdiArea->geometry().height() + 1));

// 					g_pMdiSubWindow->resize(QSize(g_pMdiSubWindow->geometry().width(), g_pMdiSubWindow->geometry().height() - 1));
// 					g_pMdiSubWindow->resize(QSize(g_pMdiSubWindow->geometry().width(), g_pMdiSubWindow->geometry().height() + 1));
// 
// 					_viewerWidget->resize(QSize(_viewerWidget->geometry().width(), _viewerWidget->geometry().height() - 1));
// 					_viewerWidget->resize(QSize(_viewerWidget->geometry().width(), _viewerWidget->geometry().height() + 1));

					m_pDockWidgetEagleEye->resize(QSize(m_pDockWidgetEagleEye->geometry().width(), m_pDockWidgetEagleEye->geometry().height() - 1));
					m_pDockWidgetEagleEye->resize(QSize(m_pDockWidgetEagleEye->geometry().width(), m_pDockWidgetEagleEye->geometry().height() + 1));

					s_nTag = 0;
				}
			}
		}
	}

	return RibbonWindow::changeEvent(e);
}

// void MainWindow::keyPressEvent(QKeyEvent* event)
// {
// 	Qtitan::RibbonMainWindow::keyPressEvent(event);
// 	if (event->key() == Qt::Key_Escape && m_actionFullScreen->isChecked())
// 		fullScreen(false);
// }

void MainWindow::slotEscPressed()
{
	if(m_actionFullScreen->isChecked())
		fullScreen(false);
}

void MainWindow::fileOpen()
{

}

void MainWindow::fileSave()
{

}

void MainWindow::fileSaveAs()
{

}

void MainWindow::setViewerWidget(osgEarth::QtGui::ViewerWidget* viewerWidget)
{
	
	_viewerWidget = viewerWidget;

	_views.clear();
	_viewerWidget->getViews(_views);

	_annotationToolbar->setActiveViews(_views);
}

void MainWindow::setTerrainProfileWidget(osgEarth::QtGui::TerrainProfileWidget* widget)
{
	if (!_terrainProfileDock)
	{
		_terrainProfileDock = new QDockWidget;
		_terrainProfileDock->setAllowedAreas(Qt::BottomDockWidgetArea);
		_terrainProfileDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		addDockWidget(Qt::BottomDockWidgetArea, _terrainProfileDock);
		_terrainProfileDock->setVisible(_terrainProfileAction->isChecked());
	}

	_terrainProfileDock->setWidget(widget);
}

void MainWindow::addModisRadioLayer()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/home",
		tr("Images (*.tif *.TIFF *.img)"));

	if (fileName.isEmpty())
		return;

	QFileInfo fileInfo(fileName);

	QString string = fileName;
	QTextCodec *codec = QTextCodec::codecForName("GB18030");
	QByteArray encodedString = codec->fromUnicode(string);

	osgEarth::Drivers::GDALOptions layerOpt;
	layerOpt.url() = osgEarth::URI(encodedString.data());
	layerOpt.isRadioModis() = true;
	osg::ref_ptr<osgEarth::ImageLayer> ptrImageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(fileInfo.fileName().toUtf8().data(), layerOpt));

	if (ptrImageLayer == NULL)
		return;

	ptrImageLayer->SetGuid(SysUtility::GetGUIDString());
	_manager->map()->addImageLayer(ptrImageLayer.get());
}

void MainWindow::addModisTemperatureLayer()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home",
													tr("Images (*.tif *.TIFF *.img)"));

	if(fileName.isEmpty())
		return;

	QFileInfo fileInfo(fileName);

	QString string = fileName;
	QTextCodec *codec = QTextCodec::codecForName("GB18030");
	QByteArray encodedString = codec->fromUnicode(string);

	osgEarth::Drivers::GDALOptions layerOpt;
	layerOpt.url() = osgEarth::URI(encodedString.data());
	layerOpt.isTemperatureModis() = true;
	osg::ref_ptr<osgEarth::ImageLayer> ptrImageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(fileInfo.fileName().toUtf8().data(), layerOpt));

	if(ptrImageLayer == NULL)
		return;

	ptrImageLayer->SetGuid(SysUtility::GetGUIDString());
	_manager->map()->addImageLayer(ptrImageLayer.get());
}


//osg::ref_ptr<osg::Array> g_ArrayAirColorArray;
void MainWindow::addAirData()
{
	int nOldWid, nOldHei;
	DataParaManager::Instance()->GetSize(nOldWid, nOldHei);

	double dResX = 360.0 / nOldWid;
	double dResY = 180.0 / nOldHei;

	AirDataDlg dlg;
	dlg.ui.lineEdit_Lon->setText(QString::number(dResX));
	dlg.ui.lineEdit_Lat->setText(QString::number(dResY));
	if (!dlg.exec())
		return;

	QString strFileName = dlg.ui.label_filePath->text();

	dResX = dlg.ui.lineEdit_Lon->text().toDouble();
	dResY = dlg.ui.lineEdit_Lat->text().toDouble();

	int nWid = 360.0 / dResX;
	int nHei = 180.0 / dResY;

	//if (nWid != nOldWid || nHei != nOldHei)
	{
		DataParaManager::Instance()->SetSize(nWid, nHei);
	}

	QString strPath = dlg.ui.label_filePath->text();
	if (strPath.isEmpty())
	{
		strPath = QString::fromLocal8Bit("C:\\OSG_OSGEarth\\数据格式\\大气.txt");
	}

	AirDataReader reader;
	reader.AddData(strPath);

	osgEarth::Features::Feature* pFeature = GetAirFeature(1.0);

	osgEarth::Annotation::FeatureNode* pFeatureNode = new osgEarth::Annotation::FeatureNode(
		_manager->MapNode(), pFeature);

	//g_ArrayAirColorArray = pDoubleArray;

	osgEarth::Annotation::AnnotationData* pAnnoData = pFeatureNode->getOrCreateAnnotationData();
	pAnnoData->setViewpoint(osgEarth::Viewpoint(strFileName.toUtf8().data(), reader.m_dy, reader.m_dx, reader.m_dz, 0.0, -90.0, 1e5));
	pAnnoData->setName(strFileName.toUtf8().data());

	//DataParaManager::Instance()->DeleteBuffer();
	//_manager->MapNode()->getTerrainEngine()->dirtyTerrain();

	_manager->addAnnotation(pFeatureNode, s_annoGroup);
}

static char * vertexShader = {
	"varying vec4 color;\n"
	"void main(void ){\n"
	"color = gl_Vertex;\n"
	"gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;\n"
	"}\n"
};
static char * fragShader = {
	"varying vec4 color;\n"
	"void main(void){\n"
	"   gl_FragColor = clamp(color,0.0,1.0);\n"
	"}\n"
};

//void MainWindow::setTransparent(osgEarth::Annotation::FeatureNode* node, double dTrans)
//{
	//osgEarth::Annotation::Feature* pFeature = node->getFeature();
	//osg::Vec4Array* pArray = (osg::Vec4Array*)pFeature->getColorArray();

	//osg::Vec4Array* pArrayNew = new osg::Vec4Array;

	//for (int i = 0; i < pArray->size(); i ++)
	//{
	//	pArrayNew->push_back(osg::Vec4((*pArray)[i].r(), (*pArray)[i].g(), (*pArray)[i].b(), dTrans));
	//}

	//osgEarth::Annotation::Feature* pFeatureNew = new osgEarth::Annotation::Feature(*pFeature);
	//pFeatureNew->setColorArray(pArrayNew);

	//node->setFeature(pFeatureNew);
//}

//void MainWindow::UnloadAirData()
//{
//// 	DataParaManager::Instance()->ResetValue();
//// 	_manager->MapNode()->getTerrainEngine()->dirtyTerrain();
//	osg::Node* pNode = s_annoGroup->getChild(0);
//	osgEarth::Annotation::FeatureNode* pFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(pNode);
//
//	setTransparent(pFeatureNode, 0.5);
//}

void MainWindow::slotRefreshTargetData()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	_manager->getAnnotations(out_annotations);

	for (int i = 0; i < out_annotations.size(); i ++)
	{
		osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>(out_annotations[i].get());
		if (pLocalGeoNode == nullptr)
			continue;

		osgEarth::Annotation::AnnotationData* pData = pLocalGeoNode->getOrCreateAnnotationData();
		std::string strGuid = pData->getName();
		std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
		if (itr != TargetDataReader::s_mapPara.end())
		{
			TargetDataPara para = itr->second;
			TargetDataReader targetReader;

			osgEarth::GeoPoint geoPoint = pLocalGeoNode->getPosition();

			osg::Node* pNode = targetReader.GetGeode(para);
// 			osg::Vec4Array* pColorArray = NULL;
// 			osgEarth::Symbology::Geometry* pGeometry = 
// 				targetReader.GetGeometry(para, &pColorArray);
// 			pLocalGeoNode->setColorArray(pColorArray);
			pLocalGeoNode->setNode(pNode);
		}
	}
}

void MainWindow::slotRefreshAirData()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	_manager->getAnnotations(out_annotations);

	osgEarth::Annotation::FeatureNode* pAirFeatureNode = NULL;
	for (int i = 0; i < out_annotations.size(); i++)
	{
		pAirFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(out_annotations[i].get());
		if (pAirFeatureNode != nullptr)
			break;
	}

	if (pAirFeatureNode == nullptr)
		return;

	osgEarth::Features::Feature* pFeatureNew = GetAirFeature(1.0);;
	pAirFeatureNode->setFeature(pFeatureNew);
}

//void MainWindow::addTargetDataJet()
//{
//	QString strNewJetPath;
//
//	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
//		"/home",
//		tr("Tecplot file (*.dat *.plt)"));
//
//	if (fileName.isEmpty())
//		return;
//
//	strNewJetPath = fileName;
//
//	osgEarth::QtGui::AnnotationVector out_annotations;
//	_manager->getAnnotations(out_annotations);
//
//	osgEarth::Annotation::LocalGeometryNode* pLastLocalGeoNode = NULL;
//
//	for (int i = 0; i < out_annotations.size(); i++)
//	{
//		osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>(out_annotations[i].get());
//		if (pLocalGeoNode == nullptr)
//			continue;
//
//		pLastLocalGeoNode = pLocalGeoNode;
//	}
//
//	if (!pLastLocalGeoNode)
//	{
//		return;
//	}
//
//	osgEarth::Annotation::AnnotationData* pData = pLastLocalGeoNode->getOrCreateAnnotationData();
//	std::string strGuid = pData->getName();
//	std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
//	if (itr != TargetDataReader::s_mapPara.end())
//	{
//		itr->second.strJetPath = strNewJetPath;
//		TargetDataPara para = itr->second;
//		TargetDataReader targetReader;
//
//		osg::Node* pNode = targetReader.GetGeode(para);
//		pLastLocalGeoNode->setNode(pNode);
//	}
//}

void MainWindow::Target2plt()
{
	Target2PltDlg target2pltDlg;
	if (!target2pltDlg.exec())
		return;

	if (target2pltDlg.ui.lineEdit_Tri->text().isEmpty()
		|| target2pltDlg.ui.lineEdit_Tmp->text().isEmpty()
		|| target2pltDlg.ui.lineEdit_OutPlt->text().isEmpty())
	{
		return;
	}

	tempAverage(target2pltDlg.ui.lineEdit_Tmp->text(), 
		target2pltDlg.ui.lineEdit_Tri->text(), target2pltDlg.ui.lineEdit_OutPlt->text());
}

void MainWindow::Output()
{
	if (m_pOutputWidget == NULL)
	{
		m_pOutputWidget = new OutputDlg(this);
	}

	m_pOutputWidget->show();
}

void MainWindow::addTargetData()
{
// 	_manager->MapNode()->getTerrainEngine()->dirtyTerrain();
// 	return;

	TargetDataDlg dlgTarget;
	if (!dlgTarget.exec())
		return;

	TargetDataPara para;

	para.bTransToRadio = dlgTarget.ui.groupBox_ToRadio->isChecked();

	para.strIndexPath = dlgTarget.m_strTRI;
	para.strValuePath = dlgTarget.m_strTmp;
	para.strJetPath = dlgTarget.ui.label_LoadJet->text();

	para.dx = dlgTarget.GetX();
	para.dy = dlgTarget.GetY();
	para.dz = dlgTarget.GetZ();

	para.dAngleX = 0.0;
	para.dAngleY = 0.0;
	para.dAngleZ = 0.0;

	para.pJet1 = NULL;
	para.pJet2 = NULL;
	para.pJet3 = NULL;
	para.pJet4 = NULL;

	dlgTarget.GetPara(para.dstart, para.dend, para.dfen, para.dfa);

	TargetDataReader targetReader;
	osg::Vec4Array* pColorArray = NULL;
	osg::Node* pNode = targetReader.GetGeode(para);

	osgEarth::Annotation::Style circleStyle;
	circleStyle.getOrCreate<osgEarth::Annotation::PolygonSymbol>()->fill()->color() = osgEarth::Annotation::Color(osgEarth::Annotation::Color::Red, 0.5);

	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = new osgEarth::Annotation::LocalGeometryNode(_manager->MapNode(), pNode, circleStyle);
	osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();

	std::string strGuid = SysUtility::GetGUIDString();
	TargetDataReader::s_mapPara[strGuid] = para;
	
	//annoData->setName(QString::fromLocal8Bit("目标数据").toUtf8().data());
	annoData->setName(strGuid);
	annoData->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 10));
	pLocalGeoNode->setAnnotationData(annoData);
	pLocalGeoNode->setPosition(osgEarth::GeoPoint(_manager->MapNode()->getMapSRS()->getGeographicSRS(), osg::Vec3d(para.dx, para.dy, para.dz)));
//	pLocalGeoNode->setColorArray(pColorArray);

	//pFeatureNode->setStyle(lineStyle);

	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	osgEarth::Viewpoint viewPoint = mainMani->getViewpoint();

// 	viewPoint.focalPoint()->set(osgEarth::SpatialReference::get("wgs84"), dx, dy, dz, osgEarth::ALTMODE_ABSOLUTE);
// 	viewPoint.setHeading(dhor);
// 	viewPoint.setPitch(-dver);
// 	viewPoint.setRange(dRange);

	mainMani->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 10));

	_manager->addAnnotation(pLocalGeoNode, s_annoGroup);
}

void MainWindow::addModelLayer()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/home",
		tr("Model (*.layer)"));

	if (fileName.isEmpty())
		return;

	QFileInfo fileInfo(fileName);

	QString string = fileName;
	QTextCodec *codec = QTextCodec::codecForName("GB18030");
	QByteArray encodedString = codec->fromUnicode(string);

	ModelLayerReader modelReader;
	osgEarth::ModelLayer* pModelLayer = modelReader.CreateModelLayer(encodedString.data());
	//osgEarth::ModelLayer* pModelLayer = modelReader.CreateModelLayer("C:\\OSG_OSGEarth\\gwaldron-osgearth-2.7-0-g25ce0e1\\tests\\feature_models.earth");
	_manager->map()->addModelLayer(pModelLayer);
}

void MainWindow::addAnnotation()
{
	osgEarth::Annotation::PlaceNode* annotation = new osgEarth::Annotation::PlaceNode(
		_mapNode.get(),
		osgEarth::GeoPoint(_mapNode->getMapSRS(), -74.0, 40.714),
		osgDB::readImageFile("../data/placemark32.png"),
		"New York");

	osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();
	annoData->setName("New York");
	annoData->setViewpoint(osgEarth::Viewpoint("New Tork", -74, 40.714, 0, 0.0, -90.0, 1e5));
	annotation->setAnnotationData(annoData);

	annotation->installDecoration("selected", new osgEarth::Annotation::ScaleDecoration(2.0f));

	_manager->addAnnotation(annotation, _annoRoot.get());

	_addAnnotationAction->setDisabled(true);
}

void MainWindow::slotFixedAngleMode(bool checked)
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	_manager->getAnnotations(out_annotations);

	osgEarth::Annotation::FeatureNode* pAirFeatureNode = NULL;
	for (int i = 0; i < out_annotations.size(); i++)
	{
		pAirFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(out_annotations[i].get());
		if (pAirFeatureNode != nullptr)
			break;
	}

	DataParaManager::Instance()->SetFixedAngleMode(checked);
	if (!pAirFeatureNode)
		return;
	
	_manager->doAction(this, new osgEarth::QtGui::ToggleNodeAction(pAirFeatureNode, !checked));
	
	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	osgEarth::Viewpoint viewPoint = mainMani->getViewpoint();

	double dHeading = viewPoint.heading().value().getValue();
	double dpitch = viewPoint.pitch().value().getValue();

	viewPoint.focalPoint()->set(osgEarth::SpatialReference::get("wgs84"), AirDataReader::m_dy, AirDataReader::m_dx, AirDataReader::m_dz, osgEarth::ALTMODE_ABSOLUTE);
	viewPoint.setHeading(dHeading);
	viewPoint.setPitch(dpitch);
	viewPoint.setRange(0.0);

	mainMani->setViewpoint(viewPoint);

	double dLon = viewPoint.focalPoint().value().x();
	double dLat = viewPoint.focalPoint().value().y();
	double dH = viewPoint.focalPoint().value().z() + viewPoint.range().value().getValue();

	DataParaManager::Instance()->SetCameraPosInfo(dLon, dLat, dH);
//	g_bIsFixedAngldMode = checked;
	slotRefreshTargetData();
	_manager->MapNode()->getTerrainEngine()->dirtyTerrain();
}

void MainWindow::slotSetRenderMode()
{
	RenderModeDlg dlg;
	if(!dlg.exec())
		return;

	if (dlg.ui.radioButton_Gray->isChecked())
	{
		DataParaManager::Instance()->SetRGBMode(false);
	}
	else
	{
		DataParaManager::Instance()->SetRGBMode(true);
	}

	DataParaManager::Instance()->SetRadioMax(dlg.ui.lineEdit_RadioMax->text().toDouble());
	DataParaManager::Instance()->SetRadioMin(dlg.ui.lineEdit_RadioMin->text().toDouble());

	DataParaManager::Instance()->SetTemperatureMax(dlg.ui.lineEdit_TemperatureMax->text().toDouble());
	DataParaManager::Instance()->SetTemperatureMin(dlg.ui.lineEdit_TemperatureMin->text().toDouble());

	slotRefreshTargetData();
	slotRefreshAirData();
	_manager->MapNode()->getTerrainEngine()->dirtyTerrain();
}

void MainWindow::terrainProfileToggled(bool checked)
{
	if (_terrainProfileDock)
		_terrainProfileDock->setVisible(checked);
}

void MainWindow::createGroupDocumentViews(Qtitan::RibbonGroup* group)
{
	QIcon fullScreenIcons;
	fullScreenIcons.addPixmap(QPixmap(m_strResPath + "_fullscreen.png"));
	fullScreenIcons.addPixmap(QPixmap(m_strResPath + "_smallfullscreen.png"));
	m_actionFullScreen = group->addAction(fullScreenIcons, tr("Full Screen Reading"), Qt::ToolButtonTextUnderIcon);

	m_actionFullScreen->setCheckable(true);
	m_actionFullScreen->setChecked(false);
	connect(m_actionFullScreen, SIGNAL(triggered(bool)), this, SLOT(fullScreen(bool)));
}

void MainWindow::fullScreen(bool checked)
{
	if (checked)
	{
		m_stateWindow = windowState();
		m_actionFullScreen->setChecked(true);
		ribbonBar()->setVisible(false);

		m_pDockWidgetAnno->setVisible(false);
		m_pDockWidgetImageLayers->setVisible(false);
		m_pDockWidgetLayers->setVisible(false);
		m_pDockWidgetViewPoints->setVisible(false);

		setWindowState(Qt::WindowFullScreen);
	}
	else
	{
		ribbonBar()->setVisible(true);

		m_pDockWidgetAnno->setVisible(true);
		m_pDockWidgetImageLayers->setVisible(true);
		m_pDockWidgetLayers->setVisible(true);
		m_pDockWidgetViewPoints->setVisible(true);

		setWindowState(m_stateWindow);
		m_actionFullScreen->setChecked(false);
	}
}

void MainWindow::createMenuFile()
{
	//QIcon iconLogo;
	//iconLogo.addPixmap(QPixmap(m_strResPath + "largezoom.png"));
	//iconLogo.addPixmap(QPixmap(":/shared/res/qtitanlogo32x32.png"));
	if (QAction* actionFile = ribbonBar()->addSystemButton(/*iconLogo,*/ QString::fromLocal8Bit("文件")))
	{
		ribbonBar()->getSystemButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

		m_actionOpenFile = new QAction(QIcon(m_strResPath + "_openfile.png"), QString::fromLocal8Bit("打开工程"), this);
		//m_actionOpenFile->setShortcut(QKeySequence::Open);
		m_actionOpenFile->setToolTip(tr("Open"));
		m_actionOpenFile->setStatusTip(tr("Open an existing document"));
		connect(m_actionOpenFile, SIGNAL(triggered()), this, SLOT(fileOpen()));

		m_actionFileNew = new QAction(QIcon(m_strResPath + "_newfile.png"), QString::fromLocal8Bit("新建工程"), this);
		//m_actionFileNew->setShortcut(QKeySequence::Open);
		//m_actionFileNew->setToolTip(tr("Open"));
		//m_actionFileNew->setStatusTip(tr("Open an existing document"));
		//connect(m_actionFileNew, SIGNAL(triggered()), this, SLOT(fileNew()));

		m_actionSaveFile = new QAction(QIcon(m_strResPath + "_savefile.png"), QString::fromLocal8Bit("保存工程"), this);
		//m_actionSaveFile->setShortcut(QKeySequence::Save);
		m_actionSaveFile->setToolTip(tr("Save"));
		m_actionSaveFile->setStatusTip(tr("Save the active document"));
		m_actionSaveFile->setEnabled(false);
		connect(m_actionSaveFile, SIGNAL(triggered()), this, SLOT(fileSave()));

		actionFile->setToolTip(tr("Click here to see everything you can do with your document"));
		Qtitan::RibbonSystemPopupBar* popupBar = qobject_cast<Qtitan::RibbonSystemPopupBar*>(actionFile->menu());

		popupBar->addAction(m_actionFileNew);
		popupBar->addAction(m_actionOpenFile);
		popupBar->addAction(m_actionSaveFile);

		QAction* actionSaveAsFile = popupBar->addAction(QIcon(m_strResPath + "_saveas.png"), QString::fromLocal8Bit("工程另存为"));
		actionSaveAsFile->setPriority(QAction::LowPriority);
		actionSaveAsFile->setToolTip(tr("Save As"));
		actionSaveAsFile->setStatusTip(tr("Save the active document with a new name"));
		connect(actionSaveAsFile, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

		popupBar->addSeparator();
		QAction* actionClose = popupBar->addAction(QIcon(m_strResPath + "_close"), QString::fromLocal8Bit("退出"));
		//actionClose->setShortcut(tr("Ctrl+C"));
		actionClose->setStatusTip(tr("Exit"));
		actionClose->setEnabled(true);

		connect(actionClose, SIGNAL(triggered()), this, SLOT(close()));

	}
}

void MainWindow::createGroupAnnotation(Qtitan::RibbonPage* page)
{
	if (Qtitan::RibbonGroup* groupClipboard = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("标注标绘")))
	{
		groupClipboard->setOptionButtonVisible(false);

		QAction* pActionPoint = groupClipboard->addAction(QIcon(m_strResPath + "_point.png"), QString::fromLocal8Bit("点"), Qt::ToolButtonTextUnderIcon);
		RibbonControl* control = groupClipboard->controlByAction(pActionPoint);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		QAction* pActionLine = groupClipboard->addAction(QIcon(m_strResPath + "_line.png"), QString::fromLocal8Bit("线"), Qt::ToolButtonTextUnderIcon);
		control = groupClipboard->controlByAction(pActionLine);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		QAction* pActionPolygon = groupClipboard->addAction(QIcon(m_strResPath + "_polygon.png"), QString::fromLocal8Bit("多边形"), Qt::ToolButtonTextUnderIcon);
		control = groupClipboard->controlByAction(pActionPolygon);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		QAction* pActionEllipse = groupClipboard->addAction(QIcon(m_strResPath + "_ellipse.png"), QString::fromLocal8Bit("椭圆"), Qt::ToolButtonTextUnderIcon);
		control = groupClipboard->controlByAction(pActionEllipse);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		m_vecAnnoAction.push_back(pActionPoint);
		m_vecAnnoAction.push_back(pActionLine);
		m_vecAnnoAction.push_back(pActionPolygon);
		m_vecAnnoAction.push_back(pActionEllipse);
		_annotationToolbar = new osgEarth::QtGui::AnnotationToolbar(m_vecAnnoAction, _annoRoot, _mapNode, _manager);
		//addToolBar(_annotationToolbar);

		for (int i = 0; i < m_vecAnnoAction.size(); i ++)
		{
			QObject::connect(m_vecAnnoAction[i], SIGNAL(triggered()), this, SLOT(slotAnnoAdding()));
		}

		QObject::connect(_annotationToolbar, SIGNAL(sigAddFinished()), this, SLOT(slotAnnoAddFinished()));
	}
}

void MainWindow::createGroupSky(Qtitan::RibbonPage* page)
{
	if (Qtitan::RibbonGroup* groupSky = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("星空")))
	{
		QDateTimeEdit* pDataTimeEdit = new QDateTimeEdit;
		pDataTimeEdit->setDateTime(QDateTime::currentDateTime());
		pDataTimeEdit->setDisplayFormat("yyyy/MM/dd  hh : mm : ss");

		pDataTimeEdit->setCalendarPopup(true);

		QAction* pActionTime = groupSky->addWidget(QIcon(), QString::fromLocal8Bit("设定时间"), pDataTimeEdit);
		RibbonControl* control = groupSky->controlByAction(pActionTime);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
 
 		QObject::connect(pDataTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(slotDataTimeChanged(const QDateTime&)));
// 		//groupSky->addWidget(new QLabel("设定时间"));
	}
}

void MainWindow::slotSetCameraPos()
{
	m_pCameraPosDlg->show();
}

extern osgEarth::Util::SkyNode* s_sky;

void MainWindow::slotSliderHourChanged(int nValue)
{
	osgEarth::DateTime dataTime = s_sky->getDateTime();
	s_sky->setDateTime(osgEarth::DateTime(dataTime.year(), dataTime.month(), dataTime.day(), nValue));
}

void MainWindow::slotDataTimeChanged(const QDateTime& dataTime)
{
	double dHour = dataTime.time().hour() + dataTime.time().minute() / 60.0 + dataTime.time().second() / 3600.0;
	s_sky->setDateTime(osgEarth::DateTime(dataTime.date().year(), dataTime.date().month(), dataTime.date().day(), dHour));
}

void MainWindow::slotAnnoAdding()
{
	for (int i = 0; i < m_vecAnnoAction.size(); i ++)
	{
		m_vecAnnoAction[i]->setEnabled(false);
	}
}

void MainWindow::slotAnnoAddFinished()
{
	for (int i = 0; i < m_vecAnnoAction.size(); i++)
	{
		m_vecAnnoAction[i]->setEnabled(true);
	}
}

QDialog* g_pDetectToolDlg = NULL;
QTextEdit* g_pTextEdit = NULL;
void MainWindow::slotDetectTool()
{
	if (g_pDetectToolDlg == NULL)
	{
		g_pDetectToolDlg = new QDialog(this);
		QHBoxLayout* pHLayout = new QHBoxLayout;
		g_pTextEdit = new QTextEdit;
		pHLayout->addWidget(g_pTextEdit);
		g_pDetectToolDlg->setLayout(pHLayout);
		g_pDetectToolDlg->setWindowTitle(QString::fromLocal8Bit("探针工具"));
	}

	//if (bCheck)
	{
		g_pDetectToolDlg->show();
	}
}

void MainWindow::slotRefresh()
{
	_manager->MapNode()->getTerrainEngine()->dirtyTerrain();
}

void MainWindow::createRibbon()
{
	m_pageHome = ribbonBar()->addPage(QString::fromLocal8Bit("主面板"));
	if (m_pageHome)
	{
		createGroupRadioData(m_pageHome);
		createGroupTemperatureData(m_pageHome);
		createGroupTool(m_pageHome);
		createGroupAirData(m_pageHome);
		createGroupRenderPara(m_pageHome);
		createGroupDataManager(m_pageHome);
		//createGroupFont(m_pageHome);
		createGroupAnnotation(m_pageHome);

		createGroupSky(m_pageHome);
	}

	m_pageLayout = ribbonBar()->addPage(QString::fromLocal8Bit("窗口布局"));
	if (m_pageLayout)
	{
		createGroupDocumentViews(m_pageLayout->addGroup(QString::fromLocal8Bit("窗口布局")));
	}
}

void MainWindow::createGroupRadioData(Qtitan::RibbonPage* page)
{
	Qtitan::RibbonGroup* groupRadioData = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("辐射数据"));

	m_pActionAddModisRadioLayer = groupRadioData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("加载modis辐射数据"), Qt::ToolButtonTextUnderIcon);
	m_pActionAddModisRadioLayer->setToolTip(QString::fromLocal8Bit("加载modis辐射数据"));
	connect(m_pActionAddModisRadioLayer, SIGNAL(triggered()), this, SLOT(addModisRadioLayer()));
	m_pActionAddModisRadioLayer->setDisabled(!_manager.valid());

	RibbonControl* control = groupRadioData->controlByAction(m_pActionAddModisRadioLayer);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
}

void MainWindow::createGroupTemperatureData(Qtitan::RibbonPage* page)
{
	Qtitan::RibbonGroup* groupTemperatureData = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("温度数据"));

	QAction* pAddModisTemperatureLayer = groupTemperatureData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("加载modis温度数据"), Qt::ToolButtonTextUnderIcon);
	pAddModisTemperatureLayer->setToolTip(QString::fromLocal8Bit("加载modis温度数据"));
	connect(pAddModisTemperatureLayer, SIGNAL(triggered()), this, SLOT(addModisTemperatureLayer()));
	pAddModisTemperatureLayer->setDisabled(!_manager.valid());
}

void MainWindow::createGroupTool(Qtitan::RibbonPage* page)
{
	Qtitan::RibbonGroup* groupTool = page->addGroup(QString::fromLocal8Bit("工具"));
	g_pActionDetectTool = groupTool->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("探针"), Qt::ToolButtonTextUnderIcon);
	//g_pActionDetectTool->setCheckable(true);

	connect(g_pActionDetectTool, SIGNAL(triggered()), this, SLOT(slotDetectTool()));
}

void MainWindow::createGroupAirData(Qtitan::RibbonPage* page)
{
	Qtitan::RibbonGroup* groupAirData = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("大气数据"));

	m_pActionAddAirData = groupAirData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("加载大气数据"), Qt::ToolButtonTextUnderIcon);
	m_pActionAddAirData->setToolTip(QString::fromLocal8Bit("加载大气数据"));
	connect(m_pActionAddAirData, SIGNAL(triggered()), this, SLOT(addAirData()));
	m_pActionAddAirData->setDisabled(!_manager.valid());

	RibbonControl* control = groupAirData->controlByAction(m_pActionAddAirData);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
	control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

// 	QAction* pUnloadAirData = groupAirData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("卸载大气数据"), Qt::ToolButtonTextUnderIcon);
// 	pUnloadAirData->setToolTip(QString::fromLocal8Bit("卸载大气数据"));
// 	connect(pUnloadAirData, SIGNAL(triggered()), this, SLOT(UnloadAirData()));
// 	pUnloadAirData->setDisabled(!_manager.valid()
}

void MainWindow::createGroupRenderPara(Qtitan::RibbonPage* page)
{
	Qtitan::RibbonGroup* groupAirData = page->addGroup(QString::fromLocal8Bit("渲染参数"));

	QAction* pActionRenderMode = groupAirData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("颜色模式"), Qt::ToolButtonTextUnderIcon);
	connect(pActionRenderMode, SIGNAL(triggered()), this, SLOT(slotSetRenderMode()));

	QAction* pActionRefresh = groupAirData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("刷新"), Qt::ToolButtonTextUnderIcon);
	connect(pActionRefresh, SIGNAL(triggered()), this, SLOT(slotRefresh()));

	QAction* pActionFixedAngleMode = groupAirData->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("定点模式"), Qt::ToolButtonTextUnderIcon);
	connect(pActionFixedAngleMode, SIGNAL(triggered(bool)), this, SLOT(slotFixedAngleMode(bool)));
	pActionFixedAngleMode->setCheckable(true);
}

void MainWindow::createGroupDataManager(Qtitan::RibbonPage* page)
{
	if (Qtitan::RibbonGroup* groupClipboard = page->addGroup(/*::qtnIcon(Image_Clipboard),*/ QString::fromLocal8Bit("数据管理")))
	{
		{
			QAction* pActionCameraPos = groupClipboard->addAction(QIcon(m_strResPath + "_cameraPos.png"), QString::fromLocal8Bit("传感器参数"), Qt::ToolButtonTextUnderIcon);
			pActionCameraPos->setToolTip(QString::fromLocal8Bit("传感器参数"));

			RibbonControl* control1 = groupClipboard->controlByAction(pActionCameraPos);
			control1->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
			control1->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
			control1->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

			connect(pActionCameraPos, SIGNAL(triggered()), this, SLOT(slotSetCameraPos()));
		}

		groupClipboard->setOptionButtonVisible(false);
// 		QAction* act = groupClipboard->optionButtonAction();
// 		act->setText(tr("Clipboard"));
// 		act->setIcon(QIcon(m_strResPath + "clipboardToolTip.png"));
// 		act->setToolTip(tr("Show the Office clipboard Task Pane"));
// 		act->setStatusTip(tr("Show the Office clipboard Task Pane"));

		m_pActionAddTargetData = groupClipboard->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("目标数据"), Qt::ToolButtonTextUnderIcon);
		m_pActionAddTargetData->setToolTip(QString::fromLocal8Bit("加载目标数据"));
		connect(m_pActionAddTargetData, SIGNAL(triggered()), this, SLOT(addTargetData()));
		m_pActionAddTargetData->setDisabled(!_manager.valid());

		RibbonControl* control = groupClipboard->controlByAction(m_pActionAddTargetData);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

// 		QAction* pActionLoadTargetDataJet = groupClipboard->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("加载尾焰"), Qt::ToolButtonTextUnderIcon);
// 		pActionLoadTargetDataJet->setToolTip(QString::fromLocal8Bit("加载尾焰"));
// 		connect(pActionLoadTargetDataJet, SIGNAL(triggered()), this, SLOT(addTargetDataJet()));
// 		pActionLoadTargetDataJet->setDisabled(!_manager.valid());

		//输出图像
		QAction* pActionOutput = groupClipboard->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("导出图片"), Qt::ToolButtonTextUnderIcon);
		pActionOutput->setToolTip(QString::fromLocal8Bit("导出图片"));
		connect(pActionOutput, SIGNAL(triggered()), this, SLOT(Output()));
		pActionOutput->setDisabled(!_manager.valid());


		//目标转plt
		QAction* pActionTarget2Plt = groupClipboard->addAction(QIcon(m_strResPath + "_loadimg.png"), QString::fromLocal8Bit("目标转plt"), Qt::ToolButtonTextUnderIcon);
		pActionTarget2Plt->setToolTip(QString::fromLocal8Bit("目标转plt"));
		connect(pActionTarget2Plt, SIGNAL(triggered()), this, SLOT(Target2plt()));
		pActionTarget2Plt->setDisabled(!_manager.valid());

		QAction* pActionAddModel = groupClipboard->addAction(QIcon(m_strResPath + "_addModel.png"), QString::fromLocal8Bit("模型"), Qt::ToolButtonTextUnderIcon);
		pActionAddModel->setToolTip(QString::fromLocal8Bit("加载模型"));
		connect(pActionAddModel, SIGNAL(triggered()), this, SLOT(addModelLayer()));
		pActionAddModel->setDisabled(!_manager.valid());

		control = groupClipboard->controlByAction(pActionAddModel);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		_addAnnotationAction = groupClipboard->addAction(QIcon(m_strResPath + "_loadanno.png"), QString::fromLocal8Bit("标注"), Qt::ToolButtonTextUnderIcon);
		_addAnnotationAction->setToolTip(tr("Add an annotation"));
		connect(_addAnnotationAction, SIGNAL(triggered()), this, SLOT(addAnnotation()));
		_addAnnotationAction->setDisabled(!_manager.valid() || !_mapNode.valid() || !_annoRoot.valid());

		control = groupClipboard->controlByAction(_addAnnotationAction);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);

		_terrainProfileAction = groupClipboard->addAction(QIcon(m_strResPath + "_profile.png"), QString::fromLocal8Bit("地形分析"), Qt::ToolButtonTextUnderIcon);
		_terrainProfileAction->setToolTip(tr("Terrain Profile Tool"));
		_terrainProfileAction->setCheckable(true);
		connect(_terrainProfileAction, SIGNAL(toggled(bool)), this, SLOT(terrainProfileToggled(bool)));

		control = groupClipboard->controlByAction(_terrainProfileAction);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupLarge)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupMedium)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
		control->sizeDefinition(RibbonControlSizeDefinition::GroupSmall)->setImageSize(RibbonControlSizeDefinition::ImageLarge);
	}
}
