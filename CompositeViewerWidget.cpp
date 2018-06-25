#include "CompositeViewerWidget.h"
#include <QtWidgets/QGridLayout>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/MultiTouchTrackballManipulator>

CompositeViewerWidget::CompositeViewerWidget(const QVector<osgEarth::QtGui::ViewerWidget*>& pVecCentralWidget, QWidget* parent, Qt::WindowFlags f, osgViewer::ViewerBase::ThreadingModel threadingModel)
: QWidget(parent, f)
{
	setThreadingModel(threadingModel);

	// disable the default setting of viewer.done() by pressing Escape.
	setKeyEventSetsDone(0);

	osgEarth::QtGui::ViewVector views;
	pVecCentralWidget[0]->getViews(views);
	addView(views[0]);

	pVecCentralWidget[1]->getViews(views);
	addView(views[0]);

	pVecCentralWidget[2]->getViews(views);
	addView(views[0]);

	pVecCentralWidget[3]->getViews(views);
	addView(views[0]);

	// 		QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("cow.osgt"));
	// 		QWidget* widget2 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("glider.osgt"));
	// 		QWidget* widget3 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("axes.osgt"));
	//QWidget* widget4 = addViewWidget( createGraphicsWindow(0,0,100,100), osgDB::readNodeFile("fountain.osgt") );
	// 		QWidget* popupWidget = addViewWidget(createGraphicsWindow(900, 100, 320, 240, "Popup window", true), osgDB::readNodeFile("dumptruck.osgt"));
	// 		popupWidget->show();

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(pVecCentralWidget[0], 0, 0);
	grid->addWidget(pVecCentralWidget[1], 0, 1);
	grid->addWidget(pVecCentralWidget[2], 1, 0);
	grid->addWidget(pVecCentralWidget[3], 1, 1);
	setLayout(grid);

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}

QWidget* CompositeViewerWidget::addViewWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene)
{
	osgViewer::View* view = new osgViewer::View;
	addView(view);

	osg::Camera* camera = view->getCamera();
	camera->setGraphicsContext(gw);

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

	view->setSceneData(scene);
	view->addEventHandler(new osgViewer::StatsHandler);
	view->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
	gw->setTouchEventsEnabled(true);
	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* CompositeViewerWidget::createGraphicsWindow(int x, int y, int w, int h, const std::string& name, bool windowDecoration)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}

void CompositeViewerWidget::paintEvent(QPaintEvent* event)
{
	frame();
}