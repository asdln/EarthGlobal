#pragma once

#include <osgEarthUtil/EarthManipulator>

class EagleEyeEarthManipulator : public osgEarth::Util::EarthManipulator
{
public:

	EagleEyeEarthManipulator();
	~EagleEyeEarthManipulator();

protected:

	virtual bool handlePointAction(const Action& action, float mx, float my, osg::View* view);

};

