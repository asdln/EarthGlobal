#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>
#include <QtCore/QEvent>

class KeyPressEater : public QObject
{
	Q_OBJECT

public:

	KeyPressEater(QObject* parent = NULL);
	~KeyPressEater();

Q_SIGNALS:

	void sigEscPressed();

protected:

	bool eventFilter(QObject *obj, QEvent *event);
};

#endif // KEYPRESSEATER_H
