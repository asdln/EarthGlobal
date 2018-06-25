#include "KeyPressEater.h"
#include <QtGui/QKeyEvent>
#include <QtWidgets/QAction>


KeyPressEater::KeyPressEater(QObject *parent)
	: QObject(parent)
{

}

KeyPressEater::~KeyPressEater()
{

}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if(keyEvent->key() == Qt::Key_Escape)
		{
			emit sigEscPressed();
		}
	}

	// standard event processing
	return QObject::eventFilter(obj, event);
}