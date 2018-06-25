#ifndef ANIMATIONSETTINGSDLG_H
#define ANIMATIONSETTINGSDLG_H

#include <QDialog>
#include "ui_AnimationSettingsDlg.h"

class AnimationSettingsDlg : public QDialog
{
	Q_OBJECT

public:
	AnimationSettingsDlg(QWidget *parent = 0);
	~AnimationSettingsDlg();

protected slots:

	void slotSetSavePath();

private:
	Ui::AnimationSettingsDlg ui;
};

#endif // ANIMATIONSETTINGSDLG_H
