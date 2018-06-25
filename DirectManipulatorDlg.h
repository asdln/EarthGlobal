#ifndef DIRECTMANIPULATORDLG_H
#define DIRECTMANIPULATORDLG_H

#include <QDialog>
#include "ui_DirectManipulatorDlg.h"

class DirectManipulatorDlg : public QDialog
{
	Q_OBJECT

public:
	DirectManipulatorDlg(QWidget *parent = 0);
	~DirectManipulatorDlg();

public slots:

	void slotSetPos();

	void slotRevert();

private:
	Ui::DirectManipulatorDlg ui;
};

#endif // DIRECTMANIPULATORDLG_H
