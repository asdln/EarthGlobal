#include "RangeFeatureGenerator.h"
#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/LineSymbol>
#include <osgEarthSymbology/PolygonSymbol>
#include <osgEarthSymbology/AltitudeSymbol>
#include <osgEarthSymbology/Color>

#include "osgEarth/DataParaManager.h"
#include "osgEarth/ColorTransform.h"
#include <osgEarthUtil/EarthManipulator>
#include <QtCore/QtMath>
#include <QtWidgets/QMdiSubWindow>
#include "AnimationController.h"

#include <osg/Texture2D>

#include "line2atmosphere.h"

extern osgViewer::Viewer* g_viewerEagleEye;
extern osgViewer::Viewer* g_viewerMain;

#define RASTER_LINEBYTES(w, d) ( (w * d + 31) / 32 * 4 )

osg::Camera* createHUDBg1(std::string imagePath)
{
	osg::ref_ptr<osg::Camera>camera = new osg::Camera;
	camera->setProjectionMatrixAsOrtho2D(0, 800, 0, 600);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setRenderOrder(osg::Camera::PRE_RENDER);
	camera->setViewport(0, 0, 1300, 800);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setAllowEventFocus(false);
	camera->setViewMatrix(osg::Matrix::identity());

	osg::ref_ptr<osg::Geode>geode = new osg::Geode;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::Geometry>gm = new osg::Geometry;

	//亚入顶点
	osg::ref_ptr<osg::Vec3Array>vertex = new osg::Vec3Array;
	vertex->push_back(osg::Vec3(0, 0, 0));
	vertex->push_back(osg::Vec3(800, 0, 0));
	vertex->push_back(osg::Vec3(800, 600, 0));
	vertex->push_back(osg::Vec3(0, 600, 0));
	gm->setVertexArray(vertex);

	//压入法线

	//纹理坐标
	osg::ref_ptr<osg::Vec2Array>coord = new osg::Vec2Array;
	coord->push_back(osg::Vec2(0, 0));
	coord->push_back(osg::Vec2(1, 0));
	coord->push_back(osg::Vec2(1, 1));
	coord->push_back(osg::Vec2(0, 1));
	gm->setTexCoordArray(0, coord);
	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Image>image = osgDB::readImageFile(imagePath);
	if(!image.valid())
	{
		return camera.release();
	}

	osg::Texture2D*t2d = new osg::Texture2D;
	t2d->setImage(0, image);

	gm->getOrCreateStateSet()->setTextureAttributeAndModes(0, t2d, osg::StateAttribute::ON);
	geode->addDrawable(gm);
	camera->addChild(geode);
	return camera.release();
}

RangeFeatureGenerator::RangeFeatureGenerator(osgEarth::QtGui::ViewerWidget* pWidget, osg::Group*rootMain, osg::Group* rootEagleEye, osgEarth::MapNode* pMapNodeMain, osgEarth::MapNode* pMapNodeEye)
: _mapNodeMain(pMapNodeMain), _mapNodeEye(pMapNodeEye)
{
	m_pWidget = pWidget;

	osgEarth::Symbology::Style polyStyle;
// 	polyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->color() = osgEarth::Symbology::Color(0.0, 1.0, 0.0, 0.5);
// 	polyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->width() = 1.0;
//	polyStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->tessellation() = 20;
	polyStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()->fill()->color() = osgEarth::Symbology::Color(1.0, .0, 0.0, 0.5);
	polyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	//if (_drapeCheckbox->checkState() == Qt::Checked)
	{
		polyStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	}

	_polygon = new osgEarth::Symbology::Polygon();
	_polyFeature = new osgEarth::Features::Feature(_polygon, _mapNodeEye->getMapSRS(), polyStyle);

	_polyNode = new osgEarth::Annotation::FeatureNode(_mapNodeEye, _polyFeature);

	osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();
	annoData->setName("123");
	annoData->setViewpoint(osgEarth::Viewpoint("Random", 0.0, 0.0, 10000.0, 0.0, -90.0, 1e5));
	_polyNode->setAnnotationData(annoData);

	rootEagleEye->addChild(_polyNode);
	QObject::connect(&m_timerRangeFeature, SIGNAL(timeout()), this, SLOT(BulidFeature()));

	int nWid = m_pWidget->rect().width();
	int nHei = m_pWidget->rect().height();

	osgViewer::ViewerBase::Cameras cameras;
	m_pWidget->getViewer()->getCameras(cameras);

	if(cameras.empty()) return;

	osg::Camera* pCamera = cameras[0];
	pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

 	m_pHudCamera = new osg::Camera;
 	m_pHudCamera->setProjectionMatrixAsOrtho2D(0, nWid, 0, nHei);
 	m_pHudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
 	m_pHudCamera->setRenderOrder(osg::Camera::PRE_RENDER);
	m_pHudCamera->setViewport(0, 0, nWid, nHei);
 	m_pHudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
 	m_pHudCamera->setAllowEventFocus(false);
 	m_pHudCamera->setViewMatrix(osg::Matrix::identity());
 
	m_pCurrentGeode = createHUDBg(nWid, nHei);
 	m_pHudCamera->addChild(m_pCurrentGeode);
 
 	rootMain->addChild(m_pHudCamera);
	m_nBackgroundWid = nWid;
	m_nBackgroundHei = nHei;
}

