#include "AnimationLoader.h"
#include "QtWidgets/QFileDialog"
#include "viewpoint2target.h"
#include <osgEarthQt/DataManager>
#include <osg/Math>
#include "OEAnimationPath.h"
#include <QtCore/QTextStream>
#include <QtMath>

extern osgViewer::Viewer* g_viewerMain;
extern osgEarth::QtGui::DataManager* g_DataManager;

osg::Vec3d getUpVector(const osg::CoordinateFrame& cf) 
{
	return osg::Vec3d(cf(2, 0), cf(2, 1), cf(2, 2)); 
}

bool createLocalCoordFrame(const osg::Vec3d& worldPos, osg::CoordinateFrame& out_frame)
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


osg::Matrixd getRotation(const osg::Vec3d& point)
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
	if (osg::equivalent(dot, 1.0))
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

osg::Quat computeCenterRotation(const osg::Vec3d& point)
{
	return getRotation(point).getRotate().inverse();
}

AnimationLoader::AnimationLoader()
{

}

AnimationLoader::~AnimationLoader()
{

}

double g_dTargetLastLon = 0.0;
double g_dTargetLastLat = 0.0;
double g_dTargetLastH = 0.0;

TargetPath* AnimationLoader::LoadTargetPath(const QString& fileName)
{
	if(fileName.isEmpty())
		return NULL;

	TargetPath* pAnimationPath = new TargetPath;
	pAnimationPath->setLoopMode(osg::AnimationPath::LOOP);

	CoordType coordType = WGS84;

	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	bool bStarted = false;

	while(!file.atEnd())
	{
		QByteArray line = file.readLine();
		if(!bStarted && !line.startsWith("1 "))
			continue;

		bStarted = true;

		//一条记录
		int nIndex;
		double dTime;
		unsigned int nJetTag;
		double dLon, dLat, dH;
		double dAngle1, dAngle2, dAngle3;
		//double dx, dy, dz, da1, da2, da3;
		//bool bShow;

		QTextStream textLine(line);
		textLine >> nIndex >> dTime >> dLat >> dLon >> dH >> dAngle1 >> dAngle2 >> dAngle3 >> nJetTag;

		//dLon = 61.75700;
		//dLat = 175.89400;
		//dH = 1301.987465;

		if(nIndex <= 0)
			continue;

		g_dTargetLastLat = dLat;
		g_dTargetLastLon = dLon;
		g_dTargetLastH = dH;

		//coordType = ?
		double dPitch, dAzimuth;
		osg::Vec3d startWorld;
		osg::Quat finalQuat;
		if(coordType == CoordType::WGS84)
		{
			const osgEarth::SpatialReference* pSrs = g_DataManager->MapNode()->getMapSRS();
			osgEarth::GeoPoint geoPoint(pSrs, dLon, dLat, dH);
			geoPoint.toWorld(startWorld);

			osg::Quat centerQuat = computeCenterRotation(startWorld);

			osg::Quat azim_q(dAngle1, osg::Vec3d(0, 0, 1));
			osg::Quat pitch_q(dAngle2, osg::Vec3d(1, 0, 0));
			osg::Quat angle_q(dAngle3, osg::Vec3d(0, 1, 0));
			osg::Matrix newRot = osg::Matrixd(centerQuat * azim_q * pitch_q * angle_q);
			finalQuat = osg::Matrixd::inverse(newRot).getRotate();
		}
		else if(coordType == CoordType::RightAngle)
		{
			//startWorld[0] = dx;
			//startWorld[1] = dy;
			//startWorld[2] = dz;

			//osg::Quat azim_q(da1, osg::Vec3d(0, 0, 1));
			//osg::Quat pitch_q(da2, osg::Vec3d(1, 0, 0));
			//osg::Quat angle_q(da3, osg::Vec3d(0, 1, 0));
			//osg::Matrix newRot = osg::Matrixd(azim_q * pitch_q * angle_q);
			//finalQuat = osg::Matrixd::inverse(newRot).getRotate();
		}

		pAnimationPath->insert(dTime, nJetTag, osg::AnimationPath::ControlPoint(startWorld, finalQuat));

	}

	return pAnimationPath;
}

