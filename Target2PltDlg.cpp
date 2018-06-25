#include "Target2PltDlg.h"
#include <QtWidgets/QFileDialog>
extern QString g_strLastDir;

Target2PltDlg::Target2PltDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit_Tri->setEnabled(false);
	ui.lineEdit_Tmp->setEnabled(false);
	ui.lineEdit_OutPlt->setEnabled(false);
}

Target2PltDlg::~Target2PltDlg()
{

}

void Target2PltDlg::slotOpenTri()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.tri *.TRI)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();
	ui.lineEdit_Tri->setText(fileName);
}

void Target2PltDlg::slotOpenTmp()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.tmp)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.lineEdit_Tmp->setText(fileName);
}

void Target2PltDlg::slotOpenOutputFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
		"/home",
		tr("tecplot (*.plt)"));

	if (fileName.isEmpty())
		return;

	ui.lineEdit_OutPlt->setText(fileName);
}

void Target2PltDlg::slotOK()
{
	QDialog::accept();
}