RangeFeatureGenerator::~RangeFeatureGenerator()
{

}

osg::Geode* RangeFeatureGenerator::createHUDBg(int nWid, int nHei)
{
	osgViewer::ViewerBase::Cameras cameras;
	m_pWidget->getViewer()->getCameras(cameras);

	if(cameras.empty()) return NULL;

	osg::Camera* pCamera = cameras[0];
	osg::Matrix matrix(pCamera->getViewMatrix() * pCamera->getProjectionMatrix());

	if(pCamera->getViewport())
		matrix.postMult(pCamera->getViewport()->computeWindowMatrix());

	osg::Matrix inverseMVPW;
	inverseMVPW.invert(matrix);

	osg::Vec3d eye;
	osg::Vec3d center;
	osg::Vec3d up;

	pCamera->getViewMatrixAsLookAt(eye, center, up);

	//状态变量 flag 0  为视线与大气没有交点
	//1 为视线与大气层顶只有一个交点
	//2 视线与大气有两个交点与地表没有交点
	//3 视线与大气有两个交点与地表一个交点
	//4 视线与大气两个交点与地表两个交点

	int nLineBytes = nWid * 3/*RASTER_LINEBYTES(nWid, 24)*/;
	uchar* pBuffer = new uchar[nLineBytes * nHei];

	DataParaManager* pDataParaManager = DataParaManager::Instance();
	double dMin = pDataParaManager->GetRadioMin();
	double dMax = pDataParaManager->GetRadioMax();

	if (pDataParaManager->IsFixedAngleMode())
	{
		for (int j = 0; j < nHei; j++)
		{
			uchar* pBytesLine = pBuffer + j * nLineBytes;

			for (int i = 0; i < nWid; i++)
			{
				osg::Vec3 near_point = osg::Vec3(i, j, 0.0f) * inverseMVPW;
				osg::Vec3 far_point = osg::Vec3(i, j, 1.0) * inverseMVPW;

				double dAirLon, dAirLat, dLandLon, dLandLat;
				int nRes = line2atmosphereXYZ(eye.x(), eye.y(), eye.z(),
					far_point.x(), far_point.y(), far_point.z(), 99000.0,
					&dAirLon, &dAirLat,
					&dLandLon, &dLandLat, 5);
				{
					double dRadio = 0.0;
					double dTrans = 1.0;

					pDataParaManager->GetAirValue(dAirLon, dAirLat, dRadio, dTrans);

					double dValue = dRadio;
					unsigned char nR = 255;
					unsigned char nG = 255;
					unsigned char nB = 255;

					if (dRadio != 0.0)
					{
						int x = 0;
					}

					if (pDataParaManager->IsRGBMode())
					{
						ColorTransform::Gray2RGB(dMin, dMax, dValue, nR, nG, nB);
					}
					else
					{
						if (dValue < dMin)
						{
							nR = 0;
						}
						else if (dValue > dMax)
						{
							nR = 255;
						}
						else
						{
							nR = (dValue - dMin) / (dMax - dMin) * 256.0;
						}

						nG = nR;
						nB = nR;
					}

					*(pBytesLine + i * 3) = nR;
					*(pBytesLine + i * 3 + 1) = nG;
					*(pBytesLine + i * 3 + 2) = nB;
				}
			}
		}
	}
	else
	{
		memset(pBuffer, 0, nLineBytes * nHei);
	}

 	osg::Image* pOsgImage = new osg::Image;
 	pOsgImage->setImage(nWid, nHei, 1, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, pBuffer, osg::Image::USE_NEW_DELETE);
	osg::ref_ptr<osg::Geode>geode = new osg::Geode;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::Geometry>gm = new osg::Geometry;

	//亚入顶点
	osg::ref_ptr<osg::Vec3Array>vertex = new osg::Vec3Array;
	vertex->push_back(osg::Vec3(0, 0, 0));
	vertex->push_back(osg::Vec3(nWid - 1, 0, 0));
	vertex->push_back(osg::Vec3(nWid - 1, nHei - 1, 0));
	vertex->push_back(osg::Vec3(0, nHei - 1, 0));
	gm->setVertexArray(vertex);

	//纹理坐标
	osg::ref_ptr<osg::Vec2Array>coord = new osg::Vec2Array;
	coord->push_back(osg::Vec2(0, 0));
	coord->push_back(osg::Vec2(1, 0));
	coord->push_back(osg::Vec2(1, 1));
	coord->push_back(osg::Vec2(0, 1));
	gm->setTexCoordArray(0, coord);
	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Image>image = pOsgImage;
	osg::Texture2D*t2d = new osg::Texture2D;
	t2d->setImage(0, image);

	gm->getOrCreateStateSet()->setTextureAttributeAndModes(0, t2d, osg::StateAttribute::ON);
	geode->addDrawable(gm);
	return geode.release();
}

