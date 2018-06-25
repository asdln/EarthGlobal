#include "NewProjectDlg.h"
#include "osgEarth/DataParaManager.h"
#include <QtWidgets/QMdiSubWindow>
#include <QtCore/QtMath>
#include <osgEarthQt/ViewerWidget>
#include <QtWidgets/QFileDialog>
#include "Document.h"

extern QString g_strLastDir;
extern osgViewer::Viewer* g_viewerMain;
extern QMdiSubWindow* g_pMdiSubWindow;
extern osgEarth::QtGui::ViewerWidget* g_viewerWidget;

NewProjectDlg::NewProjectDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit_RadioMin->setText(QString::number(DataParaManager::Instance()->GetRadioMin()));
	ui.lineEdit_RadioMax->setText(QString::number(DataParaManager::Instance()->GetRadioMax()));

//	ui.lineEdit_TemperatureMin->setText(QString::number(DataParaManager::Instance()->GetTemperatureMin()));
//	ui.lineEdit_TemperatureMax->setText(QString::number(DataParaManager::Instance()->GetTemperatureMax()));

	std::vector<osgViewer::View*> vecViews;
	g_viewerMain->getViews(vecViews);
	osgViewer::View* pView = vecViews[0];

	osg::Camera* pCamera = pView->getCamera();

	double fovy;
	double aspectRatio;
	double zNear;
	double zFar;
	pCamera->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

	ui.lineEdit_VerVPCur->setText(QString::number(fovy * 2.0));

	double dWid = g_pMdiSubWindow->widget()->width();
	double dHei = g_pMdiSubWindow->widget()->width();

	double dHorAngle = 90.0;
	dHorAngle = qAtan(dWid / dHei * qTan(fovy / 180.0 * 3.1415926)) * 360.0 / 3.1415926;
	ui.lineEdit_HorVPCur->setText(QString::number(dHorAngle));

	int nWinWid = g_viewerWidget->rect().width();
	int nWinHei = g_viewerWidget->rect().height();

	ui.lineEdit_HorRes->setText(QString::number(nWinWid));
	ui.lineEdit_VerRes->setText(QString::number(nWinHei));

	double dStart = 10.78;
	double dEnd = 11.28;
	double dFen = 1.0;
	double dFa = 0.6;

	ui.lineEdit_start->setText(QString::number(dStart));
	ui.lineEdit_End->setText(QString::number(dEnd));

	ui.lineEdit_fen->setText(QString::number(dFen));
	ui.lineEdit_fa->setText(QString::number(dFa));

	QStringList strList;
	strList.push_back(QString::fromLocal8Bit("x"));
	strList.push_back(QString::fromLocal8Bit("y"));
	strList.push_back(QString::fromLocal8Bit("z"));

	strList.push_back(QString::fromLocal8Bit("俯仰角"));
	strList.push_back(QString::fromLocal8Bit("偏航角"));
	strList.push_back(QString::fromLocal8Bit("翻滚角"));

	m_nCols = 6;
	ui.tableWidget_JetPara->setColumnCount(m_nCols);
	ui.tableWidget_JetPara->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_JetPara->setSelectionMode(QAbstractItemView::SingleSelection);

	for (int i = 0; i < m_nCols; i++)
	{
		ui.tableWidget_JetPara->setColumnWidth(i, 80);
	}
	ui.tableWidget_JetPara->setHorizontalHeaderLabels(strList);

	connect(ui.pushButton_AddJet, SIGNAL(clicked()), this, SLOT(slotAddJet()));
	connect(ui.pushButton_RemoveJet, SIGNAL(clicked()), this, SLOT(slotDeleteJet()));

	connect(ui.pushButton_ProjectPath, SIGNAL(clicked()), this, SLOT(slotProjectPath()));
	connect(ui.pushButton_CameraPath, SIGNAL(clicked()), this, SLOT(slotCameraPath()));
	connect(ui.pushButton_TargetPath, SIGNAL(clicked()), this, SLOT(slotTargetPath()));
	connect(ui.pushButton_AirDir, SIGNAL(clicked()), this, SLOT(slotAirDataDir()));
	connect(ui.pushButton_EarthRadio, SIGNAL(clicked()), this, SLOT(slotEarthRadio()));
	connect(ui.pushButton_tmp, SIGNAL(clicked()), this, SLOT(slottmp()));
	connect(ui.pushButton_TRI, SIGNAL(clicked()), this, SLOT(slotTRI()));
	connect(ui.pushButton_Plt, SIGNAL(clicked()), this, SLOT(slotPlt()));
	connect(ui.pushButton_LoadJet, SIGNAL(clicked()), this, SLOT(slotLoadJet()));

	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(slotPushButtonOK()));
}

NewProjectDlg::~NewProjectDlg()
{

}

void NewProjectDlg::slotProjectPath()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
		"/home",
		tr("project (*.xml)"));

	ui.lineEdit_ProjectPath->setText(fileName);

	QFileInfo fileInfo(fileName);
	Document* pDocument = Document::Instance();
	pDocument->SetSavePath(fileInfo.absolutePath());
}

void NewProjectDlg::slotCameraPath()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("传感器轨迹文件"),
		g_strLastDir,
		"path (*.txt)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_CameraTrack->setText(fileName);
}

void NewProjectDlg::slotTargetPath()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("目标轨迹文件"),
		g_strLastDir,
		"path (*.txt)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_TargetTrack->setText(fileName);
}

void NewProjectDlg::slotAirDataDir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	ui.lineEdit_AirDir->setText(dir);
 }

void NewProjectDlg::slotEarthRadio()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("地表辐射"),
		g_strLastDir,
		"tif (*.tif)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_EarthRadio->setText(fileName);
}

void NewProjectDlg::slotAddJet()
{
	ui.tableWidget_JetPara->insertRow(0);

	for (int i = 0; i < m_nCols; i++)
	{
		QTableWidgetItem* pItem = new QTableWidgetItem;
		pItem->setText("0.0");

		ui.tableWidget_JetPara->setItem(0, i, pItem);
	}
}

void NewProjectDlg::slotDeleteJet()
{
	QList<QTableWidgetItem *> listItems = ui.tableWidget_JetPara->selectedItems();
	if (listItems.isEmpty())
		return;

	int nRow = listItems[0]->row();
	ui.tableWidget_JetPara->removeRow(nRow);
}

void NewProjectDlg::slotPlt()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("加载plt数据"),
		g_strLastDir,
		"plt (*.plt)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_Plt->setText(fileName);
}

void NewProjectDlg::slottmp()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("加载tmp数据"),
		g_strLastDir,
		"tmp (*.tmp)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_tmp->setText(fileName);
}

void NewProjectDlg::slotTRI()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("加载TRI数据"),
		g_strLastDir,
		"TRI (*.TRI)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_TRI->setText(fileName);
}

void NewProjectDlg::slotLoadJet()
{
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("加载尾焰"),
		g_strLastDir,
		"PLT (*.plt)");

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_LoadJet->setText(fileName);
}

void NewProjectDlg::slotPushButtonOK()
{


	QDialog::accept();
}
