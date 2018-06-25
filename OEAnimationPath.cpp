#include "OEAnimationPath.h"
#include "AnimationController.h"


OEAnimationPath::OEAnimationPath()
{

}

OEAnimationPath::~OEAnimationPath()
{

}

bool OEAnimationPath::getInterpolatedControlPoint(double time, osg::AnimationPath::ControlPoint& controlPoint) const
{
	if (_timeControlPointMap.empty()) return false;

	double modulated_time = (time - getFirstTime()) / getPeriod();
	double fraction_part = modulated_time - floor(modulated_time);
	time = getFirstTime() + fraction_part * getPeriod();

	TimeControlPointMap::const_iterator second = _timeControlPointMap.lower_bound(time);
	controlPoint = second->second;
	return true;

	if (!AnimationController::IsPathFrameRunning())
	{
		return osg::AnimationPath::getInterpolatedControlPoint(time, controlPoint);
	}
	else
	{
		int nCount = _timeControlPointMap.size();
		if (AnimationController::GetCaptureFrameIndex() <= 0 || AnimationController::GetCaptureFrameIndex() >= nCount)
			return false;

		int nIndex = 0;
		std::map<double, osg::AnimationPath::ControlPoint> mapTest = _timeControlPointMap;
		osg::AnimationPath::TimeControlPointMap::iterator itr;
		for (itr = mapTest.begin(); itr != mapTest.end(); itr++)
		{
			if (nIndex == AnimationController::GetCaptureFrameIndex())
			{
				controlPoint = itr->second;
				break;
			}

			nIndex++;
		}

		return true;
	}
}