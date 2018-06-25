#ifndef TARGETPATH_H
#define TARGETPATH_H

#include "OEAnimationPath.h"

class TargetPath : public OEAnimationPath
{
public:
	TargetPath();
	~TargetPath();

	void insert(double time, unsigned int nJetState, const ControlPoint& controlPoint);

	const std::map<double, unsigned int>& GetMapJetStateTag(){ return m_mapJetStateTag; }

private:

	std::map<double, unsigned int> m_mapJetStateTag;
	
};

#endif // TARGETPATH_H
