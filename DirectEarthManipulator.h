#ifndef DIRECTEARTHMANIPULATOR_H
#define DIRECTEARTHMANIPULATOR_H

#include "osgGA/CameraManipulator"

class DirectEarthManipulator : public osgGA::CameraManipulator
{
public:
	DirectEarthManipulator();
	~DirectEarthManipulator();

	virtual osg::Matrixd getMatrix() const;

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	virtual osg::Matrixd getInverseMatrix() const;

	virtual void setByMatrix(const osg::Matrixd& matrix) { m_matrix = matrix; }

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) { m_matrix.invert(matrix); }

	void SetPosition(double dEyeLon, double dEyeLat, double dEyeH, double dAngle, double dTargetLon, double dTargetLat, double dTargetH);

private:

	double m_dEyeLon;
	double m_dEyeLat;
	double m_dEyeH;

	double m_dAngle;

	double m_dTargetLon;
	double m_dTargetLat;
	double m_dTargetH;

	osg::Matrixd m_matrix;
	
};

#endif // DIRECTEARTHMANIPULATOR_H
