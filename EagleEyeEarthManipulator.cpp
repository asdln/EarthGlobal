#include "EagleEyeEarthManipulator.h"


EagleEyeEarthManipulator::EagleEyeEarthManipulator()
{
}

EagleEyeEarthManipulator::~EagleEyeEarthManipulator()
{
}

bool EagleEyeEarthManipulator::handlePointAction(const Action& action, float mx, float my, osg::View* view)
{
	//return EarthManipulator::handlePointAction(action, mx, my, view);

	//Exit early if the action is null
	if(action._type == ACTION_NULL)
		return true;

	osg::Vec3d point;
	if(screenToWorld(mx, my, view, point))
	{
		switch(action._type)
		{
		case ACTION_GOTO:
		{
			osgEarth::Viewpoint here = getViewpoint();
			here.focalPoint()->fromWorld(_srs.get(), point);

			//osg::Vec3d pointVP;
			//here.getSRS()->transformFromWorld(point, pointVP);

			//OE_NOTICE << "X=" << pointVP.x() << ", Y=" << pointVP.y() << std::endl;

			//                here.setFocalPoint( pointVP );

			double duration_s = 1.0/*action.getDoubleOption(OPTION_DURATION, 1.0)*/;
			double range_factor = 1.0;//action.getDoubleOption(OPTION_GOTO_RANGE_FACTOR, 1.0);

			//here.range() = here.range().get() * range_factor;
			//here.setRange( here.getRange() * range_factor );

			setViewpoint(here, duration_s);
		}
		break;
		default:
		break;
		}
	}
	return true;
}