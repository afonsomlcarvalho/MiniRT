#include "../../inc/minirt.h"

/* Returns the smaller of the two numbers */
double	min(double n1, double n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

/* Solves the quadratic equation defined by
 * the parameters, returning the smallest solution
 * if greater than 1, and 0 otherwise */
double	solve_quadratic(double a, double b, double c, int flag)
{
	double	result1;
	double	result2;

	if ((pow(b, 2) - 4 * a * c) < 0.00000001)
		return (0.0);
	result1 = ((-b + sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	result2 = ((-b - sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	if (!flag && (result1 < 0.0000001 || result2 < 0.00000001))
	{
		if (result1 < 0.0000001 && result2 < 0.000000001)
			return (0.0);
		if (result1 < 0.0000001)
			return (result2);
		if (result2 < 0.0000001)
			return (result1);
	}
	if (flag && result1 == 0)
		return (result2);
	if (flag && result2 == 0)
		return (result1);
	if (result1 == result2)
		return (result1);
	return (min(result1, result2));
}

double	distance(double *p1, double *p2)
{
	return (sqrt(pow(p1[X] - p2[X], 2) + pow(p1[Y] - p2[Y], 2) + pow(p1[Z] - p2[Z], 2)));
}

/* Converts DEG from degrees to radians */
double	to_rad(int deg)
{
	return (deg * M_PI / 180);
}

/* Converts RAD from radians to degrees */
double	to_deg(double rad)
{
	return (rad * 180 / M_PI);
}
