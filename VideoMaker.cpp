#include "VideoMaker.h"

#include "opencv/highgui.h" 
#include "opencv/cv.h"
#include <QtWidgets/QMessageBox>
#include "gdal_priv.h"
#include <QFile>
#include <QtWidgets/QProgressDialog>

extern int g_OutPutFrameCount;
extern QProgressDialog* g_ProgressDialog;
extern QWidget* g_pMainWindow;

VideoMaker::VideoMaker()
{

}

VideoMaker::~VideoMaker()
{

}

void VideoMaker::MakeVideo(const QString& strDir)
{
	QString videoPath = strDir + "/" + "output.avi";
	GDALAllRegister();

	const char *pszFormat = "GTiff";
	GDALDriver *poDriver;
	poDriver = GetGDALDriverManager()->GetDriverByName("JPEG"/*pszFormat*/);
	//GDALDriver *poDriverBmp = GetGDALDriverManager()->GetDriverByName("BMP");

	//图像名称从1开始
	CvVideoWriter* video = NULL;
	int nCurrentImageIndex = 1;

	if (g_ProgressDialog == nullptr)
	{
		g_ProgressDialog = new QProgressDialog(g_pMainWindow);
		g_ProgressDialog->setAttribute(Qt::WA_DeleteOnClose);
		g_ProgressDialog->setWindowFlags(g_ProgressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
		g_ProgressDialog->setWindowFlags(g_ProgressDialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
		g_ProgressDialog->setModal(true);
		g_ProgressDialog->setCancelButtonText("Cancel");
	}

	g_ProgressDialog->setWindowTitle(QString::fromLocal8Bit("生成视频"));
	g_ProgressDialog->setRange(0, g_OutPutFrameCount);
	int nCount = -1;
	g_ProgressDialog->setLabelText("");

	while (1)
	{
		nCount++;
		g_ProgressDialog->setValue(nCount);

		if (g_ProgressDialog->wasCanceled())
		{
			g_ProgressDialog->reset();
			break;
		}

		QString tifFullPath = strDir + "/" + QString::number(nCurrentImageIndex) + ".tif";
		QString bmpFullPath = strDir + "/" + QString::number(nCurrentImageIndex) + ".jpg";

		nCurrentImageIndex++;

		GDALDataset *poSrcDS =
			(GDALDataset *)GDALOpen(tifFullPath.toLocal8Bit().data(), GA_ReadOnly);

		if (poSrcDS == NULL)
		{
			break;
		}

		GDALDataset *poDstDS;
		poDstDS = poDriver->CreateCopy(bmpFullPath.toLocal8Bit().data(), poSrcDS, FALSE,
									   NULL, NULL, NULL);
		/* Once we're done, close properly the dataset */
		if(poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);
		GDALClose((GDALDatasetH)poSrcDS);

		IplImage *iplImgNew = cvLoadImage(bmpFullPath.toLocal8Bit().data(), 1);
		if(video == NULL)
		{
			video = cvCreateVideoWriter(videoPath.toLocal8Bit().data(),
										-1/*CV_FOURCC('P', 'I', 'M', '1')*/, 20,
										cvSize(iplImgNew->width, iplImgNew->height), 1);

			if(video == NULL)
			{
				QMessageBox msgBox;
				msgBox.setText(QString::fromLocal8Bit("创建视频失败，请选择其他编码方式"));
				msgBox.exec();
				return;
			}
		}

		//for(int i = 0; i < 10; i++)
		{
			cvWriteFrame(video, iplImgNew);
		}
		//cvWriteFrame(video, iplImgNew);
		cvReleaseImage(&iplImgNew);

		QFile file(bmpFullPath);
		file.remove();
	}

	//cvResize(iplImg, iplImgNew, CV_INTER_LINEAR);

	//data为图像再内存中的地址
	//CvMat mat = cvMat(width, height, CV_8UC1, data);//Read input binary image  
	//第二个参数为flag，在opencv文档中查询
	//IplImage *pIplImage = cvDecodeImage(&mat, 1);

	g_ProgressDialog->reset();

	/*
	* 释放指针
	*/
	if (video) {
		cvReleaseVideoWriter(&video);
	}

}