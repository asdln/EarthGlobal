#pragma once

#include <QtCore/QString>

#include <osgEarth/SpatialReference>
#include <osgEarthFeatures/Feature>

#include <map>

//class osgEarth::SpatialReference;

struct TargetDataPara
{
	bool bTransToRadio;

	QString strIndexPath;
	QString strValuePath;

	double dx;
	double dy;
	double dz;

	double dstart;
	double dend;
	double dfen;
	double dfa;
};

class TargetDataReader
{
public:
	TargetDataReader();
	~TargetDataReader();

	osgEarth::Features::Feature* GetFeature(const osgEarth::SpatialReference* pSpatialRef, const TargetDataPara& para);

	double getx(){ return m_dx; }
	double gety(){ return m_dy; }

	static std::map<std::string, TargetDataPara> s_mapPara;

protected:

	double m_dx;
	double m_dy;

//	osgEarth::Features::FeatureList m_featureList;
};

