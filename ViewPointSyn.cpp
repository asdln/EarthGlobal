#include "ViewPointSyn.h"

#include <osgEarthQt/AnnotationToolbar>
#include <osgEarthQt/Common>
#include <osgEarthQt/DataManager>
#include <osgEarthQt/MapCatalogWidget>
#include <osgEarthQt/TerrainProfileWidget>
#include <osgEarthQt/ViewerWidget>

#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/GeoData>
#include <osg/Notify>
#include <osg/Version>
#include <osgEarth/ImageUtils>
#include <osgEarth/MapNode>
#include <osgEarth/Registry>
#include <osgEarthAnnotation/AnnotationData>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthAnnotation/TrackNode>
#include <osgEarthQt/ViewerWidget>
#include <osgEarthQt/LayerManagerWidget>
#include <osgEarthQt/MapCatalogWidget>
#include <osgEarthQt/DataManager>
#include <osgEarthQt/AnnotationListWidget>
#include <osgEarthQt/LOSControlWidget>
#include <osgEarthQt/TerrainProfileWidget>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/Ocean>

#include <QtCore/QtMath>

#include "MouseMoveFilter.h"

ViewPointSyn::ViewPointSyn(QObject *parent)
	: QObject(parent)
{

}

ViewPointSyn::~ViewPointSyn()
{

}

void ViewPointSyn::slotDoSyn()
{
	extern osgViewer::Viewer* g_viewerEagleEye;
	extern osgViewer::Viewer* g_viewerMain;

	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	osgEarth::Util::EarthManipulator* eagleMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerEagleEye->getCameraManipulator());

	if (mainMani == NULL)
		return;

	osgEarth::Viewpoint vpMain = mainMani->getViewpoint();
	osgEarth::Viewpoint vpEagle = eagleMani->getViewpoint();

	const osgEarth::GeoPoint& pt1 = vpEagle.focalPoint().value();
	const osgEarth::GeoPoint& pt2 = vpMain.focalPoint().value();

	double dx1 = pt1.x();
	double dy1 = pt1.y();
	double dz1 = pt1.z();

	double dx2 = pt2.x();
	double dy2 = pt2.y();
	double dz2 = pt2.z();

	if(qFabs(dx1 - dx2) > 0.0000001 || qFabs(dy1 - dy2) > 0.0000001 || qFabs(dz1 - dz2) > 0.0000001)
	{
		if(MouseMoveFilter::m_bIsActiving)
		{
			vpMain.focalPoint() = vpEagle.focalPoint();
			mainMani->setViewpoint(vpMain, 0.0);
		}
		else
		{
			vpEagle.focalPoint() = vpMain.focalPoint();
			eagleMani->setViewpoint(vpEagle, 0.00);
		}
	}
}