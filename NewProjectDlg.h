#ifndef NEWPROJECTDLG_H
#define NEWPROJECTDLG_H

#include <QDialog>
#include "ui_NewProjectDlg.h"

class NewProjectDlg : public QDialog
{
	Q_OBJECT

public:
	NewProjectDlg(QWidget *parent = 0);
	~NewProjectDlg();

public slots:

	void slotProjectPath();

	void slotCameraPath();

	void slotTargetPath();

	void slotAirDataDir();

	void slotEarthRadio();

	void slottmp();

	void slotTRI();

	void slotPlt();

	void slotAddJet();

	void slotDeleteJet();

	void slotLoadJet();

	void slotPushButtonOK();

public:
	Ui::NewProjectDlg ui;

protected:

	int m_nCols;
};

#endif // NEWPROJECTDLG_H
