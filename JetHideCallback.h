#ifndef JETHIDECALLBACK_H
#define JETHIDECALLBACK_H

#include <osg/Callback>

#include "TargetPath.h"

class JetHideCallback : public osg::NodeCallback
{
public:
	JetHideCallback(TargetPath* ap);
	~JetHideCallback();

public:

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	osg::ref_ptr<TargetPath> m_ptrTargetAnimationPath;
	
};

#endif // JETHIDECALLBACK_H
