#include "PathEarthManipulate.h"
#include <osgEarthQt/DataManager>
#include <osgEarthAnnotation/LocalGeometryNode>
#include "CameraPath.h"
#include "Document.h"
#include <QtCore/QFileInfo>
#include "AnimationController.h"
#include "RangeFeatureGenerator.h"
#include "AirDataReader.h"
#include "osgEarth/DataParaManager.h"

extern osg::ref_ptr<osg::Group> s_annoGroup;
extern RangeFeatureGenerator* g_pRangerFeatureGenerator;
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
			if (AnimationController::IsPathFrameRunning())
			{
				int nCurrentFrameIndex = AnimationController::GetCaptureFrameIndex();

				CameraPath* pCameraPath = dynamic_cast<CameraPath*>(_animationPath.get());
				const std::map<double, CameraPathRecord>& mapRecords = pCameraPath->getMapRecords();

				//double modulated_time = (animTime - pCameraPath->getFirstTime()) / pCameraPath->getPeriod();
				//double fraction_part = modulated_time - floor(modulated_time);
				//animTime = pCameraPath->getFirstTime() + fraction_part * pCameraPath->getPeriod();

				//std::map<double, CameraPathRecord>::const_iterator second = mapRecords.lower_bound(animTime);
				//CameraPathRecord record = second->second;

				QString strPath;
				int nTempIndex = 0;
				for (std::map<double, CameraPathRecord>::const_iterator itr = mapRecords.begin(); itr != mapRecords.end(); itr++)
				{
					if (nTempIndex == nCurrentFrameIndex)
					{
						strPath = itr->second.strAirDataPath;

						DataParaManager::Instance()->SetCameraPosInfo(itr->second.dCameraX, itr->second.dCameraY, itr->second.dCameraZ);

						break;
					}

					nTempIndex++;
				}
 
 			
				if (!strPath.isEmpty())
				{
					Document* pDocument = Document::Instance();
					const QString& strDocumentPath = pDocument->GetAirDataDir();

					QFileInfo fileInfo(strDocumentPath);
					QString strAirPath = fileInfo.absolutePath();
					
					strAirPath = strAirPath + strPath;

					QFileInfo fileInfo2(strAirPath);
					if (fileInfo2.exists())
					{
						//AnimationController::Instance()->LoadAirData(strAirPath);

						DataParaManager* pAirDataBuffer = DataParaManager::Instance();
						pAirDataBuffer->ResetValue();

						AirDataReader reader;
						reader.AddData(strPath);
					}

					g_pRangerFeatureGenerator->RefreshBackgroundTexture();
				}
			}

			if (1)
			{
				_matrix = osg::Matrixd::translate(cp.getPosition()) * osg::Matrixd::rotate(cp.getRotation());
				g_pRangerFeatureGenerator->RefreshBackgroundTexture();

				//重新计算目标的辐射
				DataParaManager* pDataParaManager = DataParaManager::Instance();
				if (0 && pDataParaManager->IsFixedAngleMode())
				{
					osgEarth::QtGui::AnnotationVector out_annotations;
					g_DataManager->getAnnotations(out_annotations);

					osgEarth::QtGui::AnnotationVector annotationsDelete;
					osgEarth::QtGui::AnnotationVector annotationsAdd;

					for (int i = 0; i < out_annotations.size(); i++)
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

							para.dx = pLocalGeoNode->getPosition().x();
							para.dy = pLocalGeoNode->getPosition().y();
							para.dz = pLocalGeoNode->getPosition().z();

							osg::Node* pNode = targetReader.GetGeode(para);

							osgEarth::Annotation::Style circleStyle;
							circleStyle.getOrCreate<osgEarth::Annotation::PolygonSymbol>()->fill()->color() = osgEarth::Annotation::Color(osgEarth::Annotation::Color::Red, 0.5);

							osgEarth::Annotation::LocalGeometryNode* pLocalGeoNodeNew = new osgEarth::Annotation::LocalGeometryNode(g_DataManager->MapNode(), pNode, circleStyle);
							pLocalGeoNodeNew->setAnnotationData(pData);
							pLocalGeoNodeNew->setPosition(pLocalGeoNode->getPosition());

							//pLocalGeoNode->setNode(pNode);
							annotationsDelete.push_back(pLocalGeoNode);
							annotationsAdd.push_back(pLocalGeoNodeNew);
						}
					}

					for (int i = 0; i < annotationsDelete.size(); i++)
					{
						g_DataManager->removeAnnotation(annotationsDelete[i].get(), s_annoGroup);
					}

					for (int i = 0; i < annotationsAdd.size(); i++)
					{
						g_DataManager->addAnnotation(annotationsAdd[i].get(), s_annoGroup);
					}
				}
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

