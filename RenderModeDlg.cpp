#include "RenderModeDlg.h"
#include "osgEarth/DataParaManager.h"

RenderModeDlg::RenderModeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	if (DataParaManager::Instance()->IsRGBMode())
	{
		ui.radioButton_Gray->setChecked(false);
		ui.radioButton_RGB->setChecked(true);
	}
	else
	{
		ui.radioButton_Gray->setChecked(true);
		ui.radioButton_RGB->setChecked(false);
	}

	ui.lineEdit_RadioMin->setText(QString::number(DataParaManager::Instance()->GetRadioMin()));
	ui.lineEdit_RadioMax->setText(QString::number(DataParaManager::Instance()->GetRadioMax()));

	ui.lineEdit_TemperatureMin->setText(QString::number(DataParaManager::Instance()->GetTemperatureMin()));
	ui.lineEdit_TemperatureMax->setText(QString::number(DataParaManager::Instance()->GetTemperatureMax()));
}

RenderModeDlg::~RenderModeDlg()
{

}
