#ifndef OEANIMATIONPATH_H
#define OEANIMATIONPATH_H

#include <osg/AnimationPath>

enum CoordType
{
	RightAngle = 0,
	WGS84 = 1
};

class OEAnimationPath : public osg::AnimationPath
{
public:
	OEAnimationPath();
	~OEAnimationPath();

	virtual bool getInterpolatedControlPoint(double time, osg::AnimationPath::ControlPoint& controlPoint) const;

private:

	CoordType m_coordType;
	
};

#endif // OEANIMATIONPATH_H
