#include "OutputDlg.h"

#include <osgViewer/Viewer>
#include <osgEarthQt/Common>
#include <osgViewer/ViewerBase>

#include <QtWidgets/QFileDialog>
#include "osgEarth/DataParaManager.h"
#include "osgEarthQt/DataManager"

#include <gdal_priv.h>
#include <gdalwarper.h>
#include <ogr_spatialref.h>
#include "ScreenCapture.h"
#include "osgEarthUtil/EarthManipulator"
#include "PathEarthManipulate.h"
#include "osgEarthQt/ViewerWidget"
#include "Document.h"

extern osgEarth::QtGui::DataManager* g_DataManager;
extern int g_nStartFrameIndex;
extern osgViewer::Viewer* g_viewerMain;
extern QString g_strLastDir;
extern int g_nOutputLevel;

//0是左对齐，1是右对齐
extern int g_nDataAliment;

CScreenCapture* g_pScreenCapture = NULL;

#include "AnimationController.h"

OutputDlg::OutputDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Document* pDocument = Document::Instance();
	ui.lineEdit_OutputPath->setText(pDocument->GetSavePath());

	m_PictureBox = new PictureBox();

	if (g_nDataAliment == 0)
	{
		ui.radioButton_Left->setChecked(true);
		ui.radioButton_Right->setChecked(false);
	}
	else
	{
		ui.radioButton_Left->setChecked(false);
		ui.radioButton_Right->setChecked(true);
	}

	ui.checkBox_OutputFloat->setChecked(g_nOutputLevel == 0);
	ui.comboBox_OutputLevel->setEnabled(g_nOutputLevel != 0);

	if (g_nOutputLevel != 0)
	{
		if(g_nOutputLevel == 8)
			ui.comboBox_OutputLevel->setCurrentIndex(0);

		if(g_nOutputLevel == 10)
			ui.comboBox_OutputLevel->setCurrentIndex(1);

		if(g_nOutputLevel == 12)
			ui.comboBox_OutputLevel->setCurrentIndex(2);

		if(g_nOutputLevel == 14)
			ui.comboBox_OutputLevel->setCurrentIndex(3);

		if(g_nOutputLevel == 16)
			ui.comboBox_OutputLevel->setCurrentIndex(4);
	}

}

OutputDlg::~OutputDlg()
{

}

void OutputDlg::slotOutputLevel(int)
{
	g_nOutputLevel = ui.comboBox_OutputLevel->currentText().toInt();
}

void OutputDlg::slotLeftAliment()
{
	g_nDataAliment = 0;
}

void OutputDlg::slotRightAliment()
{
	g_nDataAliment = 1;
}

void OutputDlg::slotOutputFloat(bool bValue)
{
	ui.comboBox_OutputLevel->setEnabled(!bValue);
	
	if (bValue)
	{
		g_nOutputLevel = 0;
	}
	else
	{
		g_nOutputLevel = ui.comboBox_OutputLevel->currentText().toInt();
	}
}

void OutputDlg::slotSetPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	if (dir.isNull())
	{
		return;
	}

	ui.lineEdit_OutputPath->setText(dir);
	Document* pDocument = Document::Instance();
	pDocument->SetSavePath(dir);
}

void OutputDlg::slotSelectAndOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Image (*.tif)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	showPic(fileName);
}

void OutputDlg::slotSetStartFrame(int nValue)
{
	g_nStartFrameIndex = nValue;
}

void OutputDlg::slotShowLastPic()
{
	if (!m_strLastOutputPath.isEmpty())
		showPic(m_strLastOutputPath);
}

void OutputDlg::showPic(const QString& strPath)
{
	GDALDataset  *poDataset;
	GDALAllRegister();
	poDataset = (GDALDataset *)GDALOpen(strPath.toLocal8Bit().constData(), GA_ReadOnly);

	GDALRasterBand* pBand1 = poDataset->GetRasterBand(1);

	GDALDataType datatype = pBand1->GetRasterDataType();
	if (datatype == GDT_Byte || datatype == GDT_UInt16)
	{
		m_PictureBox->setImage(QImage(strPath));
	}
	else if (datatype == GDT_Float32)
	{
		int nWid = pBand1->GetXSize();
		int nHei = pBand1->GetYSize();
		float* pFloatBuffer = new float[nWid * nHei];
		unsigned char* pCharBuffer = new unsigned char[nWid * nHei];

		pBand1->RasterIO(GF_Read, 0, 0, nWid, nHei, pFloatBuffer, nWid, nHei, GDT_Float32, 0, 0);
		double dMin = DataParaManager::Instance()->GetRadioMin();
		double dMax = DataParaManager::Instance()->GetRadioMax();

		for (int j = 0; j < nHei; j++)
		{
			for (int i = 0; i < nWid; i++)
			{
				float fValue = pFloatBuffer[j * nWid + i];
				unsigned char charValue = (fValue - dMin) / (dMax - dMin) * 255.0;
				pCharBuffer[j * nWid + i] = charValue;
			}
		}

		QImage img(pCharBuffer, nWid, nHei, nWid, QImage::Format_Grayscale8);
		m_PictureBox->setImage(img);

		delete[] pFloatBuffer;
		delete[] pCharBuffer;
	}

	GDALClose(poDataset);

	m_PictureBox->show();
	m_PictureBox->update();
}