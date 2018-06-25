#include "tempos.h"
#include "Temp2radiance.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

using namespace std;


/*函数说明
 * 输入：
 * （1） 存放文件路径：InDir 类型 CString    界面可输入
 * （2） 输入文件名：Filename 类型 CString   界面可输入
 *  (3) 输出文件路径：OutDir                界面可输入
 * （4） 起始波长：wavelengthstart 单位：μm  界面可输入与显示
 * （5） 终止波长：wavelengthend   单位：μm  界面可输入与显示
 * （6） 谱分辨率：spetrumresolution 单位：1/cm 界面可输入与显示
 * （7） 发射率： emissitivity            界面可输入与显示
 *
 *
*/



void tempos(const QString& InDir, const QString& Filename, const QString& OutDir, double wavelengthstart,
			double wavelengthend, double spetrumresolution, double emissitivity)
{      int Num;
       double temp;

	   QFile fileIn(InDir + Filename);
	   if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
		   return;

	   QTextStream infile(&fileIn);

	   QFile fileOut(OutDir + Filename.left(Filename.size() - 4) + "_rad.tmp");
	   if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;

	   QTextStream ofile(&fileOut);

	//ifstream infile(InDir + Filename,ios::in);
	
	//ofstream ofile(OutDir+ Filename.Left(Filename.GetLength()-4)+ "_rad.tmp");
// 	if(!infile)
// 	{
// 		cerr<<"Open error!"<<endl;
// 		exit(1);
// 	}
// 	if (ofile.is_open()) ofile.clear();

	infile >> Num;
	ofile << Num << "\n";
	for (int i = 0;!infile.atEnd() ; i++)
	{
		infile >> Num;
		ofile << Num << " ";
		infile >> temp;
		ofile << Temp2radiance(temp, wavelengthstart,wavelengthend, spetrumresolution,emissitivity) << "\n";
	}
// 	infile.close();
// 	ofile.close();
}
