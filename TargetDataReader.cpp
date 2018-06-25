#include "TargetDataReader.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>

#include <QtCore/QTextStream>
#include <QtCore/QVector>
#include <osg/Switch>
#include <osgEarthFeatures/Feature>

#include <osgEarthAnnotation/AnnotationData>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthAnnotation/TrackNode>

#include "Temp2radiance.h"
#include <QtWidgets/QApplication>
#include <QtCore/QFileInfo>

#include "osgEarth/DataParaManager.h"
#include "osgEarth/ColorTransform.h"

double g_dJetValue = 0.0012;

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

struct PointValue
{
	double dx;
	double dy;
	double dValue;
};

void GetRGBColor(double dLon, double dLat, double dH, double dValue, double& dR, double& dG, double& dB)
{
	DataParaManager* pDataParaManager = DataParaManager::Instance();

	if (pDataParaManager->IsFixedAngleMode())
	{
		double dRadio, dTrans;
		pDataParaManager->GetFixedAngleValue(dLon, dLat, dH, dRadio, dTrans);
		dValue = dRadio + dValue * dTrans;
	}
	
	double dValueMax = pDataParaManager->GetRadioMax();
	double dValueMin = pDataParaManager->GetRadioMin();

	dR = dValue;
	dG = dValue;
	dB = dValue;
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
	
}

osg::Geode* TargetDataReader::GetJetModel(const QString& strPath, double dLon, double dLat, double dH)
{
	QFile file(strPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return nullptr;

	QList<PointValue> listPointValue;

	int nCols = 87;
	int nRows = 56;

	int nLineIndex = -1;
	while (!file.atEnd())
	{
		nLineIndex++;
		QByteArray line = file.readLine();
		if (nLineIndex < 3)
		{
			QByteArray lineTemp;
			for (int i = 0; i < line.size(); i ++)
			{
				if (line[i] != ' ')
				{
					lineTemp.append(line[i]);
				}
			}

			QByteArray byteWid;
			int nWidIndex = -1;

			for (int i = 0; i < lineTemp.size() - 1; i ++)
			{
				if (lineTemp[i] == 'I' && lineTemp[i + 1] == '=')
				{
					nWidIndex = i + 2;
					break;
				}
			}

			if (nWidIndex != -1)
			{
				for (int i = nWidIndex; i < lineTemp.size(); i++)
				{
					if (lineTemp[i] == ',')
						break;

					byteWid.append(lineTemp[i]);
				}

				QByteArray byteHei;
				//int nWidIndex = lineTemp.indexOf("J=");

				int nHeiIndex = -1;
				for (int i = 0; i < lineTemp.size() - 1; i++)
				{
					if (lineTemp[i] == 'J' && lineTemp[i + 1] == '=')
					{
						nHeiIndex = i + 2;
						break;
					}
				}

				if (nHeiIndex != -1)
				{
					for (int i = nHeiIndex; i < lineTemp.size(); i++)
					{
						if (lineTemp[i] == ',')
							break;

						byteHei.append(lineTemp[i]);
					}
				}

				nCols = QString(byteWid).toInt();
				nRows = QString(byteHei).toInt();
			}

			continue;
		}

		QTextStream textLine(line);

		PointValue value;
		textLine >> value.dx >> value.dy >> value.dValue;

		//value.dValue *= 10000.0;

		listPointValue.push_back(value);
	}

	file.close();

	osg::Geode* geode = new osg::Geode;
	osg::Vec3Array* vertices = new osg::Vec3Array;
	osg::Vec4Array* colors = new osg::Vec4Array;

	DataParaManager* pDataParaManager = DataParaManager::Instance();

	int nCount = 0;
	for (int j = 0; j < nRows - 1; j++)
	{
		for (int i = 0; i < nCols - 1; i++)
		{
			double dValue = listPointValue[j * nCols + i].dValue;

			if (dValue < g_dJetValue)
			{
				continue;
			}

			nCount++;
			vertices->push_back(osg::Vec3d(listPointValue[j * nCols + i].dx, listPointValue[j * nCols + i].dy, 0.0));
			vertices->push_back(osg::Vec3d(listPointValue[j * nCols + i + 1].dx, listPointValue[j * nCols + i + 1].dy, 0.0));
			vertices->push_back(osg::Vec3d(listPointValue[(j + 1) * nCols + i + 1].dx, listPointValue[(j + 1) * nCols + i + 1].dy, 0.0));
			vertices->push_back(osg::Vec3d(listPointValue[(j + 1) * nCols + i].dx, listPointValue[(j + 1) * nCols + i].dy, 0.0));

			double dR, dG, dB;
			GetRGBColor(dLon, dLat, dH, dValue, dR, dG, dB);
			colors->push_back(osg::Vec4(dR, dG, dB, 1.0));

			dValue = listPointValue[j * nCols + i + 1].dValue;
			GetRGBColor(dLon, dLat, dH, dValue, dR, dG, dB);
			colors->push_back(osg::Vec4(dR, dG, dB, 1.0));

			dValue = listPointValue[(j + 1) * nCols + i + 1].dValue;
			GetRGBColor(dLon, dLat, dH, dValue, dR, dG, dB);
			colors->push_back(osg::Vec4(dR, dG, dB, 1.0));

			dValue = listPointValue[(j + 1) * nCols + i].dValue;
			GetRGBColor(dLon, dLat, dH, dValue, dR, dG, dB);
			colors->push_back(osg::Vec4(dR, dG, dB, 1.0));
		}
	}

	osg::Geometry* polyGeom = new osg::Geometry();
	polyGeom->setVertexArray(vertices);
	polyGeom->setColorArray(colors, osg::Array::BIND_PER_VERTEX);
	//polyGeom->setNormalArray(shared_normals.get(), osg::Array::BIND_OVERALL);
	polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, nCount * 4/*(nCols - 1) * (nRows - 1) * 4*/));

	//polyGeom->setName(s.c_str());
	geode->addDrawable(polyGeom);

	return geode;
}

