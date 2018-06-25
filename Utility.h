#ifndef UTILITY_H
#define UTILITY_H

#include "osg/Matrixd"

class Utility
{
public:
	Utility();
	~Utility();

	static osg::Matrixd GetCameraMatrix(double dCameraLon, double dCameraLat, double dCameraH
										, double dAngle, double dTargetLon, double dTargetLat, double dTargetH);

	static void SetCamera(double dLon, double dLat, double dH, double dAngle, double dTLon, double dTLat, double dTH);

private:
	
};

#endif // UTILITY_H
