#include "../inc/minirt.h"

/* Returns the dot product between V1 and V2 */
float	dot(float *v1, float *v2)
{
	return ((v1[X] * v2[X]) + (v1[Y] * v2[Y]) + (v1[Z] * v2[Z]));
}

/* Calculates the vector starting at P1 and passing 
 * through P2, storing it in buff */
void	vec(float *p1, float *p2, float *buff)
{
	buff[X] = p2[X] - p1[X];
	buff[Y] = p2[Y] - p1[Y];
	buff[Z] = p2[Z] - p1[Z];
}

/* Returns the smaller of the two numbers */
float	min(float n1, float n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

/* Solves the quadratic equation defined by
 * the parameters, returning the smallest solution
 * if greater than 1, and 0 otherwise */
float	solve_quadratic(float a, float b, float c, int flag)
{
	float	result1;
	float	result2;

	if ((pow(b, 2) - 4 * a * c) < 0)
		return (0.0);
	result1 = ((-b + sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	result2 = ((-b - sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a));
	if (flag == 2)
		printf("a: %f, b: %f, c: %f\n%f %f\n%f\n", a, b, c, result1, result2, sqrt(pow(b, 2) - 4 * a * c));
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

