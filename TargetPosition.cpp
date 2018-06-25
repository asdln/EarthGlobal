#include "TargetPosition.h"
#include <osgEarthQt/AnnotationListWidget>
#include <osgEarthQt/AnnotationDialogs>
#include <osgEarthQt/Common>
#include <osgEarthQt/GuiActions>
#include <osgEarthAnnotation/LocalGeometryNode>

#include "TargetDataReader.h"

extern osg::ref_ptr<osg::Group> s_annoGroup;
extern osgEarth::QtGui::DataManager* g_DataManager;

TargetPosition::TargetPosition(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.pushButton_Set->setEnabled(false);
	ui.lineEdit_Hei->setEnabled(false);
	ui.lineEdit_Lat->setEnabled(false);
	ui.lineEdit_Lon->setEnabled(false);

	ui.lineEdit_AngleX->setEnabled(false);
	ui.lineEdit_AngleY->setEnabled(false);
	ui.lineEdit_AngleZ->setEnabled(false);
}

TargetPosition::~TargetPosition()
{

}

void TargetPosition::slotOnSelectionChanged()
{
	bool bSelected = false;
	osgEarth::QtGui::AnnotationVector annos;
	g_DataManager->getAnnotations(annos);
	for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{
		if (g_DataManager->isSelected(*it))
		{
			osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode == nullptr)
				continue;

			std::string strGuid = pLocalGeoNode->getAnnotationData()->getName();
			std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
			if (itr != TargetDataReader::s_mapPara.end())
			{
				TargetDataPara para = itr->second;
				ui.lineEdit_Lon->setText(QString::number(para.dx));
				ui.lineEdit_Lat->setText(QString::number(para.dy));
				ui.lineEdit_Hei->setText(QString::number(para.dz));

				ui.lineEdit_AngleX->setText(QString::number(para.dAngleX));
				ui.lineEdit_AngleY->setText(QString::number(para.dAngleY));
				ui.lineEdit_AngleZ->setText(QString::number(para.dAngleZ));

				bSelected = true;
			}
		}
	}

	ui.pushButton_Set->setEnabled(bSelected);
	ui.lineEdit_Hei->setEnabled(bSelected);
	ui.lineEdit_Lat->setEnabled(bSelected);
	ui.lineEdit_Lon->setEnabled(bSelected);

	ui.lineEdit_AngleX->setEnabled(bSelected);
	ui.lineEdit_AngleY->setEnabled(bSelected);
	ui.lineEdit_AngleZ->setEnabled(bSelected);
}

void TargetPosition::slotSetNewPosition()
{
	osgEarth::QtGui::AnnotationVector annos;
	g_DataManager->getAnnotations(annos);
	for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{
		if (g_DataManager->isSelected(*it))
		{
			osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode == nullptr)
				continue;

			std::string strGuid = pLocalGeoNode->getOrCreateAnnotationData()->getName();
			std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
			if (itr != TargetDataReader::s_mapPara.end())
			{
// 				itr->second.dx = ui.lineEdit_Lon->text().toDouble();
// 				itr->second.dy = ui.lineEdit_Lat->text().toDouble();
// 				itr->second.dz = ui.lineEdit_Hei->text().toDouble();
// 
// 				TargetDataPara para = itr->second;
// 
// 				TargetDataReader targetReader;
// 				osgEarth::Features::Feature* pFeature =
// 					targetReader.GetFeature(g_DataManager->MapNode()->getMapSRS(), para);
// 
// 				pFeatureNode->getAnnotationData()->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, 10000.0, 0.0, -90.0, 1e5));
// 
// 				pFeatureNode->setFeature(pFeature);


				//////////////////////////////////////////////////////////////////////////
				itr->second.dx = ui.lineEdit_Lon->text().toDouble();
				itr->second.dy = ui.lineEdit_Lat->text().toDouble();
				itr->second.dz = ui.lineEdit_Hei->text().toDouble();

				itr->second.dAngleX = ui.lineEdit_AngleX->text().toDouble();
				itr->second.dAngleY = ui.lineEdit_AngleY->text().toDouble();
				itr->second.dAngleZ = ui.lineEdit_AngleZ->text().toDouble();

				TargetDataPara para = itr->second;

				pLocalGeoNode->setPosition(osgEarth::GeoPoint(g_DataManager->MapNode()->getMapSRS(), osg::Vec3d(para.dx, para.dy, para.dz)));
				//pLocalGeoNode->getOrCreateAnnotationData()->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 1e5));
				pLocalGeoNode->getOrCreateAnnotationData()->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0,  10.0));

				osg::Quat quat(para.dAngleX, osg::Vec3f(1.0, 0.0, 0.0), para.dAngleY, osg::Vec3f(0.0, 1.0, 0.0), para.dAngleZ, osg::Vec3f(0.0, 0.0, 1.0));
				pLocalGeoNode->setLocalRotation(quat);

// 				TargetDataReader targetReader;
// 
// 				osgEarth::Symbology::Geometry* pGeometry =
// 					targetReader.GetGeometry(para);
// 
// 				g_DataManager->removeAnnotation(*it);
// 
// 				osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = new osgEarth::Annotation::LocalGeometryNode(g_DataManager->MapNode(), pGeometry, osgEarth::Annotation::Style());
// 
//  				osgEarth::Annotation::AnnotationData* annoData = new osgEarth::Annotation::AnnotationData();

// 				annoData->setName(strGuid);
// 				annoData->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 1e5));
//  				pFeatureNode->setAnnotationData(annoData);
// 				g_DataManager->addAnnotation(pFeatureNode, s_annoGroup);
 				//pFeatureNode->setFeature(pFeature);
			}
		}
	}
}
