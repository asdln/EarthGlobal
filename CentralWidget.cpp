#include "CentralWidget.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>
#include <osgEarthQt/DataManager>
#include "osgEarth/DataParaManager.h"
#include <QMouseEvent>

#include <gdal_priv.h>

extern bool g_bIsFixedAngldMode;

CentralWidget::CentralWidget(osgViewer::ViewerBase* viewer)
: osgEarth::QtGui::ViewerWidget(viewer)
{
	
}

CentralWidget::~CentralWidget()
{

}

void CentralWidget::keyPressEvent(QKeyEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::keyPressEvent(event);
}

void CentralWidget::keyReleaseEvent(QKeyEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::keyReleaseEvent(event);
}

void CentralWidget::mousePressEvent(QMouseEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::mousePressEvent(event);
}

extern osgEarth::QtGui::DataManager* g_DataManager;
extern QDialog* g_pDetectToolDlg;
extern QTextEdit* g_pTextEdit;
extern QString g_strAirTarget;

QString g_strImageDetect;
void CentralWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	g_strImageDetect.clear();

	QString strLonAndLat;

	QString strAirFixedModel;

	//计算image探针
	if (g_pDetectToolDlg && !g_pDetectToolDlg->isHidden())
	{
		std::vector<osgViewer::View*> vecViews;
		getViews(vecViews);
		osgViewer::View* pView = vecViews[0];

		osg::Vec3d world;
		osgEarth::GeoPoint mapPoint;
		if (g_DataManager->MapNode()->getTerrain()->getWorldCoordsUnderMouse(pView->asView(), event->pos().rx(), height() - event->pos().ry(), world))
		{
			mapPoint.fromWorld(g_DataManager->MapNode()->getMapSRS(), world);
			osg::Vec3d vecPos = mapPoint.vec3d();

			osgEarth::ImageLayerVector out_list;
			g_DataManager->map()->getImageLayers(out_list);

			for (int i = 0; i < out_list.size(); i++)
			{
				osgEarth::ImageLayer* pImageLayer = out_list[i].get();
				std::string strGuid = pImageLayer->getTileSource()->GetGuid();
				void* pInternalHandle = DataParaManager::Instance()->GetMapPointer(strGuid);

				if (!pInternalHandle)
					continue;

				double geotransform[6];
				double invtransform[6];

				GDALDataset* pGDALDataset = static_cast<GDALDataset*>(pInternalHandle);
				pGDALDataset->GetGeoTransform(geotransform);
				GDALInvGeoTransform(geotransform, invtransform);

				int x = invtransform[0] + invtransform[1] * vecPos.x() + invtransform[2] * vecPos.y();
				int y = invtransform[3] + invtransform[4] * vecPos.x() + invtransform[5] * vecPos.y();

				//Account for slight rounding errors.  If we are right on the edge of the dataset, clamp to the edge
				double eps = 0.0001;
				if (osg::equivalent(x, 0, eps)) x = 0;
				if (osg::equivalent(y, 0, eps)) y = 0;
				if (osg::equivalent(x, (double)pGDALDataset->GetRasterXSize(), eps)) x = pGDALDataset->GetRasterXSize();
				if (osg::equivalent(y, (double)pGDALDataset->GetRasterYSize(), eps)) y = pGDALDataset->GetRasterYSize();

				unsigned short nValue = 0;
				double dValue = nValue;

				if (x >= 0 && x < pGDALDataset->GetRasterXSize() && y >= 0 && y < pGDALDataset->GetRasterYSize())
				{
					GDALRasterBand* pRasterBand = pGDALDataset->GetRasterBand(1);
					pRasterBand->RasterIO(GF_Read, x, y, 1, 1, &nValue, 1, 1, GDT_UInt16, 0, 0);
					dValue = nValue / 1000.0;

					if (DataParaManager::Instance()->IsFixedAngleMode())
					{
						double dRadio, dTrans;
						double dAirLon, dAriLat;
						DataParaManager::Instance()->GetFixedAngleValue(vecPos.x(), vecPos.y(), 100.0, dRadio, dTrans, &dAirLon, &dAriLat);
						dValue = dRadio + dTrans * dValue;

						strAirFixedModel = QString::fromLocal8Bit("大气, 辐射: ") + QString::number(dRadio)
							+ QString::fromLocal8Bit(", 透过率: ") + QString::number(dTrans) + QString::fromLocal8Bit(", 经度: ")
							+ QString::number(dAirLon) + QString::fromLocal8Bit(", 纬度: ") + QString::number(dAriLat);
					}

					QString strDetect = pImageLayer->getName().c_str();
					strDetect += ": ";
					strDetect += QString::number(dValue);
					strDetect += "\r\n";

					g_strImageDetect += strDetect;
				}
			}

			strLonAndLat = QString::fromLocal8Bit("经度：") + QString::number(vecPos.x())
				+ QString::fromLocal8Bit(" 纬度：") + QString::number(vecPos.y()) + "\r\n";
		}

		QString strFinal = strLonAndLat + g_strImageDetect + g_strAirTarget;
		strFinal += "\r\n";
		strFinal += strAirFixedModel;
		g_pTextEdit->setText(strFinal);
	}

	return ViewerWidget::mouseReleaseEvent(event);
}

void CentralWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::mouseDoubleClickEvent(event);
}

void CentralWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::mouseMoveEvent(event);
}

void CentralWidget::wheelEvent(QWheelEvent* event)
{
	if (g_bIsFixedAngldMode)
		return;

	return ViewerWidget::wheelEvent(event);
}

bool CentralWidget::gestureEvent(QGestureEvent* event)
{
	if (g_bIsFixedAngldMode)
		return true;

	return ViewerWidget::gestureEvent(event);
}