osg::Switch* TargetDataReader::GetGeode(const TargetDataPara& para)
{
	//m_featureList.clear();

	osg::Geode* geode = nullptr;

	bool bTransToRadio = para.bTransToRadio;

	if (para.strPltPath.isEmpty())
	{
		/*osg::Geode* */geode = new osg::Geode;
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

		QString strIndexPath = para.strIndexPath;
		QString strValuePath = para.strValuePath;

		double dx = para.dx;
		double dy = para.dy;
		double dz = para.dz;

		double dstart = para.dstart;
		double dend = para.dend;
		double dfen = para.dfen;
		double dfa = para.dfa;

		// 	m_dx = dx;
		// 	m_dy = dy;

		QMap<int, Point3D> mapPoint3D;
		QMap<int, SurfaceIndex> mapSurface;

		QMap<int, double> mapValue;

		//坐标最大值最小值
		//double dMin1, dMax1, dMin2, dMax2, dMin3, dMax3;
		bool bFirstTime = true;
		QVector<int> vecPartIndices;
		//Read Index
		{
			QFile file(strIndexPath);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return nullptr;

			bool bPointBegins = false;
			bool bIndexBegins = false;

			int nCurrentLineIndex = -1;
			int nPartCount = 0;

			while (!file.atEnd())
			{
				nCurrentLineIndex++;
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

				if (nPartCount == 0)
				{
					if (nCurrentLineIndex == 1)
					{
						textLine >> nPartCount;
					}
				}
				else if (nCurrentLineIndex >= 4 && nCurrentLineIndex < nPartCount + 4)
				{
					int nPartIndex = 0;
					textLine >> nPartIndex;

					vecPartIndices.push_back(nPartIndex);
				}

				if (bPointBegins && !bIndexBegins)
				{
					int nID;
					Point3D point3d;
					textLine >> nID >> point3d.dx >> point3d.dy >> point3d.dz;

					point3d.dx /= 1000.0;
					point3d.dy /= 1000.0;
					point3d.dz /= 1000.0;

					mapPoint3D[nID] = point3d;
					//vecPoint3D.push_back(point3d);
				}
				else if (bIndexBegins)
				{
					int nID;

					SurfaceIndex surface;
					textLine >> nID >> surface.a >> surface.b >> surface.c;

					if (nID == 0)
					{
						int x = 0;
					}

					//vecSurface.push_back(surface);
					mapSurface[nID] = surface;
				}
			}
		}

		double dValueMin, dValueMax;
		//Read Value
		{
			QFile file(strValuePath);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return nullptr;

			//第一行记录个数
			QByteArray line = file.readLine();

			while (!file.atEnd())
			{
				QByteArray line = file.readLine();
				QTextStream textLine(line);

				int nID;
				double dValue;
				textLine >> nID >> dValue;

				if (mapValue.empty())
				{
					dValueMin = dValueMax = dValue;
				}
				else
				{
					if (dValueMin > dValue)
						dValueMin = dValue;

					if (dValueMax < dValue)
						dValueMax = dValue;
				}

				mapValue[nID] = dValue;
				//vecValue.push_back(dValue);
			}
		}

		for (QMap<int, SurfaceIndex>::iterator itr = mapSurface.begin(); itr != mapSurface.end(); itr++)
		{
			int nSurfaceKey = itr.key();

			Point3D point1;
			Point3D point2;
			Point3D point3;

			QMap<int, Point3D>::iterator itrPoint1 = mapPoint3D.find(itr->a);
			if (itrPoint1 != mapPoint3D.end())
			{
				point1 = itrPoint1.value();
			}
			else
			{
				continue;
			}

			QMap<int, Point3D>::iterator itrPoint2 = mapPoint3D.find(itr->b);
			if (itrPoint2 != mapPoint3D.end())
			{
				point2 = itrPoint2.value();
			}
			else
			{
				continue;
			}

			QMap<int, Point3D>::iterator itrPoint3 = mapPoint3D.find(itr->c);
			if (itrPoint3 != mapPoint3D.end())
			{
				point3 = itrPoint3.value();
			}
			else
			{
				continue;
			}

			double dValue;
			QMap<int, double>::iterator itrValue = mapValue.find(nSurfaceKey);
			if (itrValue != mapValue.end())
			{
				dValue = itrValue.value();
			}
			else
			{
				continue;
			}

			//数值大小的考虑，dx当做z，范围拉伸为0到5000
			double dStretchMin = 20000;
			double dStretchMax = 21000;

			//double dValue = vecValue[i];
			DataParaManager* pDataParaManager = DataParaManager::Instance();

			double dValueRecord = dValue;

			if (bTransToRadio)
			{
				dValue = Temp2radiance(dValue, dstart, dend, dfen, dfa);

				if (pDataParaManager->IsFixedAngleMode())
				{
					double dRadio, dTrans;
					pDataParaManager->GetFixedAngleValue(dx, dy, dz, dRadio, dTrans);
					dValue = dRadio + dValue * dTrans;
				}

				dValueRecord = dValue;

				dValueMax = pDataParaManager->GetRadioMax();
				dValueMin = pDataParaManager->GetRadioMin();
			}
			else
			{
				dValueMax = pDataParaManager->GetTemperatureMax();
				dValueMin = pDataParaManager->GetTemperatureMin();
			}

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
				dStretchMin = 0.0;
				dStretchMax = 1.0;
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

			std::ostringstream ostr;
			ostr << "t:" << dValueRecord;
			std::string s = ostr.str();
			polyGeom->setName(s.c_str());

			geode->addDrawable(polyGeom);
		}
	}
	else
	{
		PltReader pltReader;
		geode = pltReader.GetPltNode(para.strPltPath, para);
	}

	///添加火焰的模型
	//osg::Group* pGroupAll = new osg::Group;
	osg::Switch* pGroupAll = new osg::Switch;
	double dPI = 3.1415926;

	double dx = para.dx;
	double dy = para.dy;
	double dz = para.dz;
	
	if (para.bCustomJet)
	{
		const QList<JetPosInfo>& listJetInfo = para.listJetPosInfo;
		for (int i = 0; i < listJetInfo.size(); i ++)
		{
			const JetPosInfo& jetPosInfo = listJetInfo[i];
			osg::Node* pNodeFlameJet1 = GetJetModel(para.strJetPath, dx, dy, dz);
			if (pNodeFlameJet1 != 0)
			{
				//1
				{
					//osg::Node* pNodeFlameJet1 = GetJetModel(para.strJetPath, dx, dy, dz);
					pNodeFlameJet1->setName(QString::number(i + 1).toUtf8().data());
					//para.pJet1 = pNodeFlameJet1;

					osg::MatrixTransform* pMatrixTransformJet = new osg::MatrixTransform;

					osg::MatrixTransform* pMatrixTransform1 = new osg::MatrixTransform;
					pMatrixTransform1->addChild(pNodeFlameJet1);

					osg::Matrix matrixRotate;
					matrixRotate.makeRotate(dPI / 2.0, osg::Vec3f(1.0, 0.0, 0.0));

					osg::Matrix matrixRotate2;
					matrixRotate2.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 1.0, 0.0));

					pMatrixTransform1->postMult(matrixRotate);
					pMatrixTransform1->postMult(matrixRotate2);

					osg::MatrixTransform* pMatrixTransform2 = new osg::MatrixTransform;
					pMatrixTransform2->addChild(pNodeFlameJet1);

					pMatrixTransform2->postMult(matrixRotate2);

					osg::Matrix matrixTranslate;
					matrixTranslate.makeTranslate(jetPosInfo.dx, jetPosInfo.dy, jetPosInfo.dz);

					pMatrixTransformJet->addChild(pMatrixTransform1);
					pMatrixTransformJet->addChild(pMatrixTransform2);

					osg::Matrix matrixRotatePitch;
					matrixRotatePitch.makeRotate(jetPosInfo.dPitch, osg::Vec3f(1.0, 0.0, 0.0));

					osg::Matrix matrixRotateYaw;
					matrixRotateYaw.makeRotate(jetPosInfo.dYaw, osg::Vec3f(0.0, 1.0, 0.0));

					osg::Matrix matrixRotateRoll;
					matrixRotateRoll.makeRotate(jetPosInfo.dRoll, osg::Vec3f(0.0, 0.0, 1.0));

					pMatrixTransformJet->postMult(matrixRotatePitch);
					pMatrixTransformJet->postMult(matrixRotateYaw);
					pMatrixTransformJet->postMult(matrixRotateRoll);

					pMatrixTransformJet->postMult(matrixTranslate);
					pGroupAll->addChild(pMatrixTransformJet);
				}
			}
		}
	}
	else
	{

		osg::Node* pNodeFlameJet1 = GetJetModel(para.strJetPath, dx, dy, dz);
		if (pNodeFlameJet1 != 0)
		{
			//1
			{
				//osg::Node* pNodeFlameJet1 = GetJetModel(para.strJetPath, dx, dy, dz);
				pNodeFlameJet1->setName("1");
				//para.pJet1 = pNodeFlameJet1;

				osg::Matrix matrixRotate;
				matrixRotate.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 0.0, 1.0));

				osg::Matrix matrixTranslate;
				matrixTranslate.makeTranslate(0.0, 0.305, 0.0);

				osg::MatrixTransform* pMatrixTransform = new osg::MatrixTransform;
				pMatrixTransform->addChild(pNodeFlameJet1);

				pMatrixTransform->postMult(matrixRotate);
				pMatrixTransform->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform);

				osg::Matrix matrixRotate2;
				matrixRotate2.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 1.0, 0.0));

				osg::MatrixTransform* pMatrixTransform2 = new osg::MatrixTransform;
				pMatrixTransform2->addChild(pNodeFlameJet1);

				pMatrixTransform2->postMult(matrixRotate);
				pMatrixTransform2->postMult(matrixRotate2);
				pMatrixTransform2->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform2);
			}

			//2
			{
				osg::Node* pNodeFlameJet2 = GetJetModel(para.strJetPath, dx, dy, dz);
				pNodeFlameJet2->setName("2");
				//para.pJet2 = pNodeFlameJet2;

				osg::Matrix matrixRotate;
				matrixRotate.makeRotate(dPI * 1.5, osg::Vec3f(0.0, 0.0, 1.0));

				osg::Matrix matrixTranslate;
				matrixTranslate.makeTranslate(0.0, -0.305, 0.0);

				osg::MatrixTransform* pMatrixTransform = new osg::MatrixTransform;
				pMatrixTransform->addChild(pNodeFlameJet2);

				pMatrixTransform->postMult(matrixRotate);
				pMatrixTransform->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform);

				osg::Matrix matrixRotate2;
				matrixRotate2.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 1.0, 0.0));

				osg::MatrixTransform* pMatrixTransform2 = new osg::MatrixTransform;
				pMatrixTransform2->addChild(pNodeFlameJet2);

				pMatrixTransform2->postMult(matrixRotate);
				pMatrixTransform2->postMult(matrixRotate2);
				pMatrixTransform2->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform2);
			}

			//3
			{
				osg::Node* pNodeFlameJet3 = GetJetModel(para.strJetPath, dx, dy, dz);
				pNodeFlameJet3->setName("3");
				//para.pJet3 = pNodeFlameJet3;

				osg::Matrix matrixRotate;
				matrixRotate.makeRotate(dPI / -2.0, osg::Vec3f(0.0, 1.0, 0.0));

				osg::Matrix matrixTranslate;
				matrixTranslate.makeTranslate(0.0, 0.0, 0.305);

				osg::MatrixTransform* pMatrixTransform = new osg::MatrixTransform;
				pMatrixTransform->addChild(pNodeFlameJet3);

				pMatrixTransform->postMult(matrixRotate);
				pMatrixTransform->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform);

				osg::Matrix matrixRotate2;
				matrixRotate2.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 0.0, 1.0));

				osg::MatrixTransform* pMatrixTransform2 = new osg::MatrixTransform;
				pMatrixTransform2->addChild(pNodeFlameJet3);

				pMatrixTransform2->postMult(matrixRotate);
				pMatrixTransform2->postMult(matrixRotate2);
				pMatrixTransform2->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform2);
			}

			//4
			{
				osg::Node* pNodeFlameJet4 = GetJetModel(para.strJetPath, dx, dy, dz);
				pNodeFlameJet4->setName("4");
				//para.pJet4 = pNodeFlameJet4;

				osg::Matrix matrixRotate;
				matrixRotate.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 1.0, 0.0));

				osg::Matrix matrixTranslate;
				matrixTranslate.makeTranslate(0.0, 0.0, -0.305);

				osg::MatrixTransform* pMatrixTransform = new osg::MatrixTransform;
				pMatrixTransform->addChild(pNodeFlameJet4);

				pMatrixTransform->postMult(matrixRotate);
				pMatrixTransform->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform);

				osg::Matrix matrixRotate2;
				matrixRotate2.makeRotate(dPI / 2.0, osg::Vec3f(0.0, 0.0, 1.0));

				osg::MatrixTransform* pMatrixTransform2 = new osg::MatrixTransform;
				pMatrixTransform2->addChild(pNodeFlameJet4);

				pMatrixTransform2->postMult(matrixRotate);
				pMatrixTransform2->postMult(matrixRotate2);
				pMatrixTransform2->postMult(matrixTranslate);

				pGroupAll->addChild(pMatrixTransform2);
			}
		}
	}

	pGroupAll->addChild(geode);
	return pGroupAll;
}

