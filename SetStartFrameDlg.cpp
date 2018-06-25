#include "SetStartFrameDlg.h"

SetStartFrameDlg::SetStartFrameDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.spinBox->setRange(0, 9999999);
}

SetStartFrameDlg::~SetStartFrameDlg()
{

}
