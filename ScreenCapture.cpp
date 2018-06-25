#include "ScreenCapture.h"

#include <osgDB/WriteFile>
#include "osgEarth/DataParaManager.h"
#include "osgEarth/ColorTransform.h"
#include "AnimationController.h"

#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtWidgets/QMessageBox>

#include <gdal_priv.h>
#include <gdalwarper.h>
#include <ogr_spatialref.h>

#include <QtWidgets/QProgressDialog>
#include "Document.h"

//量化文件“量化等级”设置下拉菜单：8、10、12、14、16位。 0对应float型
int g_nOutputLevel = /*8*/0;

//0是左对齐，1是右对齐
int g_nDataAliment = 1;

extern osgViewer::Viewer* g_viewerMain;
extern QProgressDialog* g_ProgressDialog;
extern int g_OutPutFrameCount;
extern QMutex g_ErrorLogmutex;

ScreenCapture::ScreenCapture()
{

}

ScreenCapture::~ScreenCapture()
{

}

CScreenCapture::CScreenCapture(CaptureOperation* defaultOperation /*= 0*/, int numFrames/* = 1*/):
ScreenCaptureHandler( defaultOperation, numFrames )
{
	
}

bool CScreenCapture::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	osgViewer::ViewerBase* viewer = dynamic_cast<osgViewer::View*>(&aa)->getViewerBase();
	if (!viewer) return false;

	switch(ea.getEventType())
	{
		case (osgGA::GUIEventAdapter::FRAME):
		{
			// Booleans aren't the best way of doing this, but I want to do
			// the actual adding here because I don't want to require
			// startCapture() take a viewer as argument, which could not be
			// the right one.
			if (_startCapture)
			{
				// Start capturing with the currently set number of frames.
				// If set to -1 it will capture continuously, if set to >0
				// it will capture that number of frames.
				_startCapture = false;
				addCallbackToViewer(*viewer);
			}
			else if (_stopCapture)
			{
				_stopCapture = false;
				removeCallbackFromViewer(*viewer);
			}

			if (g_ProgressDialog->wasCanceled())
			{
				stopCapture();
				g_ProgressDialog->reset();
				AnimationController::EndPathFrame();
				AnimationController::Instance()->StopAnimation();
			}

			break;
		}

		case (osgGA::GUIEventAdapter::USER) :
		{
			const CaptureEvent* pEvent = dynamic_cast<const CaptureEvent*>(ea.getUserData());
			if (pEvent)
			{
				if (getFramesToCapture() == 0)
				{
					setFramesToCapture(1);
				}
				addCallbackToViewer(*viewer);
				return true;
			}
		}
		
// 		case (osgGA::GUIEventAdapter::KEYUP) ://自定义的事件，需要进入OSG的事件队列
// 		{
// 			if (ea.getKey() == 'c')
// 			{
// 				if (getFramesToCapture() == 0)
// 				{
// 					setFramesToCapture(1);
// 				}
// 				addCallbackToViewer(*viewer);
// 				return true;
// 			}

			//const OwnDefineEventAdpater* adpater= dynamic_cast< const MyEventAdpater *>(ea.getUserData());
			//switch(adpater->m_eventType)
			//{
			//	case SAVE_IMAGE:// 保存图片的事件
			//		{
			//			if (getFramesToCapture() == 0)
			//			{
			//				setFramesToCapture(1);
			//			}
			//			addCallbackToViewer(*viewer);
			//			return true;
			//		}
			//	default:
			//		break;
			//}
			//if (adpater->m_eventType == SaveImage )
			//{
			//	// Check that we will capture at least one frame.
			//	// Just check for ==0, because >0 is means we're already
			//	// capturing and <0 means it will capture all frames.
			//	if (getFramesToCapture() == 0)
			//	{
			//		setFramesToCapture(1);
			//	}
			//	addCallbackToViewer(*viewer);
			//	return true;
			//}
//		}
		default:
			break;
	}
	return false;
}

