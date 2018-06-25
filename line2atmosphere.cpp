//#include"stdafx.h"
#include"Ge0_xyz.h"
#include<math.h>

#ifndef PI
#define PI
#define pi 3.1415926535897932384626433832795
#endif

#ifndef GEOEARTH_PARAMETER
#define GEOEARTH_PARAMETER
//克拉索夫斯基椭球
#define CZ_Beijing54 6378245.000
//#define DZ_Beijing54 6356863.0188
#define DZ_Beijing54 6356863.018773034
#define e2_54 0.00669342162297



//1975国际椭球
#define CZ_XIAN80 6378140.000
#define DZ_XIAN80 6356755.2882
#define e2_1975  0.00669438499959




#define CZ_NewBeijing54 6378137.000
#define DZ_NewBeijing54 6356752.31420


#define CZ_CGCS2000 6378137.000
//#define DZ_CGCS2000 6356752.31420	
#define DZ_CGCS2000 6356752.314140358
#define e2_CGCS2000 0.00669438002290

//WGS_84系椭球
#define CZ_WGS84 6378137.000
#define DZ_WGS84 6356752.3142
#endif


bool fequal(double value1, double value2, double precision)
{
	if (abs(value1-value2)<=precision)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*函数说明 line2atmosphereLBH
       输入：viewpoint_L double型  大地坐标下视点的经度 单位为度
	         viewpoint_B  double型  大地坐标下视点的纬度 单位为度
			  viewponit_H double型  大地坐标下视点的高度 单位为米
	            target_L  double型  大地坐标下目标或者地表的经度 单位为度
                 target_B double型  大地坐标下目标或者地表的纬度 单位为度
			       target double型   大地坐标下目标或者地表的高度 单位为米
				    atmos_H double型   大地坐标下大气层顶的高度 单位为米 一般为99000
	   输出：atmos_L double*型  大地坐标下大气层顶的经度 单位为度
	         atmos_B double*型  大地坐标下大气层顶的纬度 单位为度

			 状态变量 1  为视线与大气层顶有交点
			         -1 为视线与大气层顶没有或者不只一个交点
*/

int line2atmosphereLBH(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double target_L, double target_B, double target_H, double atmos_H,
	double *atmos_L, double *atmos_B, int axis_type)
{ 
	double DZ, CZ;
	switch (axis_type)
	{

	case 1:
	{
		CZ= CZ_Beijing54;
		DZ= DZ_Beijing54;
		break;
	}

	case 2:
	{
		CZ = CZ_XIAN80;
		DZ = DZ_XIAN80;
		break;
	}

	case 3:
	{
		CZ = CZ_NewBeijing54;
		DZ = DZ_NewBeijing54;
		break;
	}



	case 4:
	{
		CZ = CZ_CGCS2000;
		DZ = DZ_CGCS2000;
		break;
	}



	case 5:
	{
		CZ = CZ_WGS84;
		DZ = DZ_WGS84;
		break;
	}

	default:
		break;
	}


	double target_x,target_y,target_z, viewpoint_x, viewpoint_y, viewpoint_z, atmos_x, atmos_y, atmos_z;
	geo2xyz(viewpoint_L, viewpoint_B, viewponit_H, &viewpoint_x, &viewpoint_y, &viewpoint_z, axis_type);
	geo2xyz(target_L, target_B, target_H, &target_x, &target_y, &target_z, axis_type);
	double Ta, Tb, Tc,t1,t2,t,H_compute;
	double m,n,p;
	m = viewpoint_x - target_x;
	n = viewpoint_y - target_y;
	p = viewpoint_z - target_z;
	Ta = (DZ + atmos_H)*(DZ + atmos_H)*(m*m+ n*n)+ (CZ + atmos_H)*(CZ + atmos_H)*p*p;
	Tb = 2 *(DZ + atmos_H)*(DZ + atmos_H) * (target_x*m+ target_y*n)+ 2*(CZ + atmos_H)*(CZ + atmos_H)*target_z*p;
	Tc = (DZ + atmos_H)*(DZ + atmos_H)*(target_x*target_x + target_y*target_y)
		+ (CZ + atmos_H)*(CZ + atmos_H)*target_z*target_z
		- (CZ + atmos_H)*(CZ + atmos_H)*(DZ + atmos_H)*(DZ + atmos_H);

	double deltaT = Tb*Tb - 4 * Ta*Tc;
	if ((deltaT>=0)&(Ta != 0))
	{
		t1 = (-Tb + sqrt(deltaT)) / 2 / Ta;
		t2 = (-Tb - sqrt(deltaT)) / 2 / Ta;

   if (t1*t1 < t2*t2)
   {
	   t = t1;
   }
   else
   {
	   t = t2;
   }

   atmos_x = target_x + (viewpoint_x - target_x)*t;
   atmos_y = target_y + (viewpoint_y - target_y)*t;
   atmos_z = target_z + (viewpoint_z - target_z)*t;
   xyz2geo(atmos_x, atmos_y, atmos_z, atmos_L, atmos_B, &H_compute, axis_type);
   return 1;
	}
	else
	{
		return - 1;
	}
	

}



/*函数说明 line2atmosphereXYZ
输入：
Nearpoint_x  double型  离视点近点直角坐标系下x轴坐标值 单位为米
Nearpoint_y  double型  离视点近点直角坐标系下x轴坐标值 单位为米
Nearpoint_z double型  离视点近点直角坐标系下x轴坐标值 单位为米
Farpoint_x  double型  离视点近点直角坐标系下x轴坐标值 单位为米
Farpoint_y double型  离视点近点直角坐标系下x轴坐标值 单位为米
Farpoint_z double型   离视点近点直角坐标系下x轴坐标值 单位为米
atmos_H  double型   大气椭球面的高度（99km为大气层顶，0km为地表）

输出：
atmos_L double*型  视线对应的大地坐标下大气层顶的经度 单位为度
atmos_B double*型       视线对应的大地坐标下大气层顶的纬度 单位为度
land_L double*型  大地坐标下大气层顶的经度 单位为度
land_B double*型  大地坐标下大气层顶的纬度 单位为度

状态变量 flag 0  为视线与大气没有交点
              1 为视线与大气层顶只有一个交点
			  2  视线与大气有两个交点与地表没有交点
			  3 视线与大气有两个交点与地表一个交点
			  4 视线与大气两个交点与地表两个交点
 **注意：Nearpoint要保证靠真实大气层近才能实现，否则根据视点位置实现算法
*/

int line2atmosphereXYZ(double Nearpoint_x, double Nearpoint_y, double Nearpoint_z,
	double Farpoint_x, double Farpoint_y, double Farpoint_z,double atmos_H,
	double *atmos_L, double *atmos_B, 
	double *Land_L,double *Land_B,
	int axis_type)
{
	double DZ, CZ;
	switch (axis_type)
	{

	case 1:
	{
		CZ = CZ_Beijing54;
		DZ = DZ_Beijing54;
		break;
	}

	case 2:
	{
		CZ = CZ_XIAN80;
		DZ = DZ_XIAN80;
		break;
	}

	case 3:
	{
		CZ = CZ_NewBeijing54;
		DZ = DZ_NewBeijing54;
		break;
	}



	case 4:
	{
		CZ = CZ_CGCS2000;
		DZ = DZ_CGCS2000;
		break;
	}



	case 5:
	{
		CZ = CZ_WGS84;
		DZ = DZ_WGS84;
		break;
	}

	default:
		break;
	}

	*atmos_L = 0;
	*atmos_B = 0;
	*Land_L = 0;
	*Land_B = 0;

	double atmos_x, atmos_y, atmos_z;
	double Ta, Tb, Tc;
	double Ta_l, Tb_l, Tc_l;

	double	t1, t2, t, H_compute;
	double m, n, p;

	m = Farpoint_x - Nearpoint_x;
	n = Farpoint_y - Nearpoint_y;
	p = Farpoint_z -Nearpoint_z;

	double DZ_atmos = DZ + atmos_H;
	double CZ_atmos = CZ + atmos_H;

	double DZ_earth = DZ;
	double CZ_earth = CZ;

	Ta = DZ_atmos*DZ_atmos*(m*m + n*n) + CZ_atmos*CZ_atmos*p*p;
	Tb = 2 * DZ_atmos*DZ_atmos * (Nearpoint_x*m + Nearpoint_y*n) + 2 * CZ_atmos*CZ_atmos*Nearpoint_z*p;
	Tc = DZ_atmos*DZ_atmos*(Nearpoint_x*Nearpoint_x + Nearpoint_y*Nearpoint_y)
		+ CZ_atmos*CZ_atmos*Nearpoint_z*Nearpoint_z
		- CZ_atmos*CZ_atmos*DZ_atmos*DZ_atmos;




	Ta_l= DZ_earth*DZ_earth*(m*m + n*n) + CZ_earth*CZ_earth*p*p;
	Tb_l= 2 * DZ_earth*DZ_earth * (Nearpoint_x*m + Nearpoint_y*n) + 2 * CZ_earth*CZ_earth*Nearpoint_z*p;
	Tc_l= DZ_earth*DZ_earth*(Nearpoint_x*Nearpoint_x + Nearpoint_y*Nearpoint_y)
		+ CZ_earth*CZ_earth*Nearpoint_z*Nearpoint_z
		- CZ_earth*CZ_earth*DZ_earth*DZ_earth;



	double deltaT = Tb*Tb - 4 * Ta*Tc;
	double deltaT_l = Tb_l*Tb_l - 4 * Ta_l*Tc_l;
	double flag;


	if (deltaT<0)
	{
		flag = 0;//与大气没有交点
	}

	if (deltaT == 0)
	{
		flag = 1;//与大气有一个交点
		t = (-Tb ) / 2 / Ta;
		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;
		xyz2geo(atmos_x, atmos_y, atmos_z, atmos_L, atmos_B, &H_compute, axis_type);


	}
	if (deltaT >0&&deltaT_l<0)
	{
		flag = 2;//与大气两个交点与陆表没有交点

		t1 = (-Tb + sqrt(deltaT)) / 2 / Ta;
		t2 = (-Tb - sqrt(deltaT)) / 2 / Ta;

		if (abs(t1)<abs(t2))
		{

			t = t1;
		}
		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;

		xyz2geo(atmos_x, atmos_y, atmos_z, atmos_L, atmos_B, &H_compute, axis_type);
	}

	if ((deltaT>0) && (deltaT_l == 0))
	{
		flag = 3;//与大气两个交点与陆表一个交点



		t1 = (-Tb + sqrt(deltaT)) / 2 / Ta;
		t2 = (-Tb - sqrt(deltaT)) / 2 / Ta;

		if (abs(t1)<abs(t2))
		{

			t = t1;
		}
		else
		{
			t = t2;
		}

		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;

		xyz2geo(atmos_x, atmos_y, atmos_z, atmos_L, atmos_B, &H_compute, axis_type);


		t = (-Tb_l) / 2 / Ta_l;
		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;
		xyz2geo(atmos_x, atmos_y, atmos_z, Land_L, Land_B, &H_compute, axis_type);


	}

	if ((deltaT>0) && (deltaT_l >0))
	{
		flag = 4;//与大气两个交点与陆表两个交点


		t1 = (-Tb + sqrt(deltaT)) / 2 / Ta;
		t2 = (-Tb - sqrt(deltaT)) / 2 / Ta;

		if (abs(t1)<abs(t2))
		{

			t = t1;
		}
		else
		{
			t = t2;
		}

		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;

		xyz2geo(atmos_x, atmos_y, atmos_z, atmos_L, atmos_B, &H_compute, axis_type);


		t1 = (-Tb_l + sqrt(deltaT_l)) / 2 / Ta_l;
		t2 = (-Tb_l- sqrt(deltaT_l)) / 2 / Ta_l;

		if (abs(t1)<abs(t2))
		{

			t = t1;
		}
		else
		{
			t = t2;
		}

		atmos_x = Nearpoint_x + m*t;
		atmos_y = Nearpoint_y + n*t;
		atmos_z = Nearpoint_z + p*t;
		xyz2geo(atmos_x, atmos_y, atmos_z, Land_L, Land_B, &H_compute, axis_type);


	}


	return flag;


}



/*函数说明 viewpointline2atmosphereXYZ
输入：
viewpoint_L double型  大地坐标下视点的经度 单位为度
viewpoint_B  double型  大地坐标下视点的纬度 单位为度
viewponit_H double型  大地坐标下视点的高度 单位为米
Farpoint_x  double型  离视点近点直角坐标系下x轴坐标值 单位为米
Farpoint_y double型  离视点近点直角坐标系下x轴坐标值 单位为米
Farpoint_z double型   离视点近点直角坐标系下x轴坐标值 单位为米
atmos_H  double型   大气椭球面的高度（99km为大气层顶，0km为地表）

输出：
atmos_L double*型  视线对应的大地坐标下大气层顶的经度 单位为度
atmos_B double*型       视线对应的大地坐标下大气层顶的纬度 单位为度
land_L double*型  大地坐标下大气层顶的经度 单位为度
land_B double*型  大地坐标下大气层顶的纬度 单位为度

状态变量 flag 0  为视线与大气没有交点
1 为视线与大气层顶只有一个交点
2  视线与大气有两个交点与地表没有交点
3 视线与大气有两个交点与地表一个交点
4 视线与大气两个交点与地表两个交点
*/

int viewpointline2atmosphereXYZ(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double Farpoint_x, double Farpoint_y, double Farpoint_z, double atmos_H,
	double *atmos_L, double *atmos_B,
	double *Land_L, double *Land_B,
	int axis_type)
{

	double viewpoint_x, viewpoint_y, viewpoint_z, atmos_x, atmos_y, atmos_z;
	geo2xyz(viewpoint_L, viewpoint_B, viewponit_H, &viewpoint_x, &viewpoint_y, &viewpoint_z, axis_type);
	int flag;
	flag = line2atmosphereXYZ(viewpoint_x, viewpoint_y, viewpoint_z,
		Farpoint_x,  Farpoint_y, Farpoint_z, atmos_H,atmos_L, atmos_B,Land_L,Land_B,axis_type);
	return flag;


}
