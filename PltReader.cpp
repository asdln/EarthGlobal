#include "PltReader.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegularExpression>
#include <QtCore/QVector>
#include <osg/Geode>
#include <osg/Geometry>
#include "osgEarth/DataParaManager.h"
#include "Temp2radiance.h"
#include "osgEarth/ColorTransform.h"

struct Point3D
{
	double dx;
	double dy;
	double dz;

	double dValue;
};

struct SurfaceIndex
{
	int a;
	int b;
	int c;
};

PltReader::PltReader()
{

}

PltReader::~PltReader()
{

}

osg::Geode* PltReader::GetPltNode(const QString& strFilePath, const TargetDataPara& para)
{
// 	if (bTransToRadio)
// 	{
// 		dValue = Temp2radiance(dValue, dstart, dend, dfen, dfa);
// 
// 		if (pDataParaManager->IsFixedAngleMode())
// 		{
// 			double dRadio, dTrans;
// 			pDataParaManager->GetFixedAngleValue(dx, dy, dz, dRadio, dTrans);
// 			dValue = dRadio + dValue * dTrans;
// 		}
// 
// 		dValueRecord = dValue;
// 
// 		dValueMax = pDataParaManager->GetRadioMax();
// 		dValueMin = pDataParaManager->GetRadioMin();
// 	}

	double dstart = para.dstart;
	double dend = para.dend;
	double dfen = para.dfen;
	double dfa = para.dfa;

	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return nullptr;

	QVector<Point3D> vecPoint;
	QVector<SurfaceIndex> vecSurfaceIndex;

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QTextStream textLine(line);

		QString strTemp = line;
		QStringList list = strTemp.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

		double dx = -9999.0;
		double dy = -9999.0;
		double dz = -9999.0;
		double dTemp = -9999.0;
		textLine >> dx >> dy >> dz >> dTemp;

		if (dx == 0.0 && dy == 0.0 && dz == 0.0 && dTemp == 0.0)
		{
			continue;
		}

		if (list.size() == 4)
		{
			Point3D pt3D;
			pt3D.dx = dx / 1000.0;
			pt3D.dy = dy / 1000.0;
			pt3D.dz = dz / 1000.0;
			pt3D.dValue = dTemp;

			vecPoint.push_back(pt3D);
		}
		else if (list.size() == 3)
		{
			SurfaceIndex surfaceIndex;

			QTextStream textLine1(line);
			textLine1 >> surfaceIndex.a >> surfaceIndex.b >> surfaceIndex.c;
			vecSurfaceIndex.push_back(surfaceIndex);
		}
	}

	osg::Geode* geode = new osg::Geode;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

	for (int i = 0; i < vecSurfaceIndex.size(); i ++)
	{
		DataParaManager* pDataParaManager = DataParaManager::Instance();
		if (vecSurfaceIndex[i].a - 1 < 0 || vecSurfaceIndex[i].a - 1 >= vecPoint.size())
			continue;

		if (vecSurfaceIndex[i].b - 1 < 0 || vecSurfaceIndex[i].b - 1 >= vecPoint.size())
			continue;

		if (vecSurfaceIndex[i].c - 1 < 0 || vecSurfaceIndex[i].c - 1 >= vecPoint.size())
			continue;

		Point3D point1 = vecPoint[vecSurfaceIndex[i].a - 1];
		Point3D point2 = vecPoint[vecSurfaceIndex[i].b - 1];
		Point3D point3 = vecPoint[vecSurfaceIndex[i].c - 1];

		double dValue = point1.dValue;
		double dValueMax, dValueMin;

		if (1/*bTransToRadio*/)
		{
			dValue = Temp2radiance(dValue, dstart, dend, dfen, dfa);

 			if (pDataParaManager->IsFixedAngleMode())
 			{
 				double dRadio, dTrans;
 				pDataParaManager->GetFixedAngleValue(para.dx, para.dy, para.dz, dRadio, dTrans);
 				dValue = dRadio + dValue * dTrans;
 			}

			dValueMax = pDataParaManager->GetRadioMax();
			dValueMin = pDataParaManager->GetRadioMin();
		}
// 		else
// 		{
// 			dValueMax = pDataParaManager->GetTemperatureMax();
// 			dValueMin = pDataParaManager->GetTemperatureMin();
// 		}

		double dR = dValue;
		double dG = dValue;
		double dB = dValue;
		if (pDataParaManager->IsRGBMode())
		{
			unsigned char R, G, B;
			ColorTransform::Gray2RGB(dValueMin, dValueMax, dValue, R, G, B);
			dR = R / 256.0;
			dG = G / 256.0;
			dB = B / 256.0;
		}
		else
		{
			double dStretchMin = 0.0;
			double dStretchMax = 1.0;
			dValue = (dValue - dValueMin) / (dValueMax - dValueMin) * (dStretchMax - dStretchMin) + dStretchMin;

			dR = dValue;
			dG = dValue;
			dB = dValue;
		}

		osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		shared_colors->push_back(osg::Vec4(dR, dG, dB, 1.0));

		osg::ref_ptr<osg::Vec3Array> shared_normals = new osg::Vec3Array;
		shared_normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

		osg::Geometry* polyGeom = new osg::Geometry();
		osg::Vec3Array* vertices = new osg::Vec3Array;
		vertices->push_back(osg::Vec3d(point1.dx, point1.dy, point1.dz));
		vertices->push_back(osg::Vec3d(point2.dx, point2.dy, point2.dz));
		vertices->push_back(osg::Vec3d(point3.dx, point3.dy, point3.dz));

		polyGeom->setVertexArray(vertices);
		polyGeom->setColorArray(shared_colors.get(), osg::Array::BIND_OVERALL);
		polyGeom->setNormalArray(shared_normals.get(), osg::Array::BIND_OVERALL);
		polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));

		geode->addDrawable(polyGeom);
	}

	return geode;
}


