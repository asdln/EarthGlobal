#include "CameraPostionDlg.h"
#include <osgViewer/Viewer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/SpatialReference>
#include <QtCore/QtMath>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMdiArea>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthQt/AnnotationListWidget>
#include <osgEarthQt/AnnotationDialogs>
#include <osgEarthQt/Common>
#include "TargetDataReader.h"
#include <QtWidgets/QTabWidget>
#include "viewpoint2target.h"
#include <QtWidgets/QFileDialog>
#include <osgEarthQt/ViewerWidget>
#include <osgEarthQt/GuiActions>
#include <QtWidgets/QMessageBox>

using namespace osgEarth;
using namespace osgEarth::QtGui;

extern osgViewer::Viewer* g_viewerMain;
extern QMdiSubWindow* g_pMdiSubWindow;
extern QMdiArea* g_pMdiArea;
extern osgEarth::QtGui::ViewerWidget* g_viewerWidget;

extern osg::ref_ptr<osg::Group> s_annoGroup;
extern osgEarth::QtGui::DataManager* g_DataManager;

//double g_dVPVerAngle = 60.0;

class MyNodeVisitor : public osg::NodeVisitor
{
public:

	MyNodeVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		mNodeGroup = new osg::Group();
	}
	~MyNodeVisitor(){}

	virtual void apply(osg::Node& node)
	{
		traverse(node);

		if (node.getName() == "1"
			|| node.getName() == "2"
			|| node.getName() == "3"
			|| node.getName() == "4")
		{
			mNodeGroup->addChild(&node);
		}
	}

	osg::Group* getFilterResult(){ return mNodeGroup.get(); }

protected:

	osg::ref_ptr<osg::Group> mNodeGroup;
};

namespace
{
	class AnnotationListItem1 : public QListWidgetItem
	{
	public:
		AnnotationListItem1(osgEarth::Annotation::AnnotationNode* annotation) : _annotation(annotation) { }

		osgEarth::Annotation::AnnotationNode* annotation() { return _annotation.get(); }

	private:
		osg::ref_ptr<osgEarth::Annotation::AnnotationNode> _annotation;
	};
}

class AnnotationListActionCallbackProxy1 : public ActionCallback
{
public:
	AnnotationListActionCallbackProxy1(CameraPostionDlg* annoList) : _annoList(annoList) { }

	void operator()(void* sender, Action* action)
	{
		if (_annoList)
		{
			Action* foundAction = dynamic_cast<ToggleNodeAction*>(action);
			if (foundAction)
				_annoList->refreshTargetList();
		}
	}

private:
	CameraPostionDlg* _annoList;
};

CameraPostionDlg::CameraPostionDlg(QWidget *parent)
: QDialog(parent), _updating(0)
{
	ui.setupUi(this);

	ui.lineEdit_lon_s->setEnabled(false);
	ui.lineEdit_lat_s->setEnabled(false);
	ui.lineEdit_hei_s->setEnabled(false);

	ui.lineEdit_hor_s->setEnabled(false);
	ui.lineEdit_ver_s->setEnabled(false);
	ui.lineEdit_range_s->setEnabled(false);

	ui.lineEdit_VerVPCur->setEnabled(false);
	ui.lineEdit_HorVPCur->setEnabled(false);

	std::vector<osgViewer::View*> vecViews;
	g_viewerMain->getViews(vecViews);
	osgViewer::View* pView = vecViews[0];

	osg::Camera* pCamera = pView->getCamera();

	double fovy;
	double aspectRatio;
	double zNear;
	double zFar;
	pCamera->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

	ui.lineEdit_VerVPCur->setText(QString::number(fovy));

	double dWid = g_pMdiSubWindow->widget()->width();
	double dHei = g_pMdiSubWindow->widget()->width();

	double dHorAngle = 90.0;
	dHorAngle = qAtan(dWid / dHei * qTan((fovy / 2.0) / 180.0 * 3.1415926)) * 360.0 / 3.1415926;
	ui.lineEdit_HorVPCur->setText(QString::number(dHorAngle));

	ui.lineEdit_FanGunAngle->setText(QString::number(0.0));

	m_targetListWidget = ui.listWidget;

	ui.groupBox_Target->setEnabled(false);

	g_DataManager->addAfterActionCallback(new AnnotationListActionCallbackProxy1(this));

	{
		bool bRes = connect(g_DataManager, SIGNAL(mapChanged()), this, SLOT(onMapChanged()));
		bRes = connect(g_DataManager, SIGNAL(selectionChanged(/*const AnnotationVector&*/)), this, SLOT(onSelectionChanged(/*const AnnotationVector&*/)));
		bRes = connect(m_targetListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onListSelectionChanged()));

		connect(m_targetListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
		connect(m_targetListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onItemChanged(QListWidgetItem*)));
	}
}

