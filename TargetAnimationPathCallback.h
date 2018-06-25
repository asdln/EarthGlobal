#ifndef TARGETANIMATIONPATHCALLBACK_H
#define TARGETANIMATIONPATHCALLBACK_H

#include <osg/AnimationPath>

class TargetAnimationPathCallback : public osg::AnimationPathCallback
{
public:
	TargetAnimationPathCallback(osg::AnimationPath* ap);
	~TargetAnimationPathCallback();

	virtual double getAnimationTime() const;

private:
	
};

#endif // TARGETANIMATIONPATHCALLBACK_H
