#ifndef COMPOSITEVIEWERWIDGET_H
#define COMPOSITEVIEWERWIDGET_H

#include <QWidget>
#include <osgViewer/CompositeViewer>
#include "osgEarthQt/ViewerWidget"

class CompositeViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
	CompositeViewerWidget(const QVector<osgEarth::QtGui::ViewerWidget*>& pVecCentralWidget, QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);

	QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene);

	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

	virtual void paintEvent(QPaintEvent* event);

protected:

	QTimer _timer;
};

#endif // COMPOSITEVIEWERWIDGET_H
