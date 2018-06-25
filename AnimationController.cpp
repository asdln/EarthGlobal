#include "AnimationController.h"
#include "Document.h"
#include <osgViewer/Viewer>
#include <osg/AnimationPath>
#include <osgEarthUtil/EarthManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgEarthQt/Common>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthQt/DataManager>
#include "ScreenCapture.h"
#include "OEAnimationPath.h"
#include "osgEarthQt/ViewerWidget"
#include "TargetAnimationPathCallback.h"
#include "JetHideCallback.h"
#include "PathEarthManipulate.h"

#include <QtWidgets/QFileDialog>
#include "AnimationLoader.h"

#include "SysUtility.h"
#include "osgEarth/DataParaManager.h"
#include "AirDataReader.h"
#include <QtWidgets/QProgressDialog>
#include "SetStartFrameDlg.h"

extern osgViewer::Viewer* g_viewerMain;
extern osgEarth::QtGui::DataManager* g_DataManager;
extern osgEarth::QtGui::ViewerWidget* g_viewerWidget;
extern osg::ref_ptr<osg::Group> s_annoGroup;

extern QProgressDialog* g_ProgressDialog;

CScreenCapture::WriteToImageFile* g_pCaptureOperation = NULL;
extern CScreenCapture* g_pScreenCapture;

int g_CaptureFrameIndex = -1;
int g_OutPutFrameCount = 1;
int g_nStartFrameIndex = 0;

QMutex g_ErrorLogmutex;

extern osgEarth::Features::Feature* GetAirFeature(double dTransparent);

AnimationController::AnimationController()
{

}

AnimationController::~AnimationController()
{
	AnimationController* pInstance = Instance();
	if (pInstance)
	{
		delete pInstance;
	}
}

void AnimationController::LoadCameraPath(const QString& strPath)
{
	m_strCameraAnimationPath = strPath;
	m_ptrCameraAnimationPath = AnimationLoader::LoadCameraPath(strPath);
}

void AnimationController::LoadTargetPath(const QString& strPath)
{
	m_strTargetAnimationPath = strPath;
	m_ptrTargetAnimationPath = AnimationLoader::LoadTargetPath(strPath);
}

void AnimationController::LoadAirData(const QString& strPath, double dResX, double dResY)
{
	int nWid = 360.0 / dResX;
	int nHei = 180.0 / dResY;

	//if (nWid != nOldWid || nHei != nOldHei)
	{
		DataParaManager::Instance()->SetSize(nWid, nHei);
	}

	//清空之前数据
	DataParaManager* pAirDataBuffer = DataParaManager::Instance();
	pAirDataBuffer->ResetValue();

	AirDataReader reader;
 	reader.AddData(strPath);

	if (!DataParaManager::Instance()->IsFixedAngleMode())
	{
		//只保留一个大气节点。 播放动画时，实时从探测器路径里找到需要加载的大气数据。
		//查找大气节点是否被创建。
		std::vector< osg::ref_ptr<osgEarth::Annotation::AnnotationNode> > annos;
		g_DataManager->getAnnotations(annos);

		osgEarth::Annotation::FeatureNode* pAirNode = NULL;
		for (int i = 0; i < annos.size(); i++)
		{
			osgEarth::Annotation::FeatureNode* pNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(annos[i].get());
			if (!pNode)
				continue;

			if (pNode->getName() == "AirDataNode")
			{
				pAirNode = pNode;
				break;
			}
		}

		osgEarth::Features::Feature* pFeature = GetAirFeature(1.0);
		if (pAirNode == NULL)
		{
			pAirNode = new osgEarth::Annotation::FeatureNode(
				g_DataManager->MapNode(), pFeature);

			pAirNode->setName("AirDataNode");
			g_DataManager->addAnnotation(pAirNode, s_annoGroup);
		}
		else
		{
			pAirNode->setFeature(pFeature);
		}

		osgEarth::Annotation::AnnotationData* pAnnoData = pAirNode->getOrCreateAnnotationData();
		//pAnnoData->setViewpoint(osgEarth::Viewpoint(strPath.toUtf8().data(), reader.m_dy, reader.m_dx, reader.m_dz, 0.0, -90.0, 1e5));
		pAnnoData->setName(strPath.toUtf8().data());
	}
}

void AnimationController::LoadTargetData(const TargetDataPara& para)
{
	TargetDataReader targetReader;
	osg::Vec4Array* pColorArray = NULL;
	osg::Node* pNode = targetReader.GetGeode(para);

	osgEarth::Annotation::Style circleStyle;
	circleStyle.getOrCreate<osgEarth::Annotation::PolygonSymbol>()->fill()->color() = osgEarth::Annotation::Color(osgEarth::Annotation::Color::Red, 0.5);

	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = new osgEarth::Annotation::LocalGeometryNode(g_DataManager->MapNode(), pNode, circleStyle);
	osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();

	std::string strGuid = SysUtility::GetGUIDString();
	TargetDataReader::s_mapPara[strGuid] = para;

	//annoData->setName(QString::fromLocal8Bit("目标数据").toUtf8().data());
	annoData->setName(strGuid);
	annoData->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 10));
	pLocalGeoNode->setAnnotationData(annoData);
	pLocalGeoNode->setPosition(osgEarth::GeoPoint(g_DataManager->MapNode()->getMapSRS()->getGeographicSRS(), osg::Vec3d(para.dx, para.dy, para.dz)));
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

	g_DataManager->addAnnotation(pLocalGeoNode, s_annoGroup);
}

