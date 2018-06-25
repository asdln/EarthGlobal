#include "AirDataParaWidget.h"
#include <osgEarthQt/Common>
#include <osgEarthQt/DataManager>
#include <osgEarthAnnotation/FeatureNode>

extern osgEarth::QtGui::DataManager* g_DataManager;
osgEarth::Features::Feature* GetAirFeature(double dTransparent);

AirDataParaWidget::AirDataParaWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AirDataParaWidget::~AirDataParaWidget()
{

}

void AirDataParaWidget::slotSet()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	g_DataManager->getAnnotations(out_annotations);

	osgEarth::Annotation::AnnotationNode* pCurrentAnnotationNode = NULL;

	for (int i = 0; i < out_annotations.size(); i++)
	{
		if (g_DataManager->isSelected(out_annotations[i]))
		{
			pCurrentAnnotationNode = out_annotations[i];
			break;
		}
	}

	osgEarth::Annotation::FeatureNode* pFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(pCurrentAnnotationNode);
	if (!pFeatureNode)
		return;

	double dTrans = ui.lineEdit_trans->text().toDouble();
	pFeatureNode->setFeature(GetAirFeature(dTrans));
}

void AirDataParaWidget::slotOnSelectionChanged()
{
	osgEarth::QtGui::AnnotationVector out_annotations;
	g_DataManager->getAnnotations(out_annotations);

	osgEarth::Annotation::AnnotationNode* pCurrentAnnotationNode = NULL;

	for (int i = 0; i < out_annotations.size(); i++)
	{
		if (g_DataManager->isSelected(out_annotations[i]))
		{
			pCurrentAnnotationNode = out_annotations[i];
			break;
		}
	}

	osgEarth::Annotation::FeatureNode* pFeatureNode = dynamic_cast<osgEarth::Annotation::FeatureNode*>(pCurrentAnnotationNode);
	if (!pFeatureNode)
		return;

	osgEarth::Annotation::Feature* pFeature = pFeatureNode->getFeature();

	osgEarth::Symbology::Geometry* poGeometry = pFeature->getGeometry();
	osgEarth::Symbology::MultiGeometry* poMultiGeometry = dynamic_cast<osgEarth::Symbology::MultiGeometry*>(poGeometry);
	if (!poMultiGeometry)
		return;
	
	osgEarth::Symbology::GeometryCollection& geoCollection = poMultiGeometry->getComponents();
	if (geoCollection.empty())
		return;

	osgEarth::Symbology::Geometry* poFirstGeometry = geoCollection.at(0);
	double dTrans = poFirstGeometry->m_color->a();
	ui.lineEdit_trans->setText(QString::number(dTrans));
}