#include "AirDataDlg.h"
#include "osgEarth/DataParaManager.h"
#include "AirDataReader.h"
#include <QtWidgets/QFileDialog>

AirDataDlg::AirDataDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

AirDataDlg::~AirDataDlg()
{

}

void AirDataDlg::slotPushButtonAddData()
{
	extern QString g_strLastDir;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Images (*.txt)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.label_filePath->setText(fileName);
}
