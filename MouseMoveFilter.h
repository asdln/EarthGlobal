#ifndef MOUSEMOVEFILTER_H
#define MOUSEMOVEFILTER_H

#include <QObject>

class MouseMoveFilter : public QObject
{
	Q_OBJECT

public:

	MouseMoveFilter(QObject* parent = NULL);
	~MouseMoveFilter();

	static bool m_bIsActiving;

protected:

	bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MOUSEMOVEFILTER_H