int AnimationController::GetCaptureFrameIndex()
{
	//要加线程锁

	return g_CaptureFrameIndex;
}

void AnimationController::BeginPathFrame(int nStartIndex)
{
	g_CaptureFrameIndex = nStartIndex;
}

void AnimationController::EndPathFrame()
{
	g_CaptureFrameIndex = -1;
}

bool AnimationController::IsPathFrameRunning()
{
	return !(g_CaptureFrameIndex == -1);
}

void AnimationController::CaptureFrameIndexIncrement()
{
	//要加线程锁

	g_CaptureFrameIndex++;
}

void AnimationController::OutputAnimation()
{
	if (0)
	{
		QString strErrorLogPath = Document::Instance()->GetSavePath() + "/StartFrameIndex.txt";
		QFile file(strErrorLogPath);
		if (!file.exists())
		{
			file.open(QIODevice::WriteOnly);
			file.write("0");
			file.close();

			g_nStartFrameIndex = 0;
		}
		else
		{
			file.open(QIODevice::ReadOnly);
			QString str = file.readAll();
			file.close();

			g_nStartFrameIndex = str.toInt();
		}
	}

	StartAnimation();

	std::vector<osgViewer::View*> Views;
	g_viewerMain->getViews(Views);

	if (Views.empty()) return;

	if (g_pCaptureOperation == NULL)
	{
		g_pCaptureOperation = new CScreenCapture::WriteToImageFile("c:\\123.tif", "");
		CScreenCapture* pScreenCapture = new CScreenCapture(g_pCaptureOperation);
		g_pScreenCapture = pScreenCapture;

		Views[0]->addEventHandler(pScreenCapture);
	}

	Document* pDocument = Document::Instance();
	QString strAnimationSavePath = pDocument->GetSavePath();
	CameraPath* pCameraPath = AnimationController::Instance()->GetCameraPath();

	g_pCaptureOperation->setFilePath(strAnimationSavePath.toLocal8Bit().data());

	if(pCameraPath)
	{
		const osg::AnimationPath::TimeControlPointMap& mapCP = pCameraPath->getTimeControlPointMap();
		g_OutPutFrameCount = mapCP.size();
		g_pScreenCapture->setFramesToCapture(g_OutPutFrameCount - g_nStartFrameIndex);

		if (g_nStartFrameIndex >= mapCP.size())
		{
			g_nStartFrameIndex = mapCP.size() - 1;
		}

		//g_OutPutFrameCount = g_OutPutFrameCount - g_nStartFrameIndex;
		AnimationController::BeginPathFrame(g_nStartFrameIndex);

		g_ProgressDialog->setRange(g_nStartFrameIndex, g_OutPutFrameCount - 1);
		g_ProgressDialog->setValue(g_nStartFrameIndex);
	}
	else
	{
		g_pScreenCapture->setFramesToCapture(1);
	}

	Views[0]->getEventQueue()->userEvent(new CaptureEvent);
}

void AnimationController::StartAnimation()
{
	Document* pDocument = Document::Instance();
	CameraPath* pCameraPath = AnimationController::Instance()->GetCameraPath();
	TargetPath* pTargetPath = AnimationController::Instance()->GetTargetPath();

	if(pCameraPath)
	{
		g_viewerMain->setCameraManipulator(new PathEarthManipulate(pCameraPath));
		osg::AnimationPath::TimeControlPointMap& cpMap = pCameraPath->getTimeControlPointMap();
		g_OutPutFrameCount = cpMap.size();
	}

	if(pTargetPath)
	{
		osgEarth::QtGui::AnnotationVector annos;
		g_DataManager->getAnnotations(annos);

		osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = NULL;

		for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
		{

			pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode != nullptr)
				break;
		}

		if (pLocalGeoNode == NULL)
			return;

		osg::MatrixTransform* pMatrixTransform = pLocalGeoNode->getTransform();
		pMatrixTransform->setUpdateCallback(new TargetAnimationPathCallback(pTargetPath));

		osg::Switch* pSwitch = dynamic_cast<osg::Switch*>(pLocalGeoNode->getNode());
		if (pSwitch)
		{
			pSwitch->setUpdateCallback(new JetHideCallback(pTargetPath));
		}
	}
}

void AnimationController::StopAnimation()
{
	DataParaManager::Instance()->SetFixedAngleMode(false);

	g_viewerMain->setCameraManipulator(new osgEarth::Util::EarthManipulator());
	osgEarth::QtGui::AnnotationVector annos;

	g_DataManager->getAnnotations(annos);
	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = NULL;

	for(osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{

		pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
		if(pLocalGeoNode != nullptr)
			break;
	}

	if(pLocalGeoNode == NULL)
		return;

	osg::MatrixTransform* pMatrixTransform = pLocalGeoNode->getTransform();
	pMatrixTransform->setUpdateCallback(nullptr);

	osg::Switch* pSwitch = dynamic_cast<osg::Switch*>(pLocalGeoNode->getNode());
	if (pSwitch)
	{
		pSwitch->setUpdateCallback(nullptr);
	}

	{
		extern double g_dTargetLastLon;
		extern double g_dTargetLastLat;
		extern double g_dTargetLastH;

		pLocalGeoNode->getOrCreateAnnotationData()->setViewpoint(osgEarth::Viewpoint("Random", g_dTargetLastLon, g_dTargetLastLat, g_dTargetLastH, 0.0, -90.0, 10.0));
	}

	//pLocalGeoNode->setUpdateCallback(NULL);
}
