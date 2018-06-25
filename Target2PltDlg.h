#ifndef TARGET2PLTDLG_H
#define TARGET2PLTDLG_H

#include <QDialog>
#include "ui_Target2PltDlg.h"

class Target2PltDlg : public QDialog
{
	Q_OBJECT

public:
	Target2PltDlg(QWidget *parent = 0);
	~Target2PltDlg();

public slots:

	void slotOpenTri();
	void slotOpenTmp();
	void slotOpenOutputFile();

	void slotOK();

public:
	Ui::Target2PltDlg ui;
};

#endif // TARGET2PLTDLG_H
