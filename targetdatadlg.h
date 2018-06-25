#ifndef TARGETDATADLG_H
#define TARGETDATADLG_H

#include <QDialog>
#include "ui_targetdatadlg.h"

class TargetDataDlg : public QDialog
{
	Q_OBJECT

public:
	TargetDataDlg(QWidget *parent = 0);
	~TargetDataDlg();

	QString m_strTmp;
	QString m_strTRI;

	double GetX();
	double GetY();
	double GetZ();

	bool GetAuxPara(double& dStart, double& dEnd, double& dfen, double& dfa);

protected:

	double m_dStart;
	double m_dEnd;
	double m_dFen;
	double m_dFa;

public slots:

	void slotButtonClicked_tmp();

	void slotButtonClicked_TRI();

	void slotButtonClicked_LoadJet();

	void slotButtonClicked_LoadPlt();

	void slotAddJet();

	void slotDeleteJet();

public:
	Ui::TargetDataDlg ui;

	int m_nCols;
};

#endif // TARGETDATADLG_H
