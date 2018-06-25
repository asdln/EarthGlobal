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


double getRotateAngle(double x1, double y1, double z1,
	double x2, double y2, double z2,
	double m, double n, double p)
{
	const double epsilon = 1.0e-6;
	const double nyPI = acos(-1.0);
	double dist, dot, degree, angle;

	// normalize
	dist = sqrt(x1*x1 + y1*y1 + z1*z1);
	x1 /= dist;
	y1 /= dist;
	z1 /= dist;
	dist = sqrt(x2*x2 + y2*y2 + z2*z2);
	x2 /= dist;
	y2 /= dist;
	z2 /= dist;
	// dot product
	double cross;
	dot = x1*x2 + y1*y2 + z1*z2;
	if (fabs(dot - 1.0) <= epsilon)
		angle = 0.0;
	else if (fabs(dot + 1.0) <= epsilon)
		angle = nyPI;
	else {


		angle = acos(dot);
		//cross product
		cross = (x1 * y2 - x2 * y1)*p - (x1*z2 - z1*x2)*n + (y1*z2 - z1*y2)*m;
		// vector p2 is clockwise from vector p1
		// with respect to the origin (0.0)
		if (cross < 0) {
			angle = 2 * nyPI - angle;
		}
	}
	degree = angle *  180.0 / nyPI;
	return degree;
}



/*函数说明 viewpoint2targetangle
输入：viewpoint_L double型  大地坐标下视点的经度 单位为度
viewpoint_B  double型  大地坐标下视点的纬度 单位为度
viewponit_H double型  大地坐标下视点的高度 单位为米
target_L  double型  大地坐标下目标或者地表的经度 单位为度
target_B  double型  大地坐标下目标或者地表的纬度 单位为度
target_H  double型   大地坐标下目标或者地表的高度 单位为米

输出：Pitch double*型  俯仰角 单位为度
azimuth double*型     方位角 单位为度

状态变量 0  与视轴重合
        1  不与视轴重合

Pitch angle and azimuth angle
*/

int viewpoint2targetangle(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double target_L, double target_B, double target_H, double *Pitch, double *azimuth, int axis_type)
{

	const double epsilon = 1.0e-6;
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


	double target_x, target_y, target_z, viewpoint_x, viewpoint_y, viewpoint_z, atmos_x, atmos_y, atmos_z;
	double land_x, land_y, land_z;
	geo2xyz(viewpoint_L, viewpoint_B, viewponit_H, &viewpoint_x, &viewpoint_y, &viewpoint_z, axis_type);
	double viewpoint_B_H;
	double viewpoint_H_x, viewpoint_H_y, viewpoint_H_z;




	if (viewpoint_B > 70)
	{
		viewpoint_B_H = viewpoint_B - 10;

	}
	else
	{
		viewpoint_B_H = viewpoint_B + 10;

	}







	double m, n, p;

    geo2xyz(viewpoint_L, viewpoint_B_H, 0, &viewpoint_H_x, &viewpoint_H_y, &viewpoint_H_z, axis_type);

	geo2xyz(viewpoint_L, viewpoint_B, 0, &land_x, &land_y, &land_z, axis_type);

	m = -viewpoint_x+land_x;
	n = -viewpoint_y+land_y;
	p = -viewpoint_z+land_z;



	geo2xyz(target_L, target_B, target_H, &target_x, &target_y, &target_z, axis_type);



	double vector_viewpoint2target_x = target_x - viewpoint_x;
	double vector_viewpoint2target_y = target_y - viewpoint_y;
	double vector_viewpoint2target_z = target_z - viewpoint_z;





	double rH = m*vector_viewpoint2target_x + n*vector_viewpoint2target_y + p*vector_viewpoint2target_z;
	double rL = sqrt(m*m +n*n + p*p)*sqrt(vector_viewpoint2target_x*vector_viewpoint2target_x +
		vector_viewpoint2target_y*vector_viewpoint2target_y + vector_viewpoint2target_z*vector_viewpoint2target_z);
	double dot;
	if (fabs(rL) <= epsilon)
	{
		Pitch = 0;
		azimuth = 0;
		return 0;
	}
	else
	{
		dot = rH / rL;

		if (fabs(dot - 1.0) <= epsilon)

		{
			*Pitch = -90;
			*azimuth = 0;
			return 0;
		}
		else
		{ 

			*Pitch = acos(dot) * 180 / pi - 90;
		}

		

	}


	double dist_mnp = m*m + n*n + p*p;

	double vec1_x, vec1_y, vec1_z;
	double vec2_x, vec2_y, vec2_z;

	vec1_x = ((n*n + p*p)*(viewpoint_H_x - viewpoint_x) - m*n*(viewpoint_H_y - viewpoint_y) - m*p*(viewpoint_H_z - viewpoint_z)) / dist_mnp;
	vec1_y = ((m*m + p*p)*(viewpoint_H_y - viewpoint_y) - m*n*(viewpoint_H_x - viewpoint_x) - n*p*(viewpoint_H_z - viewpoint_z)) / dist_mnp;
	vec1_z = ((m*m + n*n)*(viewpoint_H_z - viewpoint_z) - m*p*(viewpoint_H_x - viewpoint_x) - n*p*(viewpoint_H_y - viewpoint_y)) / dist_mnp;

	vec2_x = ((n*n + p*p)*(target_x - viewpoint_x) - m*n*(target_y - viewpoint_y) - m*p*(target_z - viewpoint_z)) / dist_mnp;
	vec2_y = ((m*m + p*p)*(target_y - viewpoint_y) - m*n*(target_x - viewpoint_x) - n*p*(target_z - viewpoint_z)) / dist_mnp;
	vec2_z = ((m*m + n*n)*(target_z - viewpoint_z) - m*p*(target_x - viewpoint_x) - n*p*(target_y - viewpoint_y)) / dist_mnp;

	*azimuth=getRotateAngle(vec1_x, vec1_y,vec1_z,vec2_x, vec2_y, vec2_z, m,n,p);
	return 1;
}


