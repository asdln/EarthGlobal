#include "TargetAnimationPathCallback.h"

TargetAnimationPathCallback::TargetAnimationPathCallback(osg::AnimationPath* ap) : osg::AnimationPathCallback(ap)
{

}

TargetAnimationPathCallback::~TargetAnimationPathCallback()
{

}

double TargetAnimationPathCallback::getAnimationTime() const
{
	return _latestTime;
}
