#include "PathEarthManipulate.h"
#include <osgEarthQt/DataManager>
#include <osgEarthAnnotation/LocalGeometryNode>
#include "CameraPath.h"
#include "Document.h"
#include <QtCore/QFileInfo>
#include "AnimationController.h"

extern osgEarth::QtGui::DataManager* g_DataManager;

PathEarthManipulate::PathEarthManipulate(osg::AnimationPath* animationPath)
{
	_animationPath = animationPath;
}

PathEarthManipulate::~PathEarthManipulate()
{

}

osg::Quat
PathEarthManipulate::computeCenterRotation(const osg::Vec3d& point) const
{
	return getRotation(point).getRotate().inverse();
}

bool
PathEarthManipulate::createLocalCoordFrame(const osg::Vec3d& worldPos, osg::CoordinateFrame& out_frame) const
{
	//osg::ref_ptr<const osgEarth::SpatialReference> _srs;

	const osgEarth::SpatialReference* pSrs = g_DataManager->MapNode()->getMapSRS();

	//if(_srs.valid())
	{
		osg::Vec3d mapPos;
		pSrs->transformFromWorld(worldPos, mapPos);
		pSrs->createLocalToWorld(mapPos, out_frame);
	}
	return true;
}

osg::Matrixd
PathEarthManipulate::getRotation(const osg::Vec3d& point) const
{
	//The look vector will be going directly from the eye point to the point on the earth,
	//so the look vector is simply the up vector at the center point
	osg::CoordinateFrame cf;
	createLocalCoordFrame(point, cf);

	osg::Vec3d lookVector = -getUpVector(cf);

	osg::Vec3d side;

	//Force the side vector to be orthogonal to north
	osg::Vec3d worldUp(0, 0, 1);

	double dot = osg::absolute(worldUp * lookVector);
	if(osg::equivalent(dot, 1.0))
	{
		//We are looking nearly straight down the up vector, so use the Y vector for world up instead
		worldUp = osg::Vec3d(0, 1, 0);
	}

	side = lookVector ^ worldUp;
	osg::Vec3d up = side ^ lookVector;
	up.normalize();

	//We want a very slight offset
	double offset = 1e-6;

	return osg::Matrixd::lookAt(point - (lookVector * offset), point, up);
}

void PathEarthManipulate::setVecMatrix(const std::vector<osg::Matrixd>& vecMatrix)
{
	m_vecMatrix = vecMatrix;
}

/** get the position of the manipulator as 4x4 Matrix.*/
osg::Matrixd PathEarthManipulate::getMatrix() const 
{ 
	return _matrix; 
}

/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
osg::Matrixd PathEarthManipulate::getInverseMatrix() const 
{ 
	return osg::Matrixd::inverse(_matrix); 

	int nCircleCount = m_vecMatrix.size();
	static int s_nIndex = 0;

	int nRepeatCount = 100;
	static int s_nRepeatIndex = 0;

	osg::Matrixd matrixd = osg::Matrixd::inverse(m_vecMatrix[s_nIndex]);
	
	s_nRepeatIndex++;

	if (s_nRepeatIndex >= nRepeatCount)
	{
		s_nIndex++;
		s_nRepeatIndex = 0;
	}

	if (s_nIndex >= nCircleCount)
	{
		s_nIndex = 0;
	}

	return matrixd;
}