/*函数说明 viewpoint2targetangle_xyz
输入：viewpoint_x double型  直角坐标系下目标x方向坐标 单位为米
viewpoint_y  double型  大直角坐标系下目标y方向坐标 单位为米
viewponit_z double型  直角坐标系下目标z方向坐标 单位为米
target_x double型  直角坐标系下目标x方向坐标 单位为米
target_y  double型    直角坐标系下目标y方向坐标 单位为米
target_z  double型     直角坐标系下目标z方向坐标 单位为米


输出：Pitch double*型  俯仰角 单位为度
azimuth double*型     方位角 单位为度

状态变量 0  与视轴重合
1  不与视轴重合

Pitch angle and azimuth angle
*/

int viewpoint2targetangle_xyz(double viewpoint_x, double viewpoint_y, double viewpoint_z,
	double target_x, double target_y, double target_z, double *Pitch, double *azimuth, int axis_type)
{

	const double epsilon = 1.0e-6;
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


	double atmos_x, atmos_y, atmos_z;
	double viewpoint_L, viewpoint_B, viewponit_H;
	double land_x, land_y, land_z;
	//geo2xyz(viewpoint_L, viewpoint_B, viewponit_H, &viewpoint_x, &viewpoint_y, &viewpoint_z, axis_type);

	xyz2geo(viewpoint_x, viewpoint_y, viewpoint_z, &viewpoint_L, &viewpoint_B, &viewponit_H, axis_type);


	double viewpoint_B_H;


	double viewpoint_H_x, viewpoint_H_y, viewpoint_H_z;

	if (viewpoint_B > 70)
	{
		viewpoint_B_H = viewpoint_B - 10;

	}
	else
	{
		viewpoint_B_H = viewpoint_B + 10;

	}


	double m, n, p;

	geo2xyz(viewpoint_L, viewpoint_B_H, 0, &viewpoint_H_x, &viewpoint_H_y, &viewpoint_H_z, axis_type);

	geo2xyz(viewpoint_L, viewpoint_B, 0, &land_x, &land_y, &land_z, axis_type);

	m = -viewpoint_x + land_x;
	n = -viewpoint_y + land_y;
	p = -viewpoint_z + land_z;



	//geo2xyz(target_L, target_B, target_H, &target_x, &target_y, &target_z, axis_type);



	double vector_viewpoint2target_x = target_x - viewpoint_x;
	double vector_viewpoint2target_y = target_y - viewpoint_y;
	double vector_viewpoint2target_z = target_z - viewpoint_z;





	double rH = m*vector_viewpoint2target_x + n*vector_viewpoint2target_y + p*vector_viewpoint2target_z;
	double rL = sqrt(m*m + n*n + p*p)*sqrt(vector_viewpoint2target_x*vector_viewpoint2target_x +
		vector_viewpoint2target_y*vector_viewpoint2target_y + vector_viewpoint2target_z*vector_viewpoint2target_z);
	double dot;
	if (fabs(rL) <= epsilon)
	{
		Pitch =0;
		azimuth =0;
		return 0;
	}
	else
	{
		dot = rH / rL;

		if (fabs(dot - 1.0) <= epsilon)

		{
			*Pitch = -90;
			*azimuth = 0;
			return 0;
		}
		else
		{

			*Pitch = acos(dot) * 180 / pi - 90;
		}



	}


	double dist_mnp = m*m + n*n + p*p;

	double vec1_x, vec1_y, vec1_z;
	double vec2_x, vec2_y, vec2_z;

	vec1_x = ((n*n + p*p)*(viewpoint_H_x - viewpoint_x) - m*n*(viewpoint_H_y - viewpoint_y) - m*p*(viewpoint_H_z - viewpoint_z)) / dist_mnp;
	vec1_y = ((m*m + p*p)*(viewpoint_H_y - viewpoint_y) - m*n*(viewpoint_H_x - viewpoint_x) - n*p*(viewpoint_H_z - viewpoint_z)) / dist_mnp;
	vec1_z = ((m*m + n*n)*(viewpoint_H_z - viewpoint_z) - m*p*(viewpoint_H_x - viewpoint_x) - n*p*(viewpoint_H_y - viewpoint_y)) / dist_mnp;

	vec2_x = ((n*n + p*p)*(target_x - viewpoint_x) - m*n*(target_y - viewpoint_y) - m*p*(target_z - viewpoint_z)) / dist_mnp;
	vec2_y = ((m*m + p*p)*(target_y - viewpoint_y) - m*n*(target_x - viewpoint_x) - n*p*(target_z - viewpoint_z)) / dist_mnp;
	vec2_z = ((m*m + n*n)*(target_z - viewpoint_z) - m*p*(target_x - viewpoint_x) - n*p*(target_y - viewpoint_y)) / dist_mnp;

	*azimuth = getRotateAngle(vec1_x, vec1_y, vec1_z, vec2_x, vec2_y, vec2_z, m, n, p);
	return 1;
}




	


