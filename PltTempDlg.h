#ifndef PLTTEMPDLG_H
#define PLTTEMPDLG_H

#include <QDialog>
#include "ui_PltTempDlg.h"

class PltTempDlg : public QDialog
{
	Q_OBJECT

public:
	PltTempDlg(QWidget *parent = 0);
	~PltTempDlg();

	void GetPara(double& dStart, double& dEnd, double& dfen, double& dfa);

public slots:

	void slotPushButtonPath();

public:

	Ui::PltTempDlg ui;

private:
	
	double m_dStart;
	double m_dEnd;
	double m_dFen;
	double m_dFa;
};

#endif // PLTTEMPDLG_H
