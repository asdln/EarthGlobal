#include "AirDataReader.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QtMath>
#include <QtCore/QTextStream>

#include <osgEarthFeatures/Feature>

#include <osgEarthAnnotation/AnnotationData>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthAnnotation/TrackNode>

#include <osgEarth/SpatialReference>
#include <osgEarth/ECEF>

#include <osgUtil/DelaunayTriangulator>
#include "osgEarth/DataParaManager.h"
#include "osgEarth/ColorTransform.h"

extern osg::ref_ptr<osg::Group> s_annoGroup;
extern osgEarth::QtGui::DataManager* g_DataManager;

struct AirRawData
{
	double dx;
	double dy;
	double dz;

	double dRadio;
	double dTrans;
};


double AirDataReader::m_dx = 0.0;
double AirDataReader::m_dy = 0.0;
double AirDataReader::m_dz = 2000.0;

AirDataReader::AirDataReader()
{
}


AirDataReader::~AirDataReader()
{
}

void AirDataReader::AddData(const QString& strPath)
{
	QFile file(strPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	int nTag = 0;

	int a0;
	int a1;
	double a2;
	double a3;
	double a4;
	double a5;
	double a6;
	double a7;
	double a8;
	int a9;

	AirRawData rawData;
	bool bTag = 1;

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QTextStream textLine(line);

		if (bTag)
		{
			QString str1;
			QString str2;
			QString str3;
			QString str4;
			QString str5;
			
			textLine >> str1 >> str2 >> str3 >> m_dx >> str4 >> m_dy >> str5 >> m_dz;
			bTag = 0;
		}

		if (nTag != -99999)
		{
			textLine >> nTag;
		}
		else
		{
			textLine >> a0 >> a1 >> rawData.dx >> rawData.dy >> rawData.dTrans >> rawData.dRadio >> rawData.dz >> a2 >> a3 >> a9;

			//ln_debug 2017/03/30 0:40 下面会导致死机，暂时屏蔽
			DataParaManager* pAirDataBuffer = DataParaManager::Instance();
			pAirDataBuffer->SetValue(rawData.dx, rawData.dy, rawData.dRadio, rawData.dTrans);
		}
	}

	m_dz *= 1000.0;
}

osgEarth::Features::Feature* GetAirFeature(double dTransparent)
{
	int nWid;
	int nHei;

	//if (nWid != nOldWid || nHei != nOldHei)

	DataParaManager::Instance()->GetSize(nWid, nHei);

	//test code...
	//{
	//	double dValueMax = 0.000002;
	//	double dValueMin = 0.0;

	//	uchar* pDataBuffer = new uchar[360 * 180 * 4];
	//	for (int j = -90; j < 90; j ++)
	//	{
	//		for (int i = -180; i < 180; i ++)
	//		{
	//			double dRadio, dTrans;
	//			DataParaManager::Instance()->GetAirValue(i, j, dRadio, dTrans);

	//			unsigned char R, G, B;
	//			ColorTransform::Gray2RGB(dValueMin, dValueMax, dRadio, R, G, B);
	//			
	//			int nCol = i + 180;
	//			int nRow = j + 90;
	//			pDataBuffer[(nRow * 360 + nCol) * 4] = R;
	//			pDataBuffer[(nRow * 360 + nCol) * 4 + 1] = G;
	//			pDataBuffer[(nRow * 360 + nCol) * 4 + 2] = B;
	//			pDataBuffer[(nRow * 360 + nCol) * 4 + 3] = 255;
	//		}
	//	}

	//	QImage img(pDataBuffer, 360, 180, QImage::Format_RGBA8888);
	//	img.save("c:\\1.png");

	//	delete[] pDataBuffer;
	//}

	double dResX = 360.0 / nWid;
	double dResY = 180.0 / nHei;

	osgEarth::Symbology::Style lineStyle;
	lineStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color(0.0, 1.0, 0.0, 1.0);

	//osg::Vec4Array* colors = new osg::Vec4Array;
	//osg::DoubleArray* pDoubleArray = new osg::DoubleArray;
	//osg::IntArray* values = new osg::IntArray;

	osgEarth::Annotation::MultiGeometry* pMultiGeometry = new osgEarth::Annotation::MultiGeometry;

	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(pMultiGeometry,
		g_DataManager->MapNode()->getMapSRS(), lineStyle);
	//pFeature->setColorArray(colors);
	//pFeature->setValueArray(values);

	double dValueMax = DataParaManager::Instance()->GetRadioMax();
	double dValueMin = DataParaManager::Instance()->GetRadioMin();

	//if (0)
	for (int j = 0; j < nHei; j++)
	{
		for (int i = 0; i < nWid; i++)
		{
			double dRadio, dTrans;
			if (DataParaManager::Instance()->GetValue(i, j, dRadio, dTrans))
			{
				double dLon = i / (double)nWid * 360.0 - 180.0;
				double dLat = j / (double)nHei * 180.0 - 90.0;

				double dLeft = dLon - 0.5 * dResX;
				double dRight = dLon + 0.5 * dResX;

				double dTop = dLat + 0.5 * dResY;
				double dBottom = dLat - 0.5 * dResY;

				double dStretchMin = 0.0;
				double dStretchMax = 1.0;

				if (qFabs(dRadio) < 2.0e-10)
					continue;

				DataParaManager::Instance()->GetAirValue(dLon, dLat, dRadio, dTrans);

				double dValue = dRadio;
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
					dValue = (dValue - dValueMin) / (dValueMax - dValueMin) * (dStretchMax - dStretchMin) + dStretchMin;

					dR = dValue;
					dG = dValue;
					dB = dValue;
				}

				//colors->push_back(osg::Vec4(dR, dG, dB, 1.0));
				//pDoubleArray->push_back(dRadio);

				//values->push_back(j * nWid + i);
				//colors->push_back(osg::Vec4(0.0, 1.0, 0.5, 0.5));
				osgEarth::Annotation::Polygon* pPolygon = new osgEarth::Annotation::Polygon;

				pPolygon->m_nIndex = j * nWid + i;
				pPolygon->m_color = new osg::Vec4(dR, dG, dB, dTransparent);

				pPolygon->push_back(osg::Vec3d(dLeft, dTop, 99000.0));
				pPolygon->push_back(osg::Vec3d(dLeft, dBottom, 99000.0));
				pPolygon->push_back(osg::Vec3d(dRight, dBottom, 99000.0));
				pPolygon->push_back(osg::Vec3d(dRight, dTop, 99000.0));
				//pPolygon->push_back(osg::Vec3d(dLeft, dTop, 99000.0));

				pMultiGeometry->add(pPolygon);
			}
		}
	}

	return pFeature;
}

