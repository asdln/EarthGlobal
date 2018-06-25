#include "Document.h"

#include "NewProjectDlg.h"
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>

#include "AnimationController.h"
#include "osgEarthQt/DataManager"
#include "osgEarth/DataParaManager.h"
#include "RangeFeatureGenerator.h"

#include <QMessageBox>
#include <QMdiSubWindow>
extern osgViewer::Viewer* g_viewerMain;
#include "AirDataReader.h"

extern osgEarth::QtGui::DataManager* g_DataManager;
extern QMdiSubWindow* g_pMdiSubWindow;
extern RangeFeatureGenerator* g_pRangerFeatureGenerator;
#include <QtMath>

extern void LoadModisRadioLayer(const QString& fileName);

bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
	toDir.replace("\\", "/");
	if (sourceDir == toDir){
		return true;
	}
	if (!QFile::exists(sourceDir)){
		return false;
	}
	QDir *createfile = new QDir;
	bool exist = createfile->exists(toDir);
	if (exist){
		if (coverFileIfExist){
			createfile->remove(toDir);
		}
	}//end if  

	if (!QFile::copy(sourceDir, toDir))
	{
		return false;
	}
	return true;
}

Document::Document()
{
}

Document::~Document()
{
}

const QString& Document::GetSavePath()
{
	return m_strSavePath;
}

void Document::SetSavePath(const QString& strPath)
{
	m_strSavePath = strPath;
}

void Document::CreateNewProject()
{
	NewProjectDlg dlg;
	if(dlg.exec())
	{
		// 创建XML文档
		QDomDocument domDocument;

		// 创建XML文档说明
		QDomProcessingInstruction instruction;
		instruction = domDocument.createProcessingInstruction("xml", "version =\"1.0\" encoding=\"UTF-8\"");
		domDocument.appendChild(instruction);

		QDomElement projectInfo = domDocument.createElement("ProjectInfo");
		domDocument.appendChild(projectInfo);
		projectInfo.setAttribute("CameraTrack", dlg.ui.lineEdit_CameraTrack->text());
		projectInfo.setAttribute("TargetTrack", dlg.ui.lineEdit_TargetTrack->text());
		projectInfo.setAttribute("TargetDataTmp", dlg.ui.lineEdit_tmp->text());
		projectInfo.setAttribute("TargetDataTRI", dlg.ui.lineEdit_TRI->text());
		projectInfo.setAttribute("TargetDataPlt", dlg.ui.lineEdit_Plt->text());
		projectInfo.setAttribute("TargetDataJet", dlg.ui.lineEdit_LoadJet->text());

		bool bCustomJet = dlg.ui.groupBox_CustomJet->isChecked();
		projectInfo.setAttribute("CustomJet", bCustomJet);

		if (bCustomJet)
		{
			QTableWidget* pTableWidget = dlg.ui.tableWidget_JetPara;
			int nJetCount = pTableWidget->rowCount();

			QString listJetPara;
			for (int i = 0; i < nJetCount; i++)
			{
				QTableWidgetItem* pItem = pTableWidget->item(i, 0);
				double dx = pItem->text().toDouble();
				listJetPara += QString::number(dx);
				listJetPara += '#';

				pItem = pTableWidget->item(i, 1);
				double dy = pItem->text().toDouble();
				listJetPara += QString::number(dy);
				listJetPara += '#';

				pItem = pTableWidget->item(i, 2);
				double dz = pItem->text().toDouble();
				listJetPara += QString::number(dz);
				listJetPara += '#';

				pItem = pTableWidget->item(i, 3);
				double dPitch = pItem->text().toDouble();
				listJetPara += QString::number(dPitch);
				listJetPara += '#';

				pItem = pTableWidget->item(i, 4);
				double dYaw = pItem->text().toDouble();
				listJetPara += QString::number(dYaw);
				listJetPara += '#';

				pItem = pTableWidget->item(i, 5);
				double dRoll = pItem->text().toDouble();
				listJetPara += QString::number(dRoll);
			}

			projectInfo.setAttribute("CustomJetPara", listJetPara);
		}

		projectInfo.setAttribute("Start", dlg.ui.lineEdit_start->text());
		projectInfo.setAttribute("End", dlg.ui.lineEdit_End->text());
		projectInfo.setAttribute("Fen", dlg.ui.lineEdit_fen->text());
		projectInfo.setAttribute("Fa", dlg.ui.lineEdit_fa->text());
		projectInfo.setAttribute("TransToRadio", dlg.ui.groupBox_ToRadio->isChecked());

		projectInfo.setAttribute("AirDataDir", dlg.ui.lineEdit_AirDir->text());
		projectInfo.setAttribute("EarthRadio", dlg.ui.lineEdit_EarthRadio->text());

		projectInfo.setAttribute("RadioMin", dlg.ui.lineEdit_RadioMin->text());
		projectInfo.setAttribute("RadioMax", dlg.ui.lineEdit_RadioMax->text());
//		projectInfo.setAttribute("TemperatureMin", dlg.ui.lineEdit_TemperatureMin->text());
//		projectInfo.setAttribute("TemperatureMax", dlg.ui.lineEdit_TemperatureMax->text());
		projectInfo.setAttribute("HorVPCur", dlg.ui.lineEdit_HorVPCur->text());
		projectInfo.setAttribute("VerVPCur", dlg.ui.lineEdit_VerVPCur->text());
		projectInfo.setAttribute("HorRes", dlg.ui.lineEdit_HorRes->text());
		projectInfo.setAttribute("VerRes", dlg.ui.lineEdit_VerRes->text());



		// 写入XML文件
		QString documentString = domDocument.toString();

		QFile file(dlg.ui.lineEdit_ProjectPath->text());
		file.open(QIODevice::WriteOnly | QIODevice::Truncate);
		int nWrite = file.write(documentString.toUtf8().data(), documentString.toUtf8().size());
		file.close();

		OpenProjectXML(dlg.ui.lineEdit_ProjectPath->text());

		QMessageBox box;
		box.setText(QString::fromLocal8Bit("工程创建完毕"));
		box.exec();
	}
}