bool PathEarthManipulate::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if(ea.getEventType() == osgGA::GUIEventAdapter::FRAME)
	{
		osg::Quat _rotation;
		double _distance;
		osg::Quat _centerRotation;
		osg::Vec3d _center;

		/*
		double dTime = ea.getTime();
		double dPeriod = 10.0;
		double dFirstTime = 0.0;

		double modulated_time = (dTime - dFirstTime) / dPeriod;
		double fraction_part = modulated_time - floor(modulated_time);
		dTime = dFirstTime + fraction_part * dPeriod;

		if (dTime < 2.0)
		{
			_distance = 19134411.059656952;

			_rotation[0] = -0.0087265356327607679;
			_rotation[1] = -1.5639032106545497e-016;
			_rotation[2] = 4.4518510566368952e-018;
			_rotation[3] = -0.99996192306299858;

			_centerRotation[0] = 0.70710678110055036;
			_centerRotation[1] = -2.9238220828544497e-016;
			_centerRotation[2] = -2.9238220835655683e-016;
			_centerRotation[3] = 0.70710678127254456;

			_center[0] = -5.5879354554227846e-009;
			_center[1] = -6378136.9401830882;
			_center[2] = 0.0015412736102007329;
		}
		else if(dTime < 4.0)
		{
			_distance = 19137700.860358920;

			_rotation[0] = -0.0087309724024012669;
			_rotation[1] = 1.7370061292099059e-010;
			_rotation[2] = 1.3540456950122959e-011;
			_rotation[3] = -0.99996188433405242;

			_centerRotation[0] = 0.70204559438534053;
			_centerRotation[1] = -0.027086035235416691;
			_centerRotation[2] = -0.027434769332883895;
			_centerRotation[3] = 0.71108766233918796;

			_center[0] = -491045.64515334601;
			_center[1] = -6355390.5541637382;
			_center[2] = 81040.153803617839;
		}
		else if(dTime < 6.0)
		{
			_distance = 19134411.059656952;

			_rotation[0] = 0.0087265356327595519;
			_rotation[1] = -5.0764991434559475e-020;
			_rotation[2] = -5.8170917527241195e-018;
			_rotation[3] = 0.99996192306299869;

			_centerRotation[0] = 0.69208913048527410;
			_centerRotation[1] = -0.070860613490701052;
			_centerRotation[2] = -0.073166627286638988;
			_centerRotation[3] = 0.71458943007251141;

			_center[0] = -1291972.3661655001;
			_center[1] = -6239934.9575732509;
			_center[2] = 202497.67560391151;
		}
		else if(dTime < 8.0)
		{
			_distance = 19134411.059656952;

			_rotation[0] = 0.0087265356327595519;
			_rotation[1] = -5.0764991434559475e-020;
			_rotation[2] = -5.8170917527241195e-018;
			_rotation[3] = 0.99996192306299869;

			_centerRotation[0] = 0.67573824595498821;
			_centerRotation[1] = -0.13353465108227866;
			_centerRotation[2] = -0.14054280984901754;
			_centerRotation[3] = 0.71119198428676966;

			_center[0] = -2423121.9018976865;
			_center[1] = -5890607.9263573810;
			_center[2] = 323865.84232650808;
		}
		else if(dTime < 10.0)
		{
			_distance = 19137462.952538498;

			_rotation[0] = 0.0087455217507741156;
			_rotation[1] = 2.4191010444818417e-009;
			_rotation[2] = 2.2153273937508544e-009;
			_rotation[3] = 0.99996175719339730;

			_centerRotation[0] = 0.66384451863508676;
			_centerRotation[1] = -0.17480824481618648;
			_centerRotation[2] = -0.18517899013377656;
			_centerRotation[3] = 0.70317940401825541;

			_center[0] = -3136360.4216630613;
			_center[1] = -5538264.4208717030;
			_center[2] = 364123.26902817166;
		}

		_centerRotation = computeCenterRotation(_center);

			_matrix = osg::Matrixd::translate(0.0, 0.0, _distance) *
			//osg::Matrixd::rotate(_rotation) *
			osg::Matrixd::rotate(_centerRotation) *
			osg::Matrixd::translate(_center);

			if(m_eCoordType == RightAngle)
			{
				_matrix = osg::Matrixd::rotate(cp.getRotation()) * osg::Matrixd::translate(cp.getPosition());

				//_center = cp.getPosition();
				//_centerRotation = computeCenterRotation(_center);

				//_matrix = osg::Matrixd::rotate(cp.getRotation()) *
				//	osg::Matrixd::rotate(_centerRotation) *
				//	osg::Matrixd::translate(_center);
			}
			else if (m_eCoordType == WGS84)
			{
				const osgEarth::SpatialReference* pSpatialRef = g_DataManager->MapNode()->getMapSRS();
				osgEarth::GeoPoint geoPoint(pSpatialRef, cp.getPosition().x(), cp.getPosition().y(), cp.getPosition().z());

				osg::Vec3d startWorld;
				geoPoint.transform(pSpatialRef).toWorld(startWorld);

				_center = startWorld;
				_centerRotation = computeCenterRotation(_center);

				_matrix = osg::Matrixd::rotate(cp.getRotation()) *
					osg::Matrixd::rotate(_centerRotation) *
					osg::Matrixd::translate(_center);
			}
			*/

			if(_animationPath == NULL)
				return true;

			osg::AnimationPath::ControlPoint cp;
			double animTime = ea.getTime();
			_animationPath->getInterpolatedControlPoint(animTime, cp);

			std::map<double, osg::AnimationPath::ControlPoint>& tcpMap = _animationPath->getTimeControlPointMap();

			// 			osg::Vec3d vec3Pos(cp.getPosition().x(), cp.getPosition().y(), cp.getPosition().z());
			// 			_centerRotation = computeCenterRotation(vec3Pos);
			/*
			_matrix = osg::Matrixd::rotate(cp.getRotation()) *
			//osg::Matrixd::rotate(_centerRotation) *
			osg::Matrixd::translate(vec3Pos);
			*/

			//尝试在动画播放时加载大气数据
			{
				CameraPath* pCameraPath = dynamic_cast<CameraPath*>(_animationPath.get());
				const std::map<double, CameraPathRecord>& mapRecords = pCameraPath->getMapRecords();

				double modulated_time = (animTime - pCameraPath->getFirstTime()) / pCameraPath->getPeriod();
				double fraction_part = modulated_time - floor(modulated_time);
				animTime = pCameraPath->getFirstTime() + fraction_part * pCameraPath->getPeriod();

				std::map<double, CameraPathRecord>::const_iterator second = mapRecords.lower_bound(animTime);
				CameraPathRecord record = second->second;

				if (!record.strAirDataPath.isEmpty())
				{
					Document* pDocument = Document::Instance();
					const QString& strDocumentPath = pDocument->GetAirDataDir();

					QFileInfo fileInfo(strDocumentPath);
					QString strAirPath = fileInfo.absolutePath();
					
					strAirPath = strAirPath + record.strAirDataPath;

					QFileInfo fileInfo2(strAirPath);
					if (fileInfo2.exists())
					{
						AnimationController::Instance()->LoadAirData(strAirPath);
					}
				}
			}

			if (1)
			{
				_matrix = osg::Matrixd::translate(cp.getPosition()) * osg::Matrixd::rotate(cp.getRotation());
			}
			else
			{
				extern osgViewer::Viewer* g_viewerMain;
				osgEarth::QtGui::AnnotationVector out_annotations;
				g_DataManager->getAnnotations(out_annotations);

				osgEarth::Annotation::AnnotationNode* pCurrentAnnotationNode = NULL;
				osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>(out_annotations[0].get());
				if(!pLocalGeoNode)
					return true;

				const osgEarth::SpatialReference* pSrs = g_DataManager->MapNode()->getMapSRS();
				osg::Vec3d targetPos = pLocalGeoNode->getTransform()->getMatrix().getTrans();

				osgEarth::GeoPoint pt;
				pt.fromWorld(pSrs, targetPos);
				//pt.z() = pt.z() + 10000.0;
				
				//osgEarth::GeoPoint geoCamera(pSrs, dTargetX, dTargetY, dTargetZ + 10000.0);

				//osg::Camera* camera = g_viewerMain->getCamera();

				CameraPath* pCameraPath = dynamic_cast<CameraPath*>(_animationPath.get());
				const std::map<double, CameraPathRecord>& mapRecords = pCameraPath->getMapRecords();
				static int s_nCount = 0;

				double modulated_time = (animTime - pCameraPath->getFirstTime()) / pCameraPath->getPeriod();
				double fraction_part = modulated_time - floor(modulated_time);
				animTime = pCameraPath->getFirstTime() + fraction_part * pCameraPath->getPeriod();

				std::map<double, CameraPathRecord>::const_iterator second = mapRecords.lower_bound(animTime);
				CameraPathRecord record = second->second;

				osgEarth::GeoPoint geoCamera(pSrs, record.dCameraX, record.dCameraY, record.dCameraZ);
				osgEarth::GeoPoint geoTarget(pSrs, record.dTargetX, record.dTargetY, record.dTargetZ);

				osg::Vec3d cameraPosInverse1;
				osg::Vec3d targetPos1;

				geoCamera.toWorld(cameraPosInverse1);
				geoTarget.toWorld(targetPos1);

				osg::Matrixd rotation_matrix = osg::Matrixd::lookAt(cameraPosInverse1, /*targetPos*/targetPos1, osg::Vec3d(1.0, 1.0, 1.0));
				osg::AnimationPath::ControlPoint cp(-rotation_matrix.getTrans(), rotation_matrix.getRotate().inverse());

				_matrix = osg::Matrixd::translate(cp.getPosition()) * osg::Matrixd::rotate(cp.getRotation());
			}
	}

	return true;
}

