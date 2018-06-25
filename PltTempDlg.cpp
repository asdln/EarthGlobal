#include "PltTempDlg.h"
#include <QtWidgets/QFileDialog>

extern QString g_strLastDir;

PltTempDlg::PltTempDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_dStart = 10.78;
	m_dEnd = 11.28;
	m_dFen = 1.0;
	m_dFa = 0.6;

	ui.lineEdit_start->setText(QString::number(m_dStart));
	ui.lineEdit_End->setText(QString::number(m_dEnd));

	ui.lineEdit_fen->setText(QString::number(m_dFen));
	ui.lineEdit_fa->setText(QString::number(m_dFa));
}

PltTempDlg::~PltTempDlg()
{

}

void PltTempDlg::slotPushButtonPath()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Plt (*.plt)"));

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.label_Path->setText(fileName);
}

void PltTempDlg::GetPara(double& dStart, double& dEnd, double& dfen, double& dfa)
{
	dStart = ui.lineEdit_start->text().toDouble();
	dEnd = ui.lineEdit_End->text().toDouble();
	dfen = ui.lineEdit_fen->text().toDouble();
	dfa = ui.lineEdit_fa->text().toDouble();

	m_dStart = dStart;
	m_dEnd = dEnd;
	m_dFen = dfen;
	m_dFa = dfa;
}