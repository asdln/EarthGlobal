#ifndef CAMERAPATH_H
#define CAMERAPATH_H

#include "OEAnimationPath.h"
#include <QtCore/QString>

struct CameraPathRecord
{	
	double dCameraX;
	double dCameraY;
	double dCameraZ;

	double dTargetX;
	double dTargetY;
	double dTargetZ;

	double dAngle;

	QString strAirDataPath;
};

class CameraPath : public OEAnimationPath
{
public:
	CameraPath();
	~CameraPath();

	void addRecord(double dTime, const CameraPathRecord& record);

	const std::map<double, CameraPathRecord>& getMapRecords() { return m_mapRecord; }

private:
	
	std::map<double, CameraPathRecord> m_mapRecord;

};

#endif // CAMERAPATH_H
