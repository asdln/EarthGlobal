#include "TargetDataReader.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>

#include <QtCore/QTextStream>

#include <osgEarthFeatures/Feature>

#include <osgEarthAnnotation/AnnotationData>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthAnnotation/TrackNode>

#include "Temp2radiance.h"


#include "osgEarth/DataParaManager.h"
#include "osgEarth/ColorTransform.h"

struct Point3D
{
	double dx;
	double dy;
	double dz;
};

struct SurfaceIndex
{
	int a;
	int b;
	int c;
};

std::map<std::string, TargetDataPara> TargetDataReader::s_mapPara;

TargetDataReader::TargetDataReader()
{

}

TargetDataReader::~TargetDataReader()
{
}

osgEarth::Features::Feature* TargetDataReader::GetFeature(const osgEarth::SpatialReference* pSpatialRef, const TargetDataPara& para)
{
	//m_featureList.clear();

	bool bTransToRadio = para.bTransToRadio;

	QString strIndexPath = para.strIndexPath;
	QString strValuePath = para.strValuePath;

	double dx = para.dx;
	double dy = para.dy;
	double dz = para.dz;

	double dstart = para.dstart;
	double dend = para.dend;
	double dfen = para.dfen;
	double dfa = para.dfa;

	m_dx = dx;
	m_dy = dy;

	QList<Point3D> vecPoint3D;
	QList<SurfaceIndex> vecSurface;

	QList<double> vecValue;

	//坐标最大值最小值
	//double dMin1, dMax1, dMin2, dMax2, dMin3, dMax3;
	bool bFirstTime = true;
	//Read Index
	{
		QFile file(strIndexPath);
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return nullptr;

		bool bPointBegins = false;
		bool bIndexBegins = false;

		while(!file.atEnd())
		{
			QByteArray line = file.readLine();
			QTextStream textLine(line);

			if (line.startsWith("1 ") && bFirstTime)
			{
				bPointBegins = 1;
				bFirstTime = false;
			}
			else if (line.startsWith("1 ") && !bFirstTime)
			{
				bIndexBegins = 1;
			}

			if(bPointBegins && !bIndexBegins)
			{
				int nID;
				Point3D point3d;
				textLine >> nID >> point3d.dx >> point3d.dy >> point3d.dz;

// 				if (vecPoint3D.empty())
// 				{
// 					dMin1 = dMax1 = point3d.dx;
// 					dMin2 = dMax2 = point3d.dy;
// 					dMin3 = dMax3 = point3d.dz;
// 				}
// 				else
// 				{
// 					if (dMin1 > point3d.dx)
// 						dMin1 = point3d.dx;
// 
// 					if (dMax1 < point3d.dx)
// 						dMax1 = point3d.dx;
// 
// 					if(dMin2 > point3d.dy)
// 						dMin2 = point3d.dy;
// 
// 					if(dMax2 < point3d.dy)
// 						dMax2 = point3d.dy;
// 
// 					if(dMin3 > point3d.dz)
// 						dMin3 = point3d.dz;
// 
// 					if(dMax3 < point3d.dz)
// 						dMax3 = point3d.dz;
// 				}

				point3d.dx /= 111000.0;
				point3d.dy /= 111000.0;

				point3d.dx += dx;
				point3d.dy += dy;
				point3d.dz += dz;

				vecPoint3D.push_back(point3d);
			}
			else if(bIndexBegins)
			{
				int nID;
				SurfaceIndex surface;
				textLine >> nID >> surface.a >> surface.b >> surface.c;
				vecSurface.push_back(surface);
			}
		}
	}

	double dValueMin, dValueMax;
	//Read Value
	{
		QFile file(strValuePath);
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return nullptr;

		//第一行记录个数
		QByteArray line = file.readLine();

		while(!file.atEnd())
		{
			QByteArray line = file.readLine();
			QTextStream textLine(line);

			int nIndex;
			double dValue;
			textLine >> nIndex >> dValue;

			if (vecValue.empty())
			{
				dValueMin = dValueMax = dValue;
			}
			else
			{
				if(dValueMin > dValue)
					dValueMin = dValue;

				if(dValueMax < dValue)
					dValueMax = dValue;
			}

			vecValue.push_back(dValue);
		}
	}


	osgEarth::Symbology::Style lineStyle;
	lineStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color(0.0, 1.0, 0.0, 1.0);

// 	lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// 		->stroke()->color() = osgEarth::Symbology::Color(1.0, 0.0, 0.0, 1.0);

	osg::Vec4Array* colors = new osg::Vec4Array;
	osgEarth::Annotation::MultiGeometry* pMultiGeometry = new osgEarth::Annotation::MultiGeometry;

	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(pMultiGeometry,
																			pSpatialRef, lineStyle);
	pFeature->setColorArray(colors);
	

	for(int i = 0; i < vecSurface.size(); i ++)
	{
		if (vecSurface[i].a >= vecPoint3D.size()
			|| vecSurface[i].b >= vecPoint3D.size()
			|| vecSurface[i].c >= vecPoint3D.size())
		{
			continue;
		}

		if (i >= vecValue.size())
		{
			break;
		}

		Point3D point1 = vecPoint3D[vecSurface[i].a];
		Point3D point2 = vecPoint3D[vecSurface[i].b];
		Point3D point3 = vecPoint3D[vecSurface[i].c];

		//数值大小的考虑，dx当做z，范围拉伸为0到5000
		double dStretchMin = 20000;
		double dStretchMax = 21000;

// 		point1.dx = (point1.dx - dMin1) / (dMax1 - dMin1) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point2.dx = (point2.dx - dMin1) / (dMax1 - dMin1) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point3.dx = (point3.dx - dMin1) / (dMax1 - dMin1) * (dStretchMax - dStretchMin) + dStretchMin;
// 
// 		dStretchMin = 0.0;
// 		dStretchMax = 90.0;
// 
// 		point1.dy = (point1.dy - dMin2) / (dMax2 - dMin2) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point2.dy = (point2.dy - dMin2) / (dMax2 - dMin2) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point3.dy = (point3.dy - dMin2) / (dMax2 - dMin2) * (dStretchMax - dStretchMin) + dStretchMin;
// 
// 		dStretchMin = 0.0;
// 		dStretchMax = 45.0;
// 
// 		point1.dz = (point1.dz - dMin3) / (dMax3 - dMin3) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point2.dz = (point2.dz - dMin3) / (dMax3 - dMin3) * (dStretchMax - dStretchMin) + dStretchMin;
// 		point3.dz = (point3.dz - dMin3) / (dMax3 - dMin3) * (dStretchMax - dStretchMin) + dStretchMin;

		double dValue = vecValue[i];

		if (bTransToRadio)
		{
			dValue = Temp2radiance(dValue, dstart, dend, dfen, dfa);

			if(DataParaManager::Instance()->IsDataValid())
			{
				double dRadio, dTrans;
				DataParaManager::Instance()->GetValue(point1.dx, point1.dy, dRadio, dTrans);
				dValue = dRadio + dValue * dTrans;
			}

			dValueMax = DataParaManager::Instance()->GetRadioMax();
			dValueMin = DataParaManager::Instance()->GetRadioMin();
		}
		else
		{
			dValueMax = DataParaManager::Instance()->GetTemperatureMax();
			dValueMin = DataParaManager::Instance()->GetTemperatureMin();
		}

		double dR = dValue;
		double dG = dValue;
		double dB = dValue;
		if (DataParaManager::Instance()->IsRGBMode())
		{
			unsigned char R, G, B;
			ColorTransform::Gray2RGB(dValueMin, dValueMax, dValue, R, G, B);
			dR = R / 256.0;
			dG = G / 256.0;
			dB = B / 256.0;
		}
		else
		{
			dStretchMin = 0.0;
			dStretchMax = 1.0;
			dValue = (dValue - dValueMin) / (dValueMax - dValueMin) * (dStretchMax - dStretchMin) + dStretchMin;

			dR = dValue;
			dG = dValue;
			dB = dValue;
		}

// 		lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// 			->stroke()->color() = osgEarth::Symbology::Color::Yellow;
// 		lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// 			->stroke()->width() = 2.0;

		colors->push_back(osg::Vec4(dR, dG, dB, 1.0));

		osgEarth::Annotation::Polygon* pPolygon = new osgEarth::Annotation::Polygon;

		pPolygon->push_back(osg::Vec3d(point1.dx, point1.dy, point1.dz));
		pPolygon->push_back(osg::Vec3d(point2.dx, point2.dy, point2.dz));
		pPolygon->push_back(osg::Vec3d(point3.dx, point3.dy, point3.dz));

		pMultiGeometry->add(pPolygon);

//		m_featureList.push_back(pFeature);

// 		pFeature->getGeometry()->push_back(osg::Vec3d(-120.37, 34.039, 50000.0));
// 		pFeature->getGeometry()->push_back(osg::Vec3d(-120.09, 33.96, 50000.0));
// 		pFeature->getGeometry()->push_back(osg::Vec3d(-119.75, 34, 50000.0));
	}

	//sm_featureList.push_back(pFeature);

	return pFeature/*m_featureList*/;
}
