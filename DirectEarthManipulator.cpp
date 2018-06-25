#include "DirectEarthManipulator.h"
#include "Utility.h"

DirectEarthManipulator::DirectEarthManipulator()
{

}

DirectEarthManipulator::~DirectEarthManipulator()
{

}

osg::Matrixd DirectEarthManipulator::getMatrix() const
{
	return m_matrix;
}

/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
osg::Matrixd DirectEarthManipulator::getInverseMatrix() const
{
	return osg::Matrixd::inverse(m_matrix);
}

void DirectEarthManipulator::SetPosition(double dEyeLon, double dEyeLat, double dEyeH, double dAngle, double dTargetLon, double dTargetLat, double dTargetH)
{
	m_dEyeLon = dEyeLon;
	m_dEyeLat = dEyeLat;
	m_dEyeH = dEyeH;

	m_dAngle = dAngle;

	m_dTargetLat = dTargetLat;
	m_dTargetLon = dTargetLon;
	m_dTargetH = dTargetH;

	m_matrix = Utility::GetCameraMatrix(dEyeLon, dEyeLat, dEyeH, dAngle, dTargetLon, dTargetLat, dTargetH);
}