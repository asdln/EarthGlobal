#pragma once

#include <QtCore/QString>

#include <osgEarth/SpatialReference>
#include <osgEarthFeatures/Feature>

#include <map>

//class osgEarth::SpatialReference;
#include "PltReader.h"


class TargetDataReader
{
public:
	TargetDataReader();
	~TargetDataReader();

	osgEarth::Symbology::Geometry* GetGeometry(const TargetDataPara& para, osg::Vec4Array** pColorArray);

	osg::Geode* GetJetModel(const QString& strPath, double dLon, double dLat, double dH);

	osg::Switch* GetGeode(const TargetDataPara& para);

// 	double getx(){ return m_dx; }
// 	double gety(){ return m_dy; }

	static std::map<std::string, TargetDataPara> s_mapPara;

protected:

// 	double m_dx;
// 	double m_dy;

//	osgEarth::Features::FeatureList m_featureList;
};