CameraPostionDlg::~CameraPostionDlg()
{

}

void CameraPostionDlg::onItemChanged(QListWidgetItem* item)
{
	AnnotationListItem1* annoItem = dynamic_cast<AnnotationListItem1*>(item);
	if (annoItem && annoItem->annotation())
		g_DataManager->doAction(this, new osgEarth::QtGui::ToggleNodeAction(annoItem->annotation(), item->checkState() == Qt::Checked));
}

void CameraPostionDlg::onMapChanged()
{
	refreshTargetList();
}

void CameraPostionDlg::onItemDoubleClicked(QListWidgetItem* item)
{
	AnnotationListItem1* annoItem = dynamic_cast<AnnotationListItem1*>(item);
	if (annoItem && annoItem->annotation())
	{
		if (annoItem->annotation()->getAnnotationData() && annoItem->annotation()->getAnnotationData()->getViewpoint())
		{
			extern osgViewer::Viewer* g_viewerMain;
			osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
			mainMani->setViewpoint(osgEarth::Viewpoint(*annoItem->annotation()->getAnnotationData()->getViewpoint()));
		}
	}
}

void CameraPostionDlg::onSelectionChanged()
{
	refreshTargetList();
}

void CameraPostionDlg::onListSelectionChanged()
{
	if (_updating)
		return;

	AnnotationVector annos;

	QList<QListWidgetItem*> items = m_targetListWidget->selectedItems();
	for (QList<QListWidgetItem*>::iterator it = items.begin(); it != items.end(); ++it)
	{
		AnnotationListItem1* annoItem = dynamic_cast<AnnotationListItem1*>(*it);
		if (annoItem && annoItem->annotation())
			annos.push_back(annoItem->annotation());
	}

	g_DataManager->setSelectedAnnotations(annos);
}

