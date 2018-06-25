#include "targetdatadlg.h"
#include <QtWidgets/QFileDialog>
extern QString g_strLastDir;

TargetDataDlg::TargetDataDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_dStart = 10.78;
	m_dEnd = 11.28;
	m_dFen = 1.0;
	m_dFa = 0.6;

	ui.lineEditX->setText("0.0");
	ui.lineEditY->setText("0.0");
	ui.lineEditZ->setText("100.0");

	ui.lineEdit_start->setText(QString::number(m_dStart));
	ui.lineEdit_End->setText(QString::number(m_dEnd));

	ui.lineEdit_fen->setText(QString::number(m_dFen));
	ui.lineEdit_fa->setText(QString::number(m_dFa));

	QStringList strList;
	strList.push_back(QString::fromLocal8Bit("x"));
	strList.push_back(QString::fromLocal8Bit("y"));
	strList.push_back(QString::fromLocal8Bit("z"));

	strList.push_back(QString::fromLocal8Bit("俯仰角"));
	strList.push_back(QString::fromLocal8Bit("偏航角"));
	strList.push_back(QString::fromLocal8Bit("翻滚角"));

	m_nCols = 6;
	ui.tableWidget_JetPara->setColumnCount(m_nCols);
	ui.tableWidget_JetPara->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_JetPara->setSelectionMode(QAbstractItemView::SingleSelection);

	for (int i = 0; i < m_nCols; i++)
	{
		ui.tableWidget_JetPara->setColumnWidth(i, 80);
	}
	ui.tableWidget_JetPara->setHorizontalHeaderLabels(strList);

	m_strTmp = QString::fromLocal8Bit("C:\\OSG_OSGEarth\\数据格式\\目标\\339.tmp");
	m_strTRI = QString::fromLocal8Bit("C:\\OSG_OSGEarth\\数据格式\\目标\\目标6part.TRI");

	connect(ui.pushButton_AddJet, SIGNAL(clicked()), this, SLOT(slotAddJet()));
	connect(ui.pushButton_RemoveJet, SIGNAL(clicked()), this, SLOT(slotDeleteJet()));
}

TargetDataDlg::~TargetDataDlg()
{

}

void TargetDataDlg::slotAddJet()
{
	ui.tableWidget_JetPara->insertRow(0);

	for (int i = 0; i < m_nCols; i ++)
	{
		QTableWidgetItem* pItem = new QTableWidgetItem;
		pItem->setText("0.0");

		ui.tableWidget_JetPara->setItem(0, i, pItem);
	}
}

void TargetDataDlg::slotDeleteJet()
{
	QList<QTableWidgetItem *> listItems = ui.tableWidget_JetPara->selectedItems();
	if (listItems.isEmpty())
		return;

	int nRow = listItems[0]->row();
	ui.tableWidget_JetPara->removeRow(nRow);
}

void TargetDataDlg::slotButtonClicked_LoadPlt()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.plt)"));

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.label_Plt->setText(fileName);
}

void TargetDataDlg::slotButtonClicked_tmp()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.tmp)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	m_strTmp = fileName;
	ui.label_tmp->setText(m_strTmp);
}

void TargetDataDlg::slotButtonClicked_TRI()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.TRI)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	m_strTRI = fileName;
	ui.label_TRI->setText(m_strTRI);
}

void TargetDataDlg::slotButtonClicked_LoadJet()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		g_strLastDir,
		tr("Target (*.dat *.plt)"));

	if (fileName.isEmpty())
		return;

	g_strLastDir = QFileInfo(fileName).absolutePath();

	ui.label_LoadJet->setText(fileName);
}

double TargetDataDlg::GetX()
{
	return ui.lineEditX->text().toDouble();
}

double TargetDataDlg::GetY()
{
	return ui.lineEditY->text().toDouble();
}

double TargetDataDlg::GetZ()
{
	return ui.lineEditZ->text().toDouble();
}

bool TargetDataDlg::GetAuxPara(double& dStart, double& dEnd, double& dfen, double& dfa)
{
	dStart = ui.lineEdit_start->text().toDouble();
	dEnd = ui.lineEdit_End->text().toDouble();
	dfen = ui.lineEdit_fen->text().toDouble();
	dfa = ui.lineEdit_fa->text().toDouble();

	m_dStart = dStart;
	m_dEnd = dEnd;
	m_dFen = dfen;
	m_dFa = dfa;

	return ui.groupBox_CustomJet->isChecked();
}