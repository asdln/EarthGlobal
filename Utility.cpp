#include "Utility.h"
#include "osgEarth/SpatialReference"
#include "osgEarthQt/DataManager"
#include <QtCore/QtMath>
#include "osg/AnimationPath"

extern osgEarth::QtGui::DataManager* g_DataManager;
extern osgViewer::Viewer* g_viewerMain;

Utility::Utility()
{

}

Utility::~Utility()
{

}

osg::Matrixd Utility::GetCameraMatrix(double dCameraLon, double dCameraLat, double dCameraH
									  , double dAngle, double dTargetLon, double dTargetLat, double dTargetH)
{
	osg::Vec3d startWorld;
	osg::Vec3d center;

	const osgEarth::SpatialReference* pSrs = g_DataManager->MapNode()->getMapSRS();
	osgEarth::GeoPoint geoPoint(pSrs, dCameraLon, dCameraLat, dCameraH);
	//osgEarth::GeoPoint geoPoint(pSrs, dx2, dy2, dz2 + 10000.0);
	geoPoint.toWorld(startWorld);

	osgEarth::GeoPoint geoPointCenter(pSrs, dTargetLon, dTargetLat, dTargetH);
	geoPointCenter.toWorld(center);

	osg::Quat quat(qDegreesToRadians(dAngle), startWorld - center);
	osg::Matrixd matrix(quat);

	osg::Vec3d normal(0, 1.0, 0);
	osg::Vec3d vecAngle = matrix.postMult(normal);

	osg::Matrixd rotation_matrix = osg::Matrixd::lookAt(startWorld, center, vecAngle);

	osg::AnimationPath::ControlPoint cp(-rotation_matrix.getTrans(), rotation_matrix.getRotate().inverse());
	osg::Matrixd matrixRes = osg::Matrixd::translate(cp.getPosition()) * osg::Matrixd::rotate(cp.getRotation());
	return matrixRes;
}

void Utility::SetCamera(double dLon, double dLat, double dH, double dAngle, double dTLon, double dTLat, double dTH)
{
	osg::Camera* pCamera = g_viewerMain->getCamera();

	osg::Matrixd matrix = GetCameraMatrix(dLon, dLat, dH, dAngle, dTLon, dTLat, dTH);
	pCamera->setViewMatrix(osg::Matrixd::inverse(matrix));
}