void CameraPostionDlg::refreshTargetList()
{
	TargetDataPara para;
	GetSelectedLocalGeometryNodePara(para);
	osg::Switch* pJets = GetSelectedJet();
	bool bSelected = pJets != NULL;
	ui.groupBox_Target->setEnabled(bSelected);
	ui.pushButton_loadJet->setEnabled(bSelected);

	if (bSelected)
	{
		ui.checkBox_Jet1->setEnabled(true);
		ui.checkBox_Jet2->setEnabled(true);
		ui.checkBox_Jet3->setEnabled(true);
		ui.checkBox_Jet4->setEnabled(true);

		ui.checkBox_Jet1->setChecked(pJets->getValue(0)/*para.pJet1->getNodeMask() != 0*/);
		ui.checkBox_Jet2->setChecked(pJets->getValue(2)/*para.pJet2->getNodeMask() != 0*/);
		ui.checkBox_Jet3->setChecked(pJets->getValue(4)/*para.pJet3->getNodeMask() != 0*/);
		ui.checkBox_Jet4->setChecked(pJets->getValue(6)/*para.pJet4->getNodeMask() != 0*/);
	}
	else
	{
		ui.checkBox_Jet1->setEnabled(false);
		ui.checkBox_Jet2->setEnabled(false);
		ui.checkBox_Jet3->setEnabled(false);
		ui.checkBox_Jet4->setEnabled(false);
	}

	ui.lineEdit_Lon->setText(QString::number(para.dx));
	ui.lineEdit_Lat->setText(QString::number(para.dy));
	ui.lineEdit_Hei->setText(QString::number(para.dz));

	ui.lineEdit_AngleX->setText(QString::number(para.dAngleX));
	ui.lineEdit_AngleY->setText(QString::number(para.dAngleY));
	ui.lineEdit_AngleZ->setText(QString::number(para.dAngleZ));

	_updating++;

	if (1/*g_DataManager.valid()*/)
	{
		m_targetListWidget->clear();

		osgEarth::Annotation::AnnotationData* annoData = 0L;
		bool annoDataSet = false;

		AnnotationVector annos;
		g_DataManager->getAnnotations(annos);
		for (AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
		{
			osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode == nullptr)
				continue;

			AnnotationListItem1* item = new AnnotationListItem1(*it);
			item->setText(QString(tr((*it)->getAnnotationData() ? (*it)->getAnnotationData()->getName().c_str() : "Annotation")));
			item->setCheckState((*it)->getNodeMask() != 0 ? Qt::Checked : Qt::Unchecked);

			m_targetListWidget->addItem(item);

			if (g_DataManager->isSelected(*it))
			{
				if (!annoDataSet)
				{
					annoData = (*it)->getAnnotationData();
					annoDataSet = true;
				}
				else
					annoData = 0L;

				item->setSelected(true);
			}
		}
	}

	_updating--;
}

void CameraPostionDlg::slotCopy()
{
	ui.lineEdit_lon->setText(ui.lineEdit_lon_s->text());
	ui.lineEdit_lat->setText(ui.lineEdit_lat_s->text());
	ui.lineEdit_hei->setText(ui.lineEdit_hei_s->text());

	ui.lineEdit_horAngle->setText(ui.lineEdit_hor_s->text());
	ui.lineEdit_VerAngle->setText(ui.lineEdit_ver_s->text());
	ui.lineEdit_Range->setText(ui.lineEdit_range_s->text());
}

void CameraPostionDlg::slotSet()
{
	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());

	double dx = ui.lineEdit_lon->text().toDouble();
	double dy = ui.lineEdit_lat->text().toDouble();
	double dz = ui.lineEdit_hei->text().toDouble();

	double dhor = ui.lineEdit_horAngle->text().toDouble();
	double dver = ui.lineEdit_VerAngle->text().toDouble();
	double dRange = ui.lineEdit_Range->text().toDouble();

	osgEarth::Viewpoint viewPoint = mainMani->getViewpoint();
	
	viewPoint.focalPoint()->set(osgEarth::SpatialReference::get("wgs84"), dx, dy, dz, osgEarth::ALTMODE_ABSOLUTE);
	viewPoint.setHeading(dhor);
	viewPoint.setPitch(-dver);
	viewPoint.setRange(dRange);

	mainMani->setViewpoint(viewPoint);
}

void CameraPostionDlg::slotFocus()
{
	double dTargetX = ui.doubleSpinBox_FocusLon->value();
	double dTargetY = ui.doubleSpinBox_FocusLat->value();
	double dTargetZ = ui.doubleSpinBox_FocusHei->value();

	Focus(dTargetX, dTargetY, dTargetZ);
}

