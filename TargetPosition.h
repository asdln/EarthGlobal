#ifndef TARGETPOSITION_H
#define TARGETPOSITION_H

#include <QWidget>
#include "ui_TargetPosition.h"

class TargetPosition : public QWidget
{
	Q_OBJECT

public:
	TargetPosition(QWidget *parent = 0);
	~TargetPosition();

public slots:

	void slotSetNewPosition();

	void slotOnSelectionChanged();

private:
	Ui::TargetPosition ui;
};

#endif // TARGETPOSITION_H
