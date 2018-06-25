#ifndef CAMERAPOSTIONDLG_H
#define CAMERAPOSTIONDLG_H

#include <QDialog>
#include "ui_CameraPostionDlg.h"
#include <osgEarth/Viewpoint>
#include <QtWidgets/QListWidget>
#include "TargetDataReader.h"

class CameraPostionDlg : public QDialog
{
	Q_OBJECT

public:
	CameraPostionDlg(QWidget *parent = 0);
	~CameraPostionDlg();

public:

signals :

	void sigSetViewPoint(osgEarth::Viewpoint* pViewPoint);

public slots:

	void slotSetWin();

	void slotRefreshInfo();

	void slotCopy();

	void slotSet();

	void slotSetNewPosition();

	void refreshTargetList();

	void onMapChanged();
	void onSelectionChanged(/*const AnnotationVector& selection*/);
	void onItemChanged(QListWidgetItem*);

	void onListSelectionChanged();

	void onItemDoubleClicked(QListWidgetItem* item);

	void slotTrace();

	void slotFocus();

	void slotTest();

	void slotJet1(bool);

	void slotJet2(bool);

	void slotJet3(bool);

	void slotJet4(bool);

	void slotLoadJet();

	void slotSetRotateAngle();

protected:

	bool GetSelectedLocalGeometryNodePara(TargetDataPara& para);

	void Focus(double dLon, double dLat, double dH);

	osg::Switch* GetSelectedJet();

	int _updating;

	QListWidget*  m_targetListWidget;

private:
	Ui::CameraPostionDlg ui;
};

#endif // CAMERAPOSTIONDLG_H