void CameraPostionDlg::Focus(double dLon, double dLat, double dH)
{
	if (ui.lineEdit_lon->text().isEmpty()
		|| ui.lineEdit_lat->text().isEmpty()
		|| ui.lineEdit_hei->text().isEmpty())
	{
		QMessageBox box;
		box.setText(QString::fromLocal8Bit("请输入视点位置"));
		box.exec();
		return;
	}

	double dViewX = ui.lineEdit_lon->text().toDouble();
	double dViewY = ui.lineEdit_lat->text().toDouble();
	double dViewZ = ui.lineEdit_hei->text().toDouble();

	double dTargetX = dLon;//pLocalGeoNode->getPosition().x();
	double dTargetY = dLat;//pLocalGeoNode->getPosition().y();
	double dTargetZ = dH;//pLocalGeoNode->getPosition().z();

	double dPitch, dAzimuth;
	viewpoint2targetangle(dViewX, dViewY, dViewZ, dTargetX, dTargetY, dTargetZ, &dPitch, &dAzimuth, 5);

	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());

	osgEarth::Viewpoint viewPoint = mainMani->getViewpoint();

	viewPoint.focalPoint()->set(osgEarth::SpatialReference::get("wgs84"), dViewX, dViewY, dViewZ, osgEarth::ALTMODE_ABSOLUTE);
	viewPoint.setHeading(dAzimuth);
	viewPoint.setPitch(dPitch);
	viewPoint.setRange(0.0);

	mainMani->setViewpoint(viewPoint/*, 0.5*/);
}

void CameraPostionDlg::slotTrace()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	g_DataManager->getAnnotations(out_annotations);

	osgEarth::Annotation::AnnotationNode* pCurrentAnnotationNode = NULL;

	for (int i = 0; i < out_annotations.size(); i++)
	{
		if (g_DataManager->isSelected(out_annotations[i]))
		{
			pCurrentAnnotationNode = out_annotations[i];
			break;
		}
	}

	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>(pCurrentAnnotationNode);
	if (!pLocalGeoNode)
	{
		QMessageBox box;
		box.setText(QString::fromLocal8Bit("请选择目标"));
		box.exec();
		return;
	}

	double dTargetX = pLocalGeoNode->getPosition().x();
	double dTargetY = pLocalGeoNode->getPosition().y();
	double dTargetZ = pLocalGeoNode->getPosition().z();

	Focus(dTargetX, dTargetY, dTargetZ);
}

void CameraPostionDlg::slotTest()
{
	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	mainMani->rotate(0.0, 0.0, 45.0);
}

