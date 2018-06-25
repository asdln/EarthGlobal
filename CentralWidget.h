#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <osgEarthQt/ViewerWidget>

#include <QWidget>

#include <osgViewer/ViewerBase>

class CentralWidget : public osgEarth::QtGui::ViewerWidget
{
	Q_OBJECT

public:
	CentralWidget(osgViewer::ViewerBase* viewer);
	~CentralWidget();


	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual bool gestureEvent(QGestureEvent* event);

private:
};

#endif // CENTRALWIDGET_H
