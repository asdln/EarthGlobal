#include<math.h>
#include"Atan2.h"
#include"Ge0_xyz.h"
/*
地心坐标系：
WGS_84
CGCS2000
参心坐标系：
Beijing54
XIAN80
NewBeijing54
*/
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




#ifndef PI

#define PI
#define pi 3.1415926535897932384626433832795
#endif


void geo2xyz(double L, double B, double h, double *x, double *y, double*z,int axis_type)
{

	B = B*pi / 180;
	L = L*pi / 180;
	double a, b;
	switch (axis_type)
	{

	case 1:
	{
		a = CZ_Beijing54;
		b = DZ_Beijing54;
		break;
	}
		
	case 2:
	{
		a = CZ_XIAN80;
		b = DZ_XIAN80;
		break;
	}

	case 3:
	{
		a = CZ_NewBeijing54;
		b = DZ_NewBeijing54;
		break;
	}



	case 4:
	{
		a = CZ_CGCS2000;
		b = DZ_CGCS2000;
		break;
	}



	case 5:
	{
		a = CZ_WGS84;
		b = DZ_WGS84;
		break;
	}

	default:
		break;
	}


	
		double e = sqrt(a*a - b *b) / a;
		double N = a / (sqrt(1 - e*e*(sin(B)*sin(B))));

    *x = (N + h)*cos(B)*cos(L);
	*y = (N + h)*cos(B)*sin(L);
	*z = (N*(1 - e *e) + h)*sin(B);
}


void xyz2geo(double x, double y, double z, double *L, double *B, double *H, int axis_type)
{
	double a, b;
	switch (axis_type)
	{

	case 1:
	{
		a = CZ_Beijing54;
		b = DZ_Beijing54;
		break;
	}

	case 2:
	{
		a = CZ_XIAN80;
		b = DZ_XIAN80;
		break;
	}

	case 3:
	{
		a = CZ_NewBeijing54;
		b = DZ_NewBeijing54;
		break;
	}



	case 4:
	{
		a = CZ_CGCS2000;
		b = DZ_CGCS2000;
		break;
	}



	case 5:
	{
		a = CZ_WGS84;
		b = DZ_WGS84;
		break;
	}

	default:
		break;
	}



	double e = sqrt(a*a - b *b) / a;
		*L = Atan2(y, x);

		double B0 = Atan2((a*z), (b*sqrt(x*x + y*y)));
		double N;
		while (1)
		{
			N = a / (sqrt(1 - (e*e)*(sin(B0)*sin(B0))));
				*B = Atan2(z + N*(e*e)*sin(B0), (sqrt(x*x + y*y)));
			*H = (sqrt(x*x + y*y))/cos(*B) - N;
			if (abs(B0 - *B) < 1e-8)
			{
				break;
			}
				B0 = *B;


		}
		*B = *B * 180 / pi;
	    *L = *L * 180 / pi;


}