osgEarth::Symbology::Geometry* TargetDataReader::GetGeometry(const TargetDataPara& para, osg::Vec4Array** pColorArray)
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

// 	m_dx = dx;
// 	m_dy = dy;

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

// 				point3d.dx /= 111000.0;
// 				point3d.dy /= 111000.0;

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




// 	lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
// 		->stroke()->color() = osgEarth::Symbology::Color(1.0, 0.0, 0.0, 1.0);

	osg::Vec4Array* colors = new osg::Vec4Array;
	*pColorArray = colors;
	osgEarth::Annotation::MultiGeometry* pMultiGeometry = new osgEarth::Annotation::MultiGeometry;

// 	osgEarth::Symbology::Style lineStyle;
// 	lineStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
// 		->fill()->color() = osgEarth::Symbology::Color(0.0, 1.0, 0.0, 1.0);
// 
// 	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(pMultiGeometry,
// 																			pSpatialRef, lineStyle);
// 	pFeature->setColorArray(colors);
	

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
		DataParaManager* pDataParaManager = DataParaManager::Instance();

		if (bTransToRadio)
		{
			dValue = Temp2radiance(dValue, dstart, dend, dfen, dfa);

			if(pDataParaManager->IsFixedAngleMode())
			{
				double dRadio, dTrans;
				pDataParaManager->GetFixedAngleValue(point1.dx, point1.dy, point1.dz, dRadio, dTrans);
				dValue = dRadio + dValue * dTrans;
			}

			dValueMax = pDataParaManager->GetRadioMax();
			dValueMin = pDataParaManager->GetRadioMin();
		}
		else
		{
			dValueMax = pDataParaManager->GetTemperatureMax();
			dValueMin = pDataParaManager->GetTemperatureMin();
		}

		double dR = dValue;
		double dG = dValue;
		double dB = dValue;
		if(pDataParaManager->IsRGBMode())
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

	return pMultiGeometry/*m_featureList*/;
}
