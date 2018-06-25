#ifndef OUTPUTDLG_H
#define OUTPUTDLG_H

#include <QDialog>
#include "ui_OutputDlg.h"
#include "PictureBox.h"

class OutputDlg : public QDialog
{
	Q_OBJECT

public:
	OutputDlg(QWidget *parent = 0);
	~OutputDlg();

public slots:

	void slotSetPath();

	void slotShowLastPic();

	void slotOutputLevel(int);

	void slotLeftAliment();

	void slotRightAliment();

	void slotOutputFloat(bool);

	void slotSelectAndOpen();

	void slotSetStartFrame(int);

protected:

	void showPic(const QString& strPath);

private:

	QString m_strLastOutputPath;

	PictureBox* m_PictureBox;

	Ui::OutputDlg ui;
};

#endif // OUTPUTDLG_H
