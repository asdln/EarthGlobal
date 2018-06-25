#include "DirectManipulatorDlg.h"
#include "DirectEarthManipulator.h"
#include "osgViewer/Viewer"
#include "osgEarthUtil/EarthManipulator"

extern osgViewer::Viewer* g_viewerMain;

DirectManipulatorDlg::DirectManipulatorDlg(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit_EyeLon->setText(QString::number(0.0));
	ui.lineEdit_EyeLat->setText(QString::number(0.0));
	ui.lineEdit_EyeHei->setText(QString::number(10000.0));

	ui.lineEdit_Angle->setText(QString::number(0.0));
	ui.lineEdit_TargetLon->setText(QString::number(0.0));
	ui.lineEdit_TargetLat->setText(QString::number(0.0));
	ui.lineEdit_TargetHei->setText(QString::number(1000.0));

	connect(ui.pushButton_Set, SIGNAL(clicked()), this, SLOT(slotSetPos()));
	connect(ui.pushButton_Revert, SIGNAL(clicked()), this, SLOT(slotRevert()));
}

DirectManipulatorDlg::~DirectManipulatorDlg()
{

}

void DirectManipulatorDlg::slotSetPos()
{
	double dEyeLon = ui.lineEdit_EyeLon->text().toDouble();
	double dEyeLat = ui.lineEdit_EyeLat->text().toDouble();
	double dEyeHei = ui.lineEdit_EyeHei->text().toDouble();

	double dAngle = ui.lineEdit_Angle->text().toDouble();

	double dTargetLon = ui.lineEdit_TargetLon->text().toDouble();
	double dTargetLat = ui.lineEdit_TargetLat->text().toDouble();
	double dTargetHei = ui.lineEdit_TargetHei->text().toDouble();

	DirectEarthManipulator* pManipulator = new DirectEarthManipulator;
	pManipulator->SetPosition(dEyeLon, dEyeLat, dEyeHei, dAngle, dTargetLon, dTargetLat, dTargetHei);
	g_viewerMain->setCameraManipulator(pManipulator);
}

void DirectManipulatorDlg::slotRevert()
{
	g_viewerMain->setCameraManipulator(new osgEarth::Util::EarthManipulator());

	osg::Camera* pCamera = g_viewerMain->getCamera();
	pCamera->setCullingMode(osg::CullingSet::NO_CULLING);

// 	pCamera->setCullingMode(pCamera->getCullingMode() &
// 		~osg::CullSettings::SMALL_FEATURE_CULLING);
}