#include "MouseMoveFilter.h"

#include <QtCore/QEvent>

bool MouseMoveFilter::m_bIsActiving = false;

MouseMoveFilter::MouseMoveFilter(QObject *parent)
	: QObject(parent)
{

}

MouseMoveFilter::~MouseMoveFilter()
{

}

bool MouseMoveFilter::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::Enter)
	{
		m_bIsActiving = 1;
	}
	else if(event->type() == QEvent::Leave)
	{
		m_bIsActiving = 0;
	}

	// standard event processing
	return QObject::eventFilter(obj, event);
}