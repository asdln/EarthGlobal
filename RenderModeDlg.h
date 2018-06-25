#ifndef RENDERMODEDLG_H
#define RENDERMODEDLG_H

#include <QDialog>
#include "ui_RenderModeDlg.h"

class RenderModeDlg : public QDialog
{
	Q_OBJECT

public:
	RenderModeDlg(QWidget *parent = 0);
	~RenderModeDlg();

public:
	Ui::RenderModeDlg ui;
};

#endif // RENDERMODEDLG_H
