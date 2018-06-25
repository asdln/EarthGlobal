#ifndef PATHEARTHMANIPULATE_H
#define PATHEARTHMANIPULATE_H

#include "osgEarthUtil/EarthManipulator"
#include "osgGA/AnimationPathManipulator"


class PathEarthManipulate : public osgGA::AnimationPathManipulator//public osgEarth::Util::EarthManipulator
{
public:
	PathEarthManipulate(osg::AnimationPath* animationPath);
	~PathEarthManipulate();

public:

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	osg::Matrixd getRotation(const osg::Vec3d& point) const;

	bool createLocalCoordFrame(const osg::Vec3d& worldPos, osg::CoordinateFrame& out_frame) const;

	osg::Quat computeCenterRotation(const osg::Vec3d& point) const;

	/** get the position of the manipulator as 4x4 Matrix.*/
	virtual osg::Matrixd getMatrix() const;

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	virtual osg::Matrixd getInverseMatrix() const;

	void setVecMatrix(const std::vector<osg::Matrixd>& vecMatrix);

protected:

	std::vector<osg::Matrixd> m_vecMatrix;

	osg::ref_ptr<osg::AnimationPath> _animationPath;
	
};

#endif // PATHEARTHMANIPULATE_H