void Document::OpenProjectXML()
{
	extern QString g_strLastDir;
	QString fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("工程文件"),
													g_strLastDir,
													"xml (*.xml)");

	if(fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	OpenProjectXML(fileName);

	//加载第一个大气
	if (1)
	{
		CameraPath* pCameraPath = AnimationController::Instance()->GetCameraPath();
		const std::map<double, CameraPathRecord>& mapRecords = pCameraPath->getMapRecords();

		QString strPath;
		for (std::map<double, CameraPathRecord>::const_iterator itr = mapRecords.begin(); itr != mapRecords.end(); itr ++)
		{
			strPath = itr->second.strAirDataPath;
			if (!strPath.isEmpty())
			{
				break;
			}
		}

		Document* pDocument = Document::Instance();
		const QString& strDocumentPath = pDocument->GetAirDataDir();

		QFileInfo fileInfo(strDocumentPath);
		QString strAirPath = fileInfo.absolutePath();

		strAirPath = strAirPath + strPath;

		QFileInfo fileInfo2(strAirPath);
		if (fileInfo2.exists())
		{
			//AnimationController::Instance()->LoadAirData(strAirPath);

			DataParaManager* pAirDataBuffer = DataParaManager::Instance();
			pAirDataBuffer->ResetValue();

			AirDataReader reader;
			reader.AddData(strPath);
		}

		g_pRangerFeatureGenerator->RefreshBackgroundTexture();
	}

	QMessageBox box;
	box.setText(QString::fromLocal8Bit("工程加载完毕"));
	box.exec();
}

void Document::SaveAsProject()
{
	extern QString g_strLastDir;
	QString fileName = QFileDialog::getSaveFileName(NULL, QString::fromLocal8Bit("工程另存为"),
		g_strLastDir,
		"xml (*.xml)");

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	copyFileToPath(m_strXMLPath, fileName, true);
}

