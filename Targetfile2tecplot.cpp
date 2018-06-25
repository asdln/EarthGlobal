#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include   <fstream>
#include   <iostream> 
#include   <stdexcept> 
#include   <fstream>
#include <iomanip>
#include "Targetfile2tecplot.h"
using namespace std;


/*函数描述：tempAverage
           输入：tmpInDir CString格式  .tmp文件路径
		         tmpFileName CString格式 .tmp文件名
				   triInDir  CString格式  .tri文件路径
				    triFileName  CString格式  .tri文件名
		  输出：outDir CString格式   .plt文件输出路径
		        outFileName  CString格式 .plt文件名
		      
		        

*/
void tempAverage(const QString& tmpFileName,
	const QString& triFileName,
	const QString& outFileName)
{
	int temp,n,e,num;
	double **NT, **NPP;

	QFile inTmpfile(tmpFileName);
	if (!inTmpfile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QFile inTrifile(triFileName);
	if (!inTrifile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QFile file(outFileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream ofile(&file);

	QByteArray lineTri = inTrifile.readAll();
	QTextStream textLineTri(lineTri);

	QByteArray lineTmp = inTmpfile.readAll();
	QTextStream textLineTmp(lineTmp);

	textLineTri >> e;				        //面元数目
	textLineTri >> n;				        //点数目
	NT = new double *[e];
	for (size_t i = 0; i < e; i++)
	{
		NT[i] = new double[4];//面->三点、温度
	}

	NPP = new double *[n];
	for (size_t i = 0; i < n; i++)
	{
		NPP[i] = new double[5];
	}

	for (int i = 0; i < n; i++)
	{
		NPP[i][0] = 0;
		NPP[i][1] = 0;
		NPP[i][2] = 0;
		NPP[i][3] = 0;
		NPP[i][4] = 0;
	}

	for (int i = 0; i < e; i++)
	{
		NT[i][0] = 0;
		NT[i][1] = 0;
		NT[i][2] = 0;
		NT[i][3] = 0;
	}

	textLineTmp >> temp;					//保存面元对应温度
	for (int i = 0;i < e; i++)
	{
		textLineTmp >> temp;
		textLineTmp >> NT[temp - 1][3];
	}

	textLineTri >> num;

	for (int i = 0; i < 3 * num; i++)
	{
		textLineTri >> temp;
	}
	for (int i = 0; i < n; i++)		//保存各点XYZ
	{
		textLineTri >> temp;
		textLineTri >> NPP[temp - 1][0];
		textLineTri >> NPP[temp - 1][1];
		textLineTri >> NPP[temp - 1][2];
	}
	for (int i = 0; i < e; i++)		//累加每个点的温度
	{
		textLineTri >> temp;
		textLineTri >> NT[temp - 1][0];
		if (NT[temp-1][0]<=n)
		{
			NPP[(int)NT[temp-1][0]-1][3]+=NT[temp-1][3];
			NPP[(int)NT[temp-1][0]-1][4]++;
		}
		textLineTri >> NT[temp - 1][1];
		if (NT[temp-1][1]<=n)
		{
			NPP[(int)NT[temp-1][1]-1][3]+=NT[temp-1][3];
			NPP[(int)NT[temp-1][1]-1][4]++;
		}		
		textLineTri >> NT[temp - 1][2];
		if (NT[temp-1][2]<=n)
		{
			NPP[(int)NT[temp-1][2]-1][3]+=NT[temp-1][3];
			NPP[(int)NT[temp-1][2]-1][4]++;
		}
	}
// 	inTmpfile.close();
// 	inTrifile.close();

	for (int i = 0; i < n; i++)
	{
		if (NPP[i][3] == 0)				//填充280
			NPP[i][3] = 288.0;
		if (NPP[i][4]> 0)
			NPP[i][3]/=NPP[i][4];		//温度平均
	}

	QString strTemp = QString::fromLocal8Bit("目标");

	ofile << "Title=\"" + strTemp + "\"\n";
	ofile << "Variable=\"x\",\"y\",\"z\",\"T\"\n";
	ofile << "Zone N=" <<n << ",";
	ofile << "E=" <<e << ","<< "F=fepoint,ET=triangle\n";			//暂时直接写出n，e
	for (int i = 0; i < n; i++)
	{
		ofile << fixed << NPP[i][0] << " ";			//输出格式fixed
		ofile << NPP[i][1] << " ";
		ofile << NPP[i][2] << " ";
		ofile << NPP[i][3] << "\n";
	}
	for (int i = 0; i < e; i++)
	{
		ofile << /*setprecision(0) << */(int)(NT[i][0]) << " ";	//点数编号为整 舍去小数点后的0
		ofile << NT[i][1] << " ";
		ofile << NT[i][2] << "\n";
	}
	//ofile.close();

	for (size_t i = 0; i < e; i++)
	{
		delete [] NT[i];//面->三点、温度
	}
	delete[] NT;

	for (size_t i = 0; i < n; i++)
	{
	delete []	NPP[i];
	}
	delete[] NPP;

}
