#include "JetThresholdDlg.h"

JetThresholdDlg::JetThresholdDlg(double dValue, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setText(QString::number(dValue));

	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.pushButton_Cancel, SIGNAL(clicked()), this, SLOT(reject()));

	setWindowTitle(QString::fromLocal8Bit("Œ≤—Ê„–÷µ"));
}

JetThresholdDlg::~JetThresholdDlg()
{

}
