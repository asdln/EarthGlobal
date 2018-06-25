#include "TargetPath.h"

TargetPath::TargetPath()
{

}

TargetPath::~TargetPath()
{

}

void TargetPath::insert(double time, unsigned int nJetState, const ControlPoint& controlPoint)
{
	m_mapJetStateTag[time] = nJetState;
	OEAnimationPath::insert(time, controlPoint);
}