/*
void AirDataReader::AddData(const QString& strPath, osgEarth::QtGui::DataManager* pManager)
{
	QFile file(strPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	int nTag = 0;

	int a0;
	int a1;
	double a2;
	double a3;
	double a4;
	double a5;
	double a6;
	double a7;
	double a8;
	int a9;

	osgEarth::Features::FeatureList listTransFeature;
	osgEarth::Features::FeatureList listRadioFeature;

	QList<AirRawData> listRawData;
	AirRawData rawData;

	osgEarth::Symbology::Style lineStyle;
	lineStyle.getOrCreate<osgEarth::Symbology::PointSymbol>()
		->fill()->color() = osgEarth::Symbology::Color(1.0, 0.0, 0.0, 1.0);

	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(new osgEarth::Annotation::PointSet,
		pManager->MapNode()->getMap()->getSRS(), lineStyle);

	listRadioFeature.push_back(pFeature);

	osg::Vec3Array* vec3Array = new osg::Vec3Array;

	osg::Vec4Array* colors = new osg::Vec4Array;

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QTextStream textLine(line);

		if (nTag != -99999)
		{
			textLine >> nTag;
		}
		else
		{
			textLine >> a0 >> a1 >> a2 >> a3 >> rawData.dTrans >> rawData.dRadio >> rawData.dz >> rawData.dx >> rawData.dy >> a9;

			listRawData.push_back(rawData);
			pFeature->getGeometry()->push_back(osg::Vec3d(rawData.dx, rawData.dy, rawData.dz + 99000.0));

			colors->push_back(osg::Vec4(rawData.dRadio * 1e8, 0.0, 0.0, 1.0));

			vec3Array->push_back(osg::Vec3d(rawData.dx, rawData.dy, rawData.dz + 99000.0));
		}
	}

	pFeature->setColorArray(colors);

	osg::Vec4Array* pColorArray = static_cast<osg::Vec4Array*>(pFeature->getColorArray());

	{
		osgEarth::Annotation::FeatureNode* pFeatureNode = new osgEarth::Annotation::FeatureNode(
			pManager->MapNode(), listRadioFeature);

		osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();
		annoData->setName(QString::fromLocal8Bit("辐射").toUtf8().data());

		double dVPx = listRadioFeature.front()->getGeometry()->front()._v[0];
		double dVPy = listRadioFeature.front()->getGeometry()->front()._v[1];
		annoData->setViewpoint(osgEarth::Viewpoint("Random", dVPx, dVPy, 1000000.0, 0.0, -90.0, 1e5));
		pFeatureNode->setAnnotationData(annoData);

		//pManager->addAnnotation(pFeatureNode, s_annoGroup);
	}


	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator();
	dt->setInputPointArray(vec3Array);

	dt->triangulate();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//设置坐标
	geometry->setVertexArray(vec3Array);
	//设置描述
	geometry->addPrimitiveSet(dt->getTriangles());
	//设置法线
	//geometry->setNormalArray(normals.get());
	//geometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE);
	//设置纹理坐标（纹理填充）
	//osg::ref_ptr<osg::Vec2Array> texCoords = ComputerTextureCoords(*(coords.get()));//得到一 一映射后的范围在0~1的二维纹理数组
	//geometry->setTexCoordArray(0, texCoords.get());
	//尝试颜色填充
	//  osg::ref_ptr<osg::Vec4Array> vextexColorArray = ComputePerVertexColor(*(coords.get()),getOSGColorTable());
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	s_annoGroup->addChild(geometry);
}
*/