CameraPath* AnimationLoader::LoadCameraPath(const QString& fileName)
{
	if(fileName.isEmpty())
		return NULL;

	CameraPath* pAnimationPath = new CameraPath;
	pAnimationPath->setLoopMode(osg::AnimationPath::LOOP);

	CoordType coordType = WGS84;

	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	bool bStarted = false;

	while(!file.atEnd())
	{
		QByteArray line = file.readLine();
		if(!bStarted && !line.startsWith("1 "))
			continue;

		bStarted = true;

		QTextStream textLine(line);

		if(0)
		{
			int nFrameNumber;
			double dTime;
			double x, y, z, a, b, c, d;
			textLine >> nFrameNumber >> dTime >> x >> y >> z >> a >> b >> c >> d;
			pAnimationPath->insert(dTime, osg::AnimationPath::ControlPoint(osg::Vec3d(x, y, z), osg::Quat(a, b, c, d)));
		}
		else
		{
			//一条记录
			double dTime;
			int nFrameIndex;
			double dx1, dy1, dz1, dx2, dy2, dz2, dAngle;
			int nTag;
			QString strAirDataPath;
			textLine >> nFrameIndex >> dTime >> dy1 >> dx1 >> dz1 >> dy2 >> dx2 >> dz2 >> dAngle >> strAirDataPath >> nTag;

			//dx1 = 61.75700;
			//dy1 = 175.89400;
			//dz1 = 11301.987465;

			//dx2 = 61.75700;
			//dy2 = 175.89400;
			//dz2 = 1301.987465;

			double dPitch, dAzimuth;
			osg::Vec3d startWorld;
			osg::Vec3d center;
			if(coordType == CoordType::WGS84)
			{
				const osgEarth::SpatialReference* pSrs = g_DataManager->MapNode()->getMapSRS();
				osgEarth::GeoPoint geoPoint(pSrs, dx1, dy1, dz1);
				//osgEarth::GeoPoint geoPoint(pSrs, dx2, dy2, dz2 + 10000.0);
				geoPoint.toWorld(startWorld);

				osgEarth::GeoPoint geoPointCenter(pSrs, dx2, dy2, dz2);
				geoPointCenter.toWorld(center);

				//viewpoint2targetangle(dx1, dy1, dz1, dx2, dy2, dz2, &dPitch, &dAzimuth, 5);
			}
			else if(coordType == CoordType::RightAngle)
			{
// 				viewpoint2targetangle_xyz(dx1, dy1, dz1, dx2, dy2, dz2, &dPitch, &dAzimuth, 5);
// 				startWorld[0] = dx1;
// 				startWorld[1] = dy1;
// 				startWorld[2] = dz1;
			}

			//dPitch = dPitch / 180.0 * osg::PI;
			//dAzimuth = dAzimuth / 180.0 * osg::PI;
			//dAngle = dAngle / 180.0 * osg::PI;

			//osg::Quat azim_q(dAzimuth, osg::Vec3d(0, 0, 1));
			//osg::Quat pitch_q(-dPitch - osg::PI_2, osg::Vec3d(1, 0, 0));
			//osg::Quat angle_q(-dPitch - osg::PI_2, osg::Vec3d(0, 1, 0));
			//osg::Matrix newRot = osg::Matrixd(azim_q * pitch_q * angle_q);
			//osg::Quat quat = osg::Matrixd::inverse(newRot).getRotate();

			osg::Quat quat(qDegreesToRadians(dAngle), startWorld - center);
			osg::Matrixd matrix(quat);

			osg::Vec3d normal(0, 1.0, 0);
			osg::Vec3d vecAngle = matrix.postMult(normal);

			osg::Matrixd rotation_matrix = osg::Matrixd::lookAt(startWorld, center, vecAngle);

			CameraPathRecord record;
			record.dCameraX = dx1;
			record.dCameraY = dy1;
			record.dCameraZ = dz1;

			record.dTargetX = dx2;
			record.dTargetY = dy2;
			record.dTargetZ = dz2;

			record.dAngle = dAngle;

			if (strAirDataPath.right(5) == ".000C")
			{
				record.strAirDataPath = strAirDataPath + " " + QString::number(nTag);
			}

			pAnimationPath->addRecord(dTime, record);
			pAnimationPath->insert(dTime, osg::AnimationPath::ControlPoint(-rotation_matrix.getTrans(), rotation_matrix.getRotate().inverse()));
		}

	}

	return pAnimationPath;
}
