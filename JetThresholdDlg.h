#ifndef JETTHRESHOLDDLG_H
#define JETTHRESHOLDDLG_H

#include <QDialog>
#include "ui_JetThresholdDlg.h"

class JetThresholdDlg : public QDialog
{
	Q_OBJECT

public:
	JetThresholdDlg(double dValue, QWidget *parent = 0);
	~JetThresholdDlg();

public:
	Ui::JetThresholdDlg ui;
};

#endif // JETTHRESHOLDDLG_H
