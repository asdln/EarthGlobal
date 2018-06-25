#pragma once

#include <QObject>

#include <osgViewer/View>
#include <osgViewer/Viewer>
#include <osgEarth/MapNode>
#include <osgEarthSymbology/Geometry>

#include <osgEarthFeatures/Feature>
#include <osgEarthAnnotation/FeatureNode>

#include <osgEarthQt/ViewerWidget>

class RangeFeatureGenerator : public QObject
{
	Q_OBJECT

public:
	RangeFeatureGenerator(osgEarth::QtGui::ViewerWidget* pWidget, osg::Group*rootMain, osg::Group* rootEagleEye, osgEarth::MapNode* pMapNodeMain, osgEarth::MapNode* pMapNodeEye);
	~RangeFeatureGenerator();

public:

public slots:

	void RefreshRangeFeature();

	void BulidFeature();

public:

	void RefreshBackgroundTexture();

protected:

	osg::Geode* createHUDBg(int nWid, int nHei);

protected:

	osg::ref_ptr<osgEarth::MapNode>  _mapNodeMain;

	osg::ref_ptr<osgEarth::MapNode>  _mapNodeEye;

	osg::ref_ptr<osgEarth::Symbology::Polygon> _polygon;

	osg::ref_ptr<osgEarth::Features::Feature> _polyFeature;

	osg::ref_ptr<osgEarth::Annotation::FeatureNode> _polyNode;

	osgEarth::QtGui::ViewerWidget* m_pWidget;

	QTimer m_timerRangeFeature;

	int m_nBackgroundWid;
	int m_nBackgroundHei;

	osg::Camera* m_pHudCamera;
	osg::Geode* m_pCurrentGeode;
};