void Document::OpenProjectXML(const QString& strPath)
{
	// 读取文件
	QFile file(strPath);
	if (!file.open(QIODevice::ReadOnly))
		return;

	m_strXMLPath = strPath;

	QFileInfo fileInfo(strPath);
	SetSavePath(fileInfo.absolutePath());

	QByteArray byteArray = file.readAll();
	file.close();

	// 用Document打开
	QDomDocument domDocument;
	bool success = domDocument.setContent(byteArray);
	if (!success)
		return;

	QDomElement projectInfo = domDocument.documentElement();

	QString strCameTrack = projectInfo.attribute("CameraTrack");
	QString strTargetTrack = projectInfo.attribute("TargetTrack");

	TargetDataPara para;
	para.dx = 0.0;
	para.dy = 0.0;
	para.dz = 1000.0;

	para.dAngleX = 0.0;
	para.dAngleY = 0.0;
	para.dAngleZ = 0.0;

	para.strValuePath = projectInfo.attribute("TargetDataTmp");
	para.strIndexPath = projectInfo.attribute("TargetDataTRI");
	para.strJetPath = projectInfo.attribute("TargetDataJet");
	para.strPltPath = projectInfo.attribute("TargetDataPlt");

	para.dstart = projectInfo.attribute("Start").toDouble();
	para.dend = projectInfo.attribute("End").toDouble();
	para.dfen = projectInfo.attribute("Fen").toDouble();
	para.dfa = projectInfo.attribute("Fa").toDouble();

	para.bTransToRadio = projectInfo.attribute("TransToRadio").toInt();

	para.bCustomJet = projectInfo.attribute("CustomJet").toInt();
	if (para.bCustomJet)
	{
		QString strJetPara = projectInfo.attribute("CustomJetPara");

		QStringList listPara = strJetPara.split('#');
		int nJetCount = listPara.size() / 6;

		for (int i = 0; i < nJetCount; i ++)
		{
			JetPosInfo jetPosInfo;
			jetPosInfo.dx = listPara[i * 6].toDouble();
			jetPosInfo.dy = listPara[i * 6 + 1].toDouble();
			jetPosInfo.dz = listPara[i * 6 + 2].toDouble();
			jetPosInfo.dPitch = listPara[i * 6 + 3].toDouble();
			jetPosInfo.dYaw = listPara[i * 6 + 4].toDouble();
			jetPosInfo.dRoll = listPara[i * 6 + 5].toDouble();

			para.listJetPosInfo.push_back(jetPosInfo);
		}
	}

	m_strAirDataDir = projectInfo.attribute("AirDataDir");
	QString strEarthRadio = projectInfo.attribute("EarthRadio");

	double dRadioMin = projectInfo.attribute("RadioMin").toDouble();
	double dRadioMax = projectInfo.attribute("RadioMax").toDouble();
	double dTemperatureMin = projectInfo.attribute("TemperatureMin").toDouble();
	double dTemperatureMax = projectInfo.attribute("TemperatureMax").toDouble();

	DataParaManager* pDataParaManager = DataParaManager::Instance();
	pDataParaManager->SetRadioMin(dRadioMin);
	pDataParaManager->SetRadioMax(dRadioMax);
	pDataParaManager->SetTemperatureMin(dTemperatureMin);
	pDataParaManager->SetTemperatureMax(dTemperatureMax);

	//设置视场和窗口大小
	{
		double dHorVPCur = projectInfo.attribute("HorVPCur").toDouble();
		double VerVPCur = projectInfo.attribute("VerVPCur").toDouble();
		int nHorRes = projectInfo.attribute("HorRes").toInt();
		int nVerRes = projectInfo.attribute("VerRes").toInt();

		osg::Camera* camera = g_viewerMain->getCamera();

		double dVerAngle = VerVPCur;
		double dHorAngle = dHorVPCur;

		double dParaVerAngle = dVerAngle / 2.0;

		double dOffset = 1.0;

		double dWidth = 1.0;
		double dHeight = 1.0;

		dVerAngle /= 2.0;
		dVerAngle = dVerAngle / 180.0 * 3.1415926;

		dHorAngle /= 2.0;
		dHorAngle = dHorAngle / 180.0 * 3.1415926;

		double dWidDivHei = qTan(dHorAngle) / qTan(dVerAngle);

		QWidget* pWidget = g_pMdiSubWindow->widget();

		double dWidSpace = g_pMdiSubWindow->width() - pWidget->width();
		double dHeiSpace = g_pMdiSubWindow->height() - pWidget->height();

		double dCurrentWidDivHei = pWidget->width() / (double)pWidget->height();

		double dNewWid = pWidget->width();
		double dNewHei = nVerRes;

		dNewWid = dNewHei * dWidDivHei;
		

		g_pMdiSubWindow->setGeometry(0, 0, dNewWid + dWidSpace, dNewHei + dHeiSpace);
		camera->setProjectionMatrixAsPerspective(dParaVerAngle, camera->getViewport()->width() / camera->getViewport()->height(), 1.0f, 10000.0f);
	}

	AnimationController* pAnimationController = AnimationController::Instance();

	pAnimationController->LoadTargetData(para);
	//	pAnimationController->LoadAirData(strAriData);

	pAnimationController->LoadCameraPath(strCameTrack);
	pAnimationController->LoadTargetPath(strTargetTrack);

	if (!strEarthRadio.isEmpty())
	{
		LoadModisRadioLayer(strEarthRadio);
	}
}