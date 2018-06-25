
#include "Temp2radiance.h"

#include <QtCore/QtMath>
#ifndef PLANK_PARAMETERS
#define PLANK_PARAMETERS FFFF
#define h  6.626E-34    //普朗克常数 J.s
#define C  2.997825E8        //光速 m/s
#define pi 3.141592  
#endif
#ifndef BOLTZMAN_Parameter
#define  BOLTZMAN_Parameter FFFF
#define K 1.3806E-23   //波兹曼常数 单位 J/K
#endif // 


/*
波数域普朗克函数说明
输入：
（1） 温度：temp      单位为     K        double型
（2） 波数：v         单位为   1/cm       double型

输出：
(3)  谱亮度 BvT 单位 w/m2/sr/cm         double型
*/
double plankfunction(double temp, double v)
{
	double vlt = v*100;
	double parameter1 = 2 * h*vlt*vlt*vlt*C*C;
	double parameter2 = h*vlt *C / K / temp;
	double parameter3 = qExp(parameter2) - 1;
	double BvT = 100*parameter1 / parameter3;
	return BvT;
}



/*函数说明
输入：
（1）温度：temperature 单位为K double型
（2）模拟起始波段：wavelengthstart         单位为μm       double型
（3）模拟终端波段：wavelengthend           单位为μm       double型
（4）模拟波数谱分辨率：spetrumresolution   单位为cm^-1    double型
 (5)发射率：       emissitivity           无单位         double型

 输出：
 （1）辐射亮度      radiance          单位为 w/sr/m2  double型
*/
double Temp2radiance(double temperature, double wavelengthstart, 
	double wavelengthend, double spetrumresolution, 
	double emissitivity)
{
	double v_start = 10000/ wavelengthstart;   //  单位为1/cm
	double v_end = 10000 / wavelengthend;       // 单位为1/cm
	double v = v_end;
	double BvT = 0;
	double radiance = 0;
	while (v <=v_start)
	{
		BvT = plankfunction(temperature, v);
		radiance = radiance + BvT;
		v = v + spetrumresolution;
	}

	radiance = radiance*spetrumresolution*emissitivity;
	return radiance;

}



