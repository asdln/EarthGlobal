#include "TransDataToRadioDlg.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
extern QString g_strLastDir;

TransDataToRadioDlg::TransDataToRadioDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.doubleSpinBox_StartWave->setValue(10.78);
	ui.doubleSpinBox_EndWave->setValue(11.28);

	ui.lineEdit_Output->setReadOnly(true);
	ui.lineEdit_TempFile->setReadOnly(true);
	ui.lineEdit_TransRatio->setReadOnly(true);

	QObject::connect(ui.pushButton_Do, SIGNAL(clicked()), this, SLOT(slotProcess()));
	QObject::connect(ui.pushButton_Temp, SIGNAL(clicked()), this, SLOT(slotSetTempFile()));
	QObject::connect(ui.pushButton_TransRatio, SIGNAL(clicked()), this, SLOT(slotSetTransRatioFile()));
	QObject::connect(ui.pushButton_Output, SIGNAL(clicked()), this, SLOT(slotSetOutputFile()));
}

TransDataToRadioDlg::~TransDataToRadioDlg()
{

}

void TransDataToRadioDlg::slotSetTempFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开温度数据"),
									g_strLastDir,
									tr("Images (*.tif *.tiff)"));

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_TempFile->setText(fileName);
}

void TransDataToRadioDlg::slotSetTransRatioFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开发射率数据"),
														g_strLastDir,
													   tr("Images (*.tif *.tiff)"));

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_TransRatio->setText(fileName);
}

void TransDataToRadioDlg::slotSetOutputFile()
{
	QString strOutputFile = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("设置保存路径"),
								 "",
								 tr("Images (*.tif *.tiff)"));

	ui.lineEdit_Output->setText(strOutputFile);
}

void TransDataToRadioDlg::slotProcess()
{
	if(ui.lineEdit_TempFile->text().isEmpty()
	   || ui.lineEdit_TransRatio->text().isEmpty()
	   || ui.lineEdit_Output->text().isEmpty())
	{
		QMessageBox box;
		box.setText(QString::fromLocal8Bit("请指定路径"));
		box.exec();
		return;
	}

	return QDialog::accept();
}