extern QMdiSubWindow* g_pMdiSubWindow;
bool g_bRefreshRange = 1;

void RangeFeatureGenerator::RefreshRangeFeature()
{
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	osgEarth::Util::EarthManipulator* eagleMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerEagleEye->getCameraManipulator());

	if (mainMani == NULL)
		return;

	osgEarth::Viewpoint vpMain = mainMani->getViewpoint();
	osgEarth::Viewpoint vpEagle = eagleMani->getViewpoint();

	const osgEarth::GeoPoint& pt1 = vpEagle.focalPoint().value();
	const osgEarth::GeoPoint& pt2 = vpMain.focalPoint().value();

	double dx1 = pt1.x();
	double dy1 = pt1.y();
	double dz1 = pt1.z();

	double dHeading1 = vpEagle.heading().value().getValue();
	double dPitch1 = vpEagle.pitch().value().getValue();
	double dRange1 = vpEagle.range().value().getValue();

	static double s_dx1 = dx1;
	static double s_dy1 = dy1;
	static double s_dz1 = dz1;

	static double s_dHeading1 = dHeading1;
	static double s_dPitch1 = dPitch1;
	static double s_dRange1 = dRange1;

	bool bChanged1 = false;
	if (qFabs(s_dx1 - dx1) > 0.0000001
		|| qFabs(s_dy1 - dy1) > 0.0000001
		|| qFabs(s_dz1 - dz1 > 0.0000001)
		|| qFabs(s_dHeading1 - dHeading1) > 0.0000001
		|| qFabs(s_dPitch1 - dPitch1) > 0.0000001
		|| qFabs(s_dRange1 - dRange1))
	{
		bChanged1 = true;

		s_dx1 = dx1;
		s_dy1 = dy1;
		s_dz1 = dz1;

		s_dHeading1 = dHeading1;
		s_dPitch1 = dPitch1;
		s_dRange1 = dRange1;
	}

	double dx2 = pt2.x();
	double dy2 = pt2.y();
	double dz2 = pt2.z();

	double dHeading2 = vpMain.heading().value().getValue();
	double dPitch2 = vpMain.pitch().value().getValue();
	double dRange2 = vpMain.range().value().getValue();

	static double s_dx2 = dx2;
	static double s_dy2 = dy2;
	static double s_dz2 = dz2;

	static double s_dHeading2 = dHeading2;
	static double s_dPitch2 = dPitch2;
	static double s_dRange2 = dRange2;

	bool bChanged2 = false;
	if (qFabs(s_dx2 - dx2) > 0.0000001
		|| qFabs(s_dy2 - dy2) > 0.0000001
		|| qFabs(s_dz2 - dz2 > 0.0000001)
		|| qFabs(s_dHeading2 - dHeading2) > 0.0000001
		|| qFabs(s_dPitch2 - dPitch2) > 0.0000001
		|| qFabs(s_dRange2 - dRange2))
	{
		bChanged2 = true;

		s_dx2 = dx2;
		s_dy2 = dy2;
		s_dz2 = dz2;

		s_dHeading2 = dHeading2;
		s_dPitch2 = dPitch2;
		s_dRange2 = dRange2;
	}

	static int nWinWid = g_pMdiSubWindow->rect().width();
	static int nHeight = g_pMdiSubWindow->rect().height();

	if (bChanged1 || bChanged2)
	{
		g_bRefreshRange = 1;
		m_timerRangeFeature.start(500);
		//RefreshBackgroundTexture();
	}

	if (nWinWid != g_pMdiSubWindow->rect().width() || nHeight != g_pMdiSubWindow->rect().height())
	{
		g_bRefreshRange = 0;
		m_timerRangeFeature.start(500);

		nWinWid = g_pMdiSubWindow->rect().width();
		nHeight = g_pMdiSubWindow->rect().height();
		//RefreshBackgroundTexture();
	}

	std::vector<osgViewer::View*> vecViews;
	g_viewerMain->getViews(vecViews);
	osgViewer::View* pView = vecViews[0];

	osg::Camera* pCamera = pView->getCamera();
	osg::Viewport* pViewPort = pCamera->getViewport();

	static double g_dViewPortWid = 0.0;
	static double g_dViewPortHei = 0.0;

	static int g_nWinWid = 0;
	static int g_nWinHei = 0;

	double dViewPortWid = pViewPort->width();
	double dViewPortHei = pViewPort->height();

	if (g_dViewPortWid != dViewPortWid
		|| g_dViewPortHei != dViewPortHei)
	{
		g_dViewPortWid = dViewPortWid;
		g_dViewPortHei = dViewPortHei;

		g_bRefreshRange = 0;
		m_timerRangeFeature.start(500);
	}
}

