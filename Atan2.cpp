#include <math.h>


#ifndef PI
#define PI
#define pi 3.141592653
#endif

double Atan2(double y, double x)
{
	double theta;
	if (x == 0 && y > 0)
	{
		theta = pi / 2;
	}

	if (x == 0 && y < 0)
	{
		theta = -pi / 2;
	}
	if (x > 0)
	{
		theta = atan(y / x);
	}

	if (x < 0)
	{
		if (y < 0)

		{
			theta = atan(y / x) - pi;
		}
		else
		{
			theta = atan(y / x) + pi;
		}
	}

	if (x == 0 && y == 0)
	{
		theta = 0;
	}
	return theta;
}