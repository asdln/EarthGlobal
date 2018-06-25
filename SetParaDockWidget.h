#ifndef SETPARADOCKWIDGET_H
#define SETPARADOCKWIDGET_H

#include <QDockWidget>
#include "ui_SetParaDockWidget.h"

class AirDataParaWidget;
class TargetPosition;

class SetParaDockWidget : public QDockWidget
{
	Q_OBJECT

public:
	SetParaDockWidget(const QString strTitle, QWidget *parent = 0);
	~SetParaDockWidget();

public slots:

	void slotOnSelectionChanged();

protected:

	QTabWidget* m_pTabWidget;

	AirDataParaWidget* m_pAirDataParaWidget;
	TargetPosition* m_pTargetPositionWidget;

private:
	//Ui::SetParaDockWidget ui;
};

#endif // SETPARADOCKWIDGET_H
