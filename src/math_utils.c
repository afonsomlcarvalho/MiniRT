#include "../inc/minirt.h"

/* Returns the dot product between V1 and V2 */
double	dot(double *v1, double *v2)
{
	return ((v1[X] * v2[X]) + (v1[Y] * v2[Y]) + (v1[Z] * v2[Z]));
}

/* Calculates the vector starting at P1 and passing 
 * through P2, storing it in buff */
void	vec(double *p1, double *p2, double *buff)
{
	buff[X] = p2[X] - p1[X];
	buff[Y] = p2[Y] - p1[Y];
	buff[Z] = p2[Z] - p1[Z];
}

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

	if ((pow(b, 2) - 4 * a * c) < 0)
		return (0.0);
	result1 = ((-b + sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	result2 = ((-b - sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	if (flag == 2)
		printf("\na: %lf, b: %lf, c: %lf\nrsults: %lf %lf\n", a, b, c, result1, result2);
	if (!flag && (result1 < 1 || result2 < 1))
	{
		if (result1 < 1 && result2 < 1)
			return (0.0);
		if (result1 < 1)
			return (result2);
		if (result2 < 1)
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