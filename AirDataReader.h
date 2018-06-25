#pragma once

#include <QtCore/QString>

#include <osgEarth/SpatialReference>
#include <osgEarthFeatures/Feature>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthQt/DataManager>

class AirDataReader
{
public:
	AirDataReader();
	~AirDataReader();

	static double m_dx;
	static double m_dy;
	static double m_dz;

	void AddData(const QString& strPath);
};