void RangeFeatureGenerator::RefreshBackgroundTexture()
{
	int nWid = m_pWidget->rect().width();
	int nHei = m_pWidget->rect().height();

	m_nBackgroundWid = nWid;
	m_nBackgroundHei = nHei;

	m_pHudCamera->setProjectionMatrixAsOrtho2D(0, nWid, 0, nHei);
	m_pHudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_pHudCamera->setRenderOrder(osg::Camera::PRE_RENDER);
	m_pHudCamera->setViewport(0, 0, nWid, nHei);
	m_pHudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	m_pHudCamera->setAllowEventFocus(false);
	m_pHudCamera->setViewMatrix(osg::Matrix::identity());

	int nNum = m_pHudCamera->getNumChildren();

	m_pHudCamera->removeChild(m_pCurrentGeode);

	m_pCurrentGeode = createHUDBg(nWid, nHei);
	m_pHudCamera->addChild(m_pCurrentGeode);
}

void RangeFeatureGenerator::BulidFeature()
{
	if (g_bRefreshRange)
	{
		_polygon->clear();

		std::vector<osgViewer::View*> vecViews;
		g_viewerMain->getViews(vecViews);
		osgViewer::View* pView = vecViews[0];

		QWidget* pWidget = dynamic_cast<QWidget*>(m_pWidget);
		QRect rect = pWidget->geometry();
		int nWid = rect.width();
		int nHei = rect.height();

		int nGridSize = 10;

		osg::Vec3d world;
		osgEarth::GeoPoint mapPoint;
		if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), 0.0, 0.0, world))
		{
			mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
			_polygon->push_back(mapPoint.vec3d());
		}

		int nCountHor = (nWid - 1) / nGridSize;
		for (int i = 0; i < nCountHor; i++)
		{
			if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), i * nGridSize, 0.0, world))
			{
				mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
				_polygon->push_back(mapPoint.vec3d());
			}
		}

		if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), nWid - 1, 0.0, world))
		{
			mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
			_polygon->push_back(mapPoint.vec3d());
		}

		int nCountVer = (nHei - 1) / nGridSize;
		for (int i = 0; i < nCountVer; i++)
		{
			if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), nWid - 1, i * nGridSize, world))
			{
				mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
				_polygon->push_back(mapPoint.vec3d());
			}
		}

		if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), nWid - 1, nHei - 1, world))
		{
			mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
			_polygon->push_back(mapPoint.vec3d());
		}

		for (int i = 0; i < nCountHor; i++)
		{
			if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), nWid - 1 - i * nGridSize, nHei - 1, world))
			{
				mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
				_polygon->push_back(mapPoint.vec3d());
			}
		}

		if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), 0.0, nHei - 1, world))
		{
			mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
			_polygon->push_back(mapPoint.vec3d());
		}

		for (int i = 0; i < nCountVer; i++)
		{
			if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), 0, nHei - 1 - i * nGridSize, world))
			{
				mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
				_polygon->push_back(mapPoint.vec3d());
			}
		}

		if (_mapNodeMain->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), 0.0, 0.0, world))
		{
			mapPoint.fromWorld(_mapNodeMain->getMapSRS(), world);
			_polygon->push_back(mapPoint.vec3d());
		}

		_polyNode->setFeature(_polyFeature);
	}

	//在动画输出时不在此处进行背景图的更新。在Camera的控制器进行更新
	if (!AnimationController::IsPathFrameRunning())
		RefreshBackgroundTexture();

	m_timerRangeFeature.stop();
}