void CScreenCapture::WriteToImageFile::operator()( const osg::Image& image, const unsigned int context_id )//仿函数实现图片保存
{
	if ( !_filename.empty() )
	{
		QString strName = QString::fromLocal8Bit(_filename.c_str());
		QFileInfo fileInfo(strName);

// 		QString strFilePath = fileInfo.absolutePath() + fileInfo.completeBaseName() + "_" + QString::number(AnimationController::GetCaptureFrameIndex())
// 			+ "." + fileInfo.suffix();

		QString strFilePath = QString::fromLocal8Bit(_filename.c_str());
		if (fileInfo.suffix() != "tif")
		{
			strFilePath = strName + "/" + QString::number(AnimationController::GetCaptureFrameIndex() + 1) + ".tif";
		}


		if (!AnimationController::IsPathFrameRunning())
			return;

		//图像名称从1开始
		g_ProgressDialog->setLabelText(QString::fromLocal8Bit("输出第") + QString::number(AnimationController::GetCaptureFrameIndex() + 1) + QString::fromLocal8Bit("帧"));
		g_ProgressDialog->setValue(AnimationController::GetCaptureFrameIndex() + 1);

		QString strErrorLogPath = Document::Instance()->GetSavePath() + "/ErrorLog.txt";

		g_ErrorLogmutex.lock();
		QFile file(strErrorLogPath);
		file.open(QIODevice::WriteOnly);
		QByteArray byteArray = QString::number(AnimationController::GetCaptureFrameIndex()).toUtf8();
		file.write(byteArray.data());        // write to stderr
		file.close();
		g_ErrorLogmutex.unlock();

		bool bTag = image.isDataContiguous();
		osgDB::writeImageFile( image, _filename );

		const unsigned char* pData = image.data();

		DataParaManager* pDataParaManager = DataParaManager::Instance();
		double dMinValue = pDataParaManager->GetRadioMin();
		double dMaxValue = pDataParaManager->GetRadioMax();

		int nWid = image.s();
		int nHei = image.t();

		std::vector<osgViewer::View*> vecViews;
		g_viewerMain->getViews(vecViews);
		osgViewer::View* pView = vecViews[0];

		osg::Camera* pCamera = pView->getCamera();
		osg::Viewport* pViewPort = pCamera->getViewport();

		int nNewWid = pViewPort->width();
		int nNewHei = pViewPort->height();

		GLenum enumFormat = image.getPixelFormat();
		float* pFloatBuffer = new float[nNewWid * nNewHei];

		if (enumFormat == GL_RGB && image.isDataContiguous())
		{
// 			for (int j = 0; j < nHei; j ++)
// 			{
// 				for (int i = 0; i < nWid; i++)
// 				{
// 					unsigned char r = pData[(j * nWid + i) * 3];
// 					unsigned char g = pData[(j * nWid + i) * 3 + 1];
// 					unsigned char b = pData[(j * nWid + i) * 3 + 2];
// 
// 					float fValue = 0.0;
// 					ColorTransform::RGB2Value(r, g, b, dMinValue, dMaxValue, fValue);
// 
// 					pFloatBuffer[(nHei - 1 - j) * nWid + i] = fValue;
// 				}
// 			}

			for (int j = 0; j < nNewHei; j++)
			{
				for (int i = 0; i < nNewWid; i++)
				{
					unsigned char r = pData[(j * nWid + i) * 3];
					unsigned char g = pData[(j * nWid + i) * 3 + 1];
					unsigned char b = pData[(j * nWid + i) * 3 + 2];

					float fValue = 0.0;
					ColorTransform::RGB2Value(r, g, b, dMinValue, dMaxValue, fValue);

					pFloatBuffer[(nNewHei - 1 - j) * nNewWid + i] = fValue;
				}
			}
		}
		else
		{
			return;
		}

		nWid = nNewWid;
		nHei = nNewHei;

		const char *pszFormat = "GTiff";
		GDALDriver *poDriver;
		char **papszMetadata;
		poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
		if (poDriver == NULL)
			exit(1);
		papszMetadata = poDriver->GetMetadata();

		GDALDataset *poDstDS;
		char **papszOptions = NULL;

		if (g_nOutputLevel == 0)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_Float32, papszOptions);

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pFloatBuffer, nWid, nHei, GDT_Float32, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
		}
		else if (g_nOutputLevel == 8)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_Byte, papszOptions);
			unsigned char* pCharBuffer = new unsigned char[nWid * nHei];

			for (int j = 0; j < nHei; j++)
			{
				for (int i = 0; i < nWid; i++)
				{
					float fValue = pFloatBuffer[j * nWid + i];
					unsigned char value = (fValue - dMinValue) / (dMaxValue - dMinValue) * 256.0;
					pCharBuffer[j * nWid + i] = value;
				}
			}

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pCharBuffer, nWid, nHei, GDT_Byte, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
			delete[] pCharBuffer;
		}
		else if (g_nOutputLevel == 10)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_UInt16, papszOptions);
			unsigned short* pShortBuffer = new unsigned short[nWid * nHei];

			double dMax = 0xffff >> 6;

			for (int j = 0; j < nHei; j++)
			{
				for (int i = 0; i < nWid; i++)
				{
					float fValue = pFloatBuffer[j * nWid + i];
					unsigned short value = (fValue - dMinValue) / (dMaxValue - dMinValue) * dMax;
					if (g_nDataAliment == 0)
					{
						value = value << 6;
					}
					pShortBuffer[j * nWid + i] = value;
				}
			}

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pShortBuffer, nWid, nHei, GDT_UInt16, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
			delete[] pShortBuffer;
			pShortBuffer = NULL;
		}
		else if (g_nOutputLevel == 12)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_UInt16, papszOptions);
			unsigned short* pShortBuffer = new unsigned short[nWid * nHei];

			double dMax = 0xffff >> 4;

			for (int j = 0; j < nHei; j++)
			{
				for (int i = 0; i < nWid; i++)
				{
					float fValue = pFloatBuffer[j * nWid + i];
					unsigned short value = (fValue - dMinValue) / (dMaxValue - dMinValue) * dMax;
					if (g_nDataAliment == 0)
					{
						value = value << 4;
					}
					pShortBuffer[j * nWid + i] = value;
				}
			}

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pShortBuffer, nWid, nHei, GDT_UInt16, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
			delete[] pShortBuffer;
			pShortBuffer = NULL;
		}
		else if (g_nOutputLevel == 14)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_UInt16, papszOptions);
			unsigned short* pShortBuffer = new unsigned short[nWid * nHei];

			double dMax = 0xffff >> 2;

			for (int j = 0; j < nHei; j++)
			{
				for (int i = 0; i < nWid; i++)
				{
					float fValue = pFloatBuffer[j * nWid + i];
					unsigned short value = (fValue - dMinValue) / (dMaxValue - dMinValue) * dMax;
					if (g_nDataAliment == 0)
					{
						value = value << 2;
					}
					pShortBuffer[j * nWid + i] = value;
				}
			}

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pShortBuffer, nWid, nHei, GDT_UInt16, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
			delete[] pShortBuffer;
			pShortBuffer = NULL;
		}
		else if (g_nOutputLevel == 16)
		{
			poDstDS = poDriver->Create(strFilePath.toLocal8Bit().constData(), nWid, nHei, 1, GDT_UInt16, papszOptions);
			unsigned short* pShortBuffer = new unsigned short[nWid * nHei];

			double dMax = 0xffff;

			for (int j = 0; j < nHei; j++)
			{
				for (int i = 0; i < nWid; i++)
				{
					float fValue = pFloatBuffer[j * nWid + i];
					unsigned short value = (fValue - dMinValue) / (dMaxValue - dMinValue) * dMax;
					pShortBuffer[j * nWid + i] = value;
				}
			}

			GDALRasterBand *poBand;
			poBand = poDstDS->GetRasterBand(1);
			poBand->RasterIO(GF_Write, 0, 0, nWid, nHei, pShortBuffer, nWid, nHei, GDT_UInt16, 0, 0);
			/* Once we're done, close properly the dataset */
			GDALClose((GDALDatasetH)poDstDS);
			delete[] pShortBuffer;
			pShortBuffer = NULL;
		}

		delete[] pFloatBuffer;
		pFloatBuffer = NULL;

		if (AnimationController::IsPathFrameRunning())
		{
			if (AnimationController::GetCaptureFrameIndex() == g_OutPutFrameCount - 1)
			{
				AnimationController::EndPathFrame();

				g_ProgressDialog->reset();

				QMessageBox box;
				box.setText(QString::fromLocal8Bit("图片导出完成"));
				box.exec();

				AnimationController::Instance()->StopAnimation();
			}
			else
			{
				AnimationController::CaptureFrameIndexIncrement();
			}
		}
	}
}

CScreenCapture::WriteToImageFile::WriteToImageFile( const std::string& filename, const std::string& extension, SavePolicy savePolicy /*= SEQUENTIAL_NUMBER*/ )
: _filename( filename ),
_extension( extension ),
_savePolicy( savePolicy )
{

}