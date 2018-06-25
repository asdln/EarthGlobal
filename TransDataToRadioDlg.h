#ifndef TRANSDATATORADIODLG_H
#define TRANSDATATORADIODLG_H

#include <QDialog>
#include "ui_TransDataToRadioDlg.h"

class TransDataToRadioDlg : public QDialog
{
	Q_OBJECT

public:
	TransDataToRadioDlg(QWidget *parent = 0);
	~TransDataToRadioDlg();

public slots:

	void slotProcess();

	void slotSetTempFile();

	void slotSetTransRatioFile();

	void slotSetOutputFile();

public:
	Ui::TransDataToRadioDlg ui;
};

#endif // TRANSDATATORADIODLG_H
