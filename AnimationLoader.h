#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include <QtCore/QString>
#include <osg/AnimationPath>
#include "PathEarthManipulate.h"
#include "CameraPath.h"
#include "TargetPath.h"

class AnimationLoader
{
public:
	AnimationLoader();
	~AnimationLoader();

	static TargetPath* LoadTargetPath(const QString& fileName);

	static CameraPath* LoadCameraPath(const QString& fileName);

private:
	
};

#endif // ANIMATIONLOADER_H
