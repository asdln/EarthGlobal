#ifndef AIRDATAPARAWIDGET_H
#define AIRDATAPARAWIDGET_H

#include <QWidget>
#include "ui_AirDataParaWidget.h"

class AirDataParaWidget : public QWidget
{
	Q_OBJECT

public:
	AirDataParaWidget(QWidget *parent = 0);
	~AirDataParaWidget();

public slots:

	void slotSet();

	void slotOnSelectionChanged();

private:
	Ui::AirDataParaWidget ui;
};

#endif // AIRDATAPARAWIDGET_H
