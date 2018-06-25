#include "AnimationSettingsDlg.h"
#include "Document.h"

#include <QtWidgets/QFileDialog>

AnimationSettingsDlg::AnimationSettingsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Document* pDocument = Document::Instance();
	ui.lineEdit_Path->setText(pDocument->GetSavePath());
}

AnimationSettingsDlg::~AnimationSettingsDlg()
{

}

void AnimationSettingsDlg::slotSetSavePath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	if (dir.isNull())
	{
		return;
	}

	ui.lineEdit_Path->setText(dir);
	
	Document* pDocument = Document::Instance();
	pDocument->SetSavePath(dir);
}