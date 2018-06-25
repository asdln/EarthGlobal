#ifndef SETSTARTFRAMEDLG_H
#define SETSTARTFRAMEDLG_H

#include <QDialog>
#include "ui_SetStartFrameDlg.h"

class SetStartFrameDlg : public QDialog
{
	Q_OBJECT

public:
	SetStartFrameDlg(QWidget *parent = 0);
	~SetStartFrameDlg();

public:
	Ui::SetStartFrameDlg ui;
};

#endif // SETSTARTFRAMEDLG_H