//后来的面
/*
void AirDataReader::AddData(const QString& strPath, osgEarth::QtGui::DataManager* pManager)
{
	QFile file(strPath);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	int nTag = 0;

	int a0;
	int a1;
	double a2;
	double a3;
	double a4;
	double a5;
	double a6;
	double a7;
	double a8;
	int a9;

	osgEarth::Features::FeatureList listTransFeature;
	osgEarth::Features::FeatureList listRadioFeature;

//	QList<AirRawData> listRawData;
	AirRawData rawData;

	osgEarth::Symbology::Style lineStyle;
	lineStyle.getOrCreate<osgEarth::Symbology::PointSymbol>()
		->fill()->color() = osgEarth::Symbology::Color(1.0, 0.0, 0.0, 1.0);

	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(new osgEarth::Annotation::PointSet,
																			pManager->MapNode()->getMap()->getSRS(), lineStyle);

	listRadioFeature.push_back(pFeature);

	osg::Vec4Array* colors = new osg::Vec4Array;

	osg::ref_ptr<osg::Vec3Array> allPoints = new osg::Vec3Array();

	while(!file.atEnd())
	{
		QByteArray line = file.readLine();
		QTextStream textLine(line);

		if(nTag != -99999)
		{
			textLine >> nTag;
		}
		else
		{
			textLine >> a0 >> a1 >> rawData.dx >> rawData.dy >> rawData.dTrans >> rawData.dRadio >> rawData.dz >> a2 >> a3 >> a9;

			bool bCopyed = false;

			for (int i = 0; i < allPoints->size(); i ++)
			{
				osg::Vec3 vecValue(rawData.dx, rawData.dy, rawData.dz);
				//if (allPoints->at(i).x() == rawData.dx && allPoints->at(i).y() == rawData.dy)
				if (allPoints->at(i).x() == vecValue.x() && allPoints->at(i).y() == vecValue.y())
				{
					bCopyed = true;
					break;
				}
			}

			if (!bCopyed)
			{
				pFeature->getGeometry()->push_back(osg::Vec3(rawData.dx, rawData.dy, 99000.0));
				allPoints->push_back(osg::Vec3(rawData.dx, rawData.dy, 99000.0));

				colors->push_back(osg::Vec4(rawData.dRadio * 1e8, 0.0, 0.0, 1.0));
			}

//			listRawData.push_back(rawData);

		}
	}

	allPoints.release();

	pFeature->setColorArray(colors);

	osg::Vec4Array* pColorArray = static_cast<osg::Vec4Array*>(pFeature->getColorArray());

	{
		osgEarth::Annotation::FeatureNode* pFeatureNode = new osgEarth::Annotation::FeatureNode(
			pManager->MapNode(), listRadioFeature);

		osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();
		annoData->setName(QString::fromLocal8Bit("辐射").toUtf8().data());

		double dVPx = listRadioFeature.front()->getGeometry()->front()._v[0];
		double dVPy = listRadioFeature.front()->getGeometry()->front()._v[1];
		annoData->setViewpoint(osgEarth::Viewpoint("Random", dVPx, dVPy, 1000000.0, 0.0, -90.0, 1e5));
		pFeatureNode->setAnnotationData(annoData);

		pManager->addAnnotation(pFeatureNode, s_annoGroup);
	}
}
*/