void CameraPostionDlg::slotRefreshInfo()
{
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	if (mainMani == NULL)
		return;

	osgEarth::Viewpoint viewPoint = mainMani->getViewpoint();

	double dx = viewPoint.focalPoint().value().x();
	double dy = viewPoint.focalPoint().value().y();
	double dz = viewPoint.focalPoint().value().z();

	osg::Vec3d offset = viewPoint.positionOffset().value();

	double dHeading = viewPoint.heading().value().getValue();
	double dpitch = viewPoint.pitch().value().getValue();
	double dRange = viewPoint.range().value().getValue();

	ui.lineEdit_lon_s->setText(QString::number(dx));
	ui.lineEdit_lat_s->setText(QString::number(dy));
	ui.lineEdit_hei_s->setText(QString::number(dz));

	ui.lineEdit_hor_s->setText(QString::number(dHeading));
	ui.lineEdit_ver_s->setText(QString::number(-dpitch));
	ui.lineEdit_range_s->setText(QString::number(dRange));

	double dWid = g_pMdiSubWindow->widget()->width();
	double dHei = g_pMdiSubWindow->widget()->height();

	std::vector<osgViewer::View*> vecViews;
	g_viewerMain->getViews(vecViews);
	osgViewer::View* pView = vecViews[0];

	osg::Camera* pCamera = pView->getCamera();

	double fovy;
	double aspectRatio;
	double zNear;
	double zFar;
	pCamera->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

	double dHorAngle = 90.0;
	dHorAngle = qAtan(dWid / dHei * qTan(fovy / 180.0 * 3.1415926)) * 360.0 / 3.1415926;
	if (dHorAngle < 0.0)
	{
		dHorAngle += 360.0;
	}
	ui.lineEdit_HorVPCur->setText(QString::number(dHorAngle));
	ui.lineEdit_VerVPCur->setText(QString::number(fovy * 2.0));

	//void RangeFeatureGenerator::RefreshWinWidPortInfo()
	if (g_viewerWidget)
	{
		std::vector<osgViewer::View*> vecViews;
		g_viewerMain->getViews(vecViews);
		osgViewer::View* pView = vecViews[0];

		osg::Camera* pCamera = pView->getCamera();
		osg::Viewport* pViewPort = pCamera->getViewport();

		static double g_dViewPortWid = 0.0;
		static double g_dViewPortHei = 0.0;

		static int g_nWinWid = 0;
		static int g_nWinHei = 0;
		
		double dViewPortWid = pViewPort->width();
		double dViewPortHei = pViewPort->height();

		int nWinWid = g_viewerWidget->rect().width();
		int nWinHei = g_viewerWidget->rect().height();

		if (g_dViewPortWid != dViewPortWid 
			|| g_dViewPortHei != dViewPortHei 
			|| g_nWinWid != nWinWid 
			|| g_nWinHei != nWinHei)
		{
			g_dViewPortWid = dViewPortWid;
			g_dViewPortHei = dViewPortHei;
			g_nWinWid = nWinWid;
			g_nWinHei = nWinHei;

			ui.textEdit_Info->setText(QString::fromLocal8Bit("宽: ") + QString::number(nWinWid) + QString::fromLocal8Bit(", 高: ")
				+ QString::number(nWinHei) + QString::fromLocal8Bit(", 水平分辨率: ") + QString::number(g_dViewPortWid, 'g', 4)
				+ QString::fromLocal8Bit(", 垂直分辨率: ") + QString::number(g_dViewPortHei, 'g', 4));
		}
	}	 
}

void CameraPostionDlg::slotSetWin()
{
	double dVPWid = ui.lineEdit_HorRes->text().toDouble();
	double dVPHei = ui.lineEdit_VerRes->text().toDouble();

	{
		QMdiSubWindow* pMdiSubWindow = dynamic_cast<QMdiSubWindow*>(g_viewerWidget->parent());
		if (pMdiSubWindow)
		{
			QRect rectFather = pMdiSubWindow->rect();
			QRect rect = g_viewerWidget->rect();

			int nXoffset = rectFather.width() - rect.width();
			int nYoffset = rectFather.height() - rect.height();

			pMdiSubWindow->resize(QSize(dVPWid + nXoffset, dVPHei + nYoffset));
		}
	}

	int nWinWid = g_viewerWidget->rect().width();
	int nWinHei = g_viewerWidget->rect().height();

	double dVerAngle = ui.lineEdit_VerVP->text().toDouble();
	double dParaVerAngle = dVerAngle;

	std::vector<osgViewer::View*> vecViews;
	g_viewerMain->getViews(vecViews);
	osgViewer::View* pView = vecViews[0];

	osg::Camera* pCamera = pView->getCamera();
	osg::Viewport* pViewPort = pCamera->getViewport();
	pCamera->setProjectionMatrixAsPerspective(dParaVerAngle, nWinWid/(double)nWinHei, 1.0f, 10000.0f);

	//pViewPort->setViewport(0.0, 0.0, dVPWid, dVPHei);
}

void CameraPostionDlg::slotSetRotateAngle()
{
	double dAngle = ui.lineEdit_FanGunAngle->text().toDouble();

	extern osgViewer::Viewer* g_viewerMain;
	osgEarth::Util::EarthManipulator* mainMani = dynamic_cast<osgEarth::Util::EarthManipulator*>(g_viewerMain->getCameraManipulator());
	mainMani->rotate(0.0, 0.0, dAngle);
}

//void CameraPostionDlg::slotSetViewPort()
//{
	//osg::Camera* camera = g_viewerMain->getCamera();
	//
	//QString strTest = ui.lineEdit_VerVP->text();
	//if (ui.lineEdit_VerVP->text().isEmpty())
	//	return;

	//double dVerAngle = ui.lineEdit_VerVP->text().toDouble();
	//double dParaVerAngle = dVerAngle / 2.0;

	//double dOffset = 1.0;
	//
	//double dWidth = 1.0;
	//double dHeight = 1.0;

	//dVerAngle /= 2.0;
	//dVerAngle = dVerAngle / 180.0 * 3.1415926;

	//double dWidDivHei = qTan(dHorAngle) / qTan(dVerAngle);
	//QWidget* pWidget = g_pMdiSubWindow->widget();

	//double dWidSpace = g_pMdiSubWindow->width() - pWidget->width();
	//double dHeiSpace = g_pMdiSubWindow->height() - pWidget->height();

	//double dCurrentWidDivHei = pWidget->width() / (double)pWidget->height();

	//double dNewWid = pWidget->width();
	//double dNewHei = pWidget->height();

	//if (dWidDivHei > dCurrentWidDivHei)
	//{
	//	dNewHei = dNewWid / dWidDivHei;
	//}
	//else
	//{
	//	dNewWid = dNewHei * dWidDivHei;
	//}

	//g_pMdiSubWindow->setGeometry(0, 0, dNewWid + dWidSpace, dNewHei + dHeiSpace);
	//camera->setProjectionMatrixAsPerspective(dParaVerAngle, camera->getViewport()->width() / camera->getViewport()->height(), 1.0f, 10000.0f);
//}

void CameraPostionDlg::slotSetNewPosition()
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
				itr->second.dx = ui.lineEdit_Lon->text().toDouble();
				itr->second.dy = ui.lineEdit_Lat->text().toDouble();
				itr->second.dz = ui.lineEdit_Hei->text().toDouble();

				itr->second.dAngleX = ui.lineEdit_AngleX->text().toDouble();
				itr->second.dAngleY = ui.lineEdit_AngleY->text().toDouble();
				itr->second.dAngleZ = ui.lineEdit_AngleZ->text().toDouble();

				TargetDataPara para = itr->second;

				pLocalGeoNode->setPosition(osgEarth::GeoPoint(g_DataManager->MapNode()->getMapSRS(), osg::Vec3d(para.dx, para.dy, para.dz)));
				pLocalGeoNode->getOrCreateAnnotationData()->setViewpoint(osgEarth::Viewpoint("Random", para.dx, para.dy, para.dz, 0.0, -90.0, 10.0));

				double dRa = 3.1415926 / 180.0;
				osg::Quat quat(para.dAngleX * dRa, osg::Vec3f(1.0, 0.0, 0.0), para.dAngleY * dRa, osg::Vec3f(0.0, 1.0, 0.0), para.dAngleZ * dRa, osg::Vec3f(0.0, 0.0, 1.0));
				pLocalGeoNode->setLocalRotation(quat);
			}
		}
	}
}

osg::Switch* CameraPostionDlg::GetSelectedJet()
{
	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = NULL;
	osgEarth::QtGui::AnnotationVector annos;
	g_DataManager->getAnnotations(annos);
	for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{
		if (g_DataManager->isSelected(*it))
		{
			pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode != nullptr)
				break;
		}
	}

	if (pLocalGeoNode == NULL) 
		return 0;

	return dynamic_cast<osg::Switch*>(pLocalGeoNode->getNode());
}

bool CameraPostionDlg::GetSelectedLocalGeometryNodePara(TargetDataPara& para)
{
	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = NULL;
	osgEarth::QtGui::AnnotationVector annos;
	g_DataManager->getAnnotations(annos);
	for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{
		if (g_DataManager->isSelected(*it))
		{
			pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode != nullptr)
				break;
		}
	}

	if (pLocalGeoNode == NULL) return false;

	osgEarth::Annotation::AnnotationData* pData = pLocalGeoNode->getOrCreateAnnotationData();
	std::string strGuid = pData->getName();
	std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
	if (itr != TargetDataReader::s_mapPara.end())
	{
		para = itr->second;
		return true;
	}

	return false;
}

void CameraPostionDlg::slotJet1(bool bValue)
{
	//TargetDataPara para;
	//GetSelectedLocalGeometryNodePara(para);

	//if (!para.pJet1) return;
	//para.pJet1->setNodeMask(bValue ? ~0 : 0);

	osg::Switch* pJetSwitch = GetSelectedJet();
	if (!pJetSwitch)
		return;

	pJetSwitch->setValue(0, bValue);
	pJetSwitch->setValue(1, bValue);
}

void CameraPostionDlg::slotJet2(bool bValue)
{
	//TargetDataPara para;
	//GetSelectedLocalGeometryNodePara(para);

	//if (!para.pJet2) return;
	//para.pJet2->setNodeMask(bValue ? ~0 : 0);

	osg::Switch* pJetSwitch = GetSelectedJet();
	if (!pJetSwitch)
		return;

	pJetSwitch->setValue(2, bValue);
	pJetSwitch->setValue(3, bValue);
}

void CameraPostionDlg::slotJet3(bool bValue)
{
	//TargetDataPara para;
	//GetSelectedLocalGeometryNodePara(para);

	//if (!para.pJet3) return;
	//para.pJet3->setNodeMask(bValue ? ~0 : 0);

	osg::Switch* pJetSwitch = GetSelectedJet();
	if (!pJetSwitch)
		return;

	pJetSwitch->setValue(4, bValue);
	pJetSwitch->setValue(5, bValue);
}

void CameraPostionDlg::slotJet4(bool bValue)
{
	//TargetDataPara para;
	//GetSelectedLocalGeometryNodePara(para);

	//if (!para.pJet4) return;
	//para.pJet4->setNodeMask(bValue ? ~0 : 0);

	osg::Switch* pJetSwitch = GetSelectedJet();
	if (!pJetSwitch)
		return;

	pJetSwitch->setValue(6, bValue);
	pJetSwitch->setValue(7, bValue);
}

void CameraPostionDlg::slotLoadJet()
{
	QString strNewJetPath;

	extern QString g_strLastDir;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Tecplot file (*.dat *.plt)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	strNewJetPath = fileName;

	osgEarth::QtGui::AnnotationVector annos;
	g_DataManager->getAnnotations(annos);
	TargetDataPara para;

	osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = NULL;

	for (osgEarth::QtGui::AnnotationVector::const_iterator it = annos.begin(); it != annos.end(); ++it)
	{
		if (g_DataManager->isSelected(*it))
		{
			pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>((*it).get());
			if (pLocalGeoNode != nullptr)
				break;
		}
	}

	if (pLocalGeoNode == nullptr)
		return;

	osgEarth::Annotation::AnnotationData* pData = pLocalGeoNode->getOrCreateAnnotationData();
	std::string strGuid = pData->getName();
	std::map<std::string, TargetDataPara>::iterator itr = TargetDataReader::s_mapPara.find(strGuid);
	if (itr != TargetDataReader::s_mapPara.end())
	{
		itr->second.strJetPath = strNewJetPath;
		TargetDataPara& para = itr->second;
		TargetDataReader targetReader;

		osg::Node* pNode = targetReader.GetGeode(para);
		pLocalGeoNode->setNode(pNode);

		ui.checkBox_Jet1->setCheckable(true);
		ui.checkBox_Jet2->setCheckable(true);
		ui.checkBox_Jet3->setCheckable(true);
		ui.checkBox_Jet4->setCheckable(true);

		ui.checkBox_Jet1->setChecked(true);
		ui.checkBox_Jet2->setChecked(true);
		ui.checkBox_Jet3->setChecked(true);
		ui.checkBox_Jet4->setChecked(true);

		emit g_DataManager->mapChanged();
	}
}