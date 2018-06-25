#include "CameraPath.h"

CameraPath::CameraPath()
{

}

CameraPath::~CameraPath()
{

}

void CameraPath::addRecord(double dTime, const CameraPathRecord& record)
{
	m_mapRecord[dTime] = record;
}