#ifndef AIRDATADLG_H
#define AIRDATADLG_H

#include <QDialog>
#include "ui_AirDataDlg.h"

class AirDataDlg : public QDialog
{
	Q_OBJECT

public slots:

	void slotPushButtonAddData();

public:
	AirDataDlg(QWidget *parent = 0);
	~AirDataDlg();

public:
	Ui::AirDataDlg ui;
};

#endif // AIRDATADLG_H
