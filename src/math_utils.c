#include "../inc/minirt.h"
#include <math.h>

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
	if (!flag && (result1 < 0 || result2 < 0))
	{
		if (result1 < 0 && result2 < 0)
			return (0.0);
		if (result1 < 0)
			return (result2);
		if (result2 < 0)
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

double	vector_size(double *vector)
{
	return (sqrt(pow(vector[X], 2) + pow(vector[Y], 2) + pow(vector[Z], 2)));
}

/* Normalizes the vector starting at ORIGIN and ending at DESTINATION 
 * storing the new vector in NORM */
void	normalize_vector(double *origin, double *destination, double *norm)
{
	double	size;
	double	v[3];

	vec(origin, destination, v);
	size = sqrt(pow(v[X], 2) + pow(v[Y], 2) + pow(v[Z], 2));
	norm[X] = v[X] / size;
	norm[Y] = v[Y] / size;
	norm[Z] = v[Z] / size;
}

/* Multiplies each point of VEC by FACTOR, storing the result in BUFF*/
void	mult_vecs(double factor, double *vec, double *buff)
{
	buff[X] = vec[X] * factor;
	buff[Y] = vec[Y] * factor;
	buff[Z] = vec[Z] * factor;
}

/* Stores the result of the operation V1 - V2 in BUFF */
void	subtract_vecs(double *v1, double *v2, double *buff)
{
	buff[X] = v1[X] - v2[X];
	buff[Y] = v1[Y] - v2[Y];
	buff[Z] = v1[Z] - v2[Z];
}

void	translate(double *point, double *vector)
{
	point[X] += vector[X];
	point[Y] += vector[Y];
	point[Z] += vector[Z];
}

void	cross_product(double *v1, double *v2, double *buf)
{
	int	i;

	buf[X] = v1[Y] * v2[Z] - v1[Z] * v2[Y];
	buf[Y] = v1[X] * v2[Z] - v1[Z] * v2[X];
	buf[Z] = v1[X] * v2[Y] - v1[Y] * v2[X];
	i = -1;
	while (++i < 3)
	{
		if (buf[i])
			return ;
	}
	buf[X] = (v1[X] == 0 && v2[X] == 0);
	buf[Y] = (v1[Y] == 0 && v2[Y] == 0);
	buf[Z] = (v1[Z] == 0 && v2[Z] == 0);
}
