#include "SetParaDockWidget.h"

#include <osgEarthQt/DataManager>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/LocalGeometryNode>

#include "TargetPosition.h"
#include "AirDataParaWidget.h"

extern osgEarth::QtGui::DataManager* g_DataManager;

SetParaDockWidget::SetParaDockWidget(const QString strTitle, QWidget *parent)
: QDockWidget(strTitle, parent)
{
	m_pTabWidget = new QTabWidget;
	
	QObject::connect(g_DataManager, SIGNAL(selectionChanged()), this, SLOT(slotOnSelectionChanged()));

	m_pAirDataParaWidget = new AirDataParaWidget;
//	m_pTargetPositionWidget = new TargetPosition();

//	m_pTabWidget->addTab(m_pTargetPositionWidget, QString::fromLocal8Bit("目标参数"));
	m_pTabWidget->addTab(m_pAirDataParaWidget, QString::fromLocal8Bit("大气参数"));

	setWidget(m_pTabWidget);
}

SetParaDockWidget::~SetParaDockWidget()
{

}

void SetParaDockWidget::slotOnSelectionChanged()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	g_DataManager->getAnnotations(out_annotations);

	osgEarth::Annotation::AnnotationNode* pCurrentAnnotationNode = NULL;

	for(int i = 0; i < out_annotations.size(); i++)
	{
		if(g_DataManager->isSelected(out_annotations[i]))
		{
			pCurrentAnnotationNode = out_annotations[i];
			break;
		}
	}

	if (pCurrentAnnotationNode == NULL)
	{
		m_pAirDataParaWidget->setEnabled(false);
		//m_pTargetPositionWidget->setEnabled(false);
		return;
	}
	else
	{
		//大气
		osgEarth::Annotation::FeatureNode* pFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(pCurrentAnnotationNode);
		//目标
		osgEarth::Annotation::LocalGeometryNode* pLocalGeoNode = dynamic_cast<osgEarth::Annotation::LocalGeometryNode*>(pCurrentAnnotationNode);

		if (pFeatureNode)
		{
			m_pTabWidget->setCurrentIndex(1);
			m_pAirDataParaWidget->setEnabled(true);
			//m_pTargetPositionWidget->setEnabled(false);
			m_pAirDataParaWidget->slotOnSelectionChanged();
		}

		if (pLocalGeoNode)
		{
			m_pTabWidget->setCurrentIndex(0);
			m_pAirDataParaWidget->setEnabled(false);
			//m_pTargetPositionWidget->setEnabled(true);
			//m_pTargetPositionWidget->slotOnSelectionChanged();
		}
	}
}
