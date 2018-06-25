#ifndef PROGRESSNUMBERWIDGET_H
#define PROGRESSNUMBERWIDGET_H

#include <QDialog>
#include "ui_ProgressNumberWidget.h"

class ProgressNumberWidget : public QDialog
{
	Q_OBJECT

public:
	ProgressNumberWidget(QWidget *parent = 0);
	~ProgressNumberWidget();

public:
	Ui::ProgressNumberWidget ui;
};

#endif // PROGRESSNUMBERWIDGET_H
