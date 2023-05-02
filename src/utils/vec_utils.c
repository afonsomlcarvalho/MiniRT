#include "../../inc/minirt.h"

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

double	vector_size(double *vector)
{
	return (sqrt(pow(vector[X], 2) + pow(vector[Y], 2) + pow(vector[Z], 2)));
}

/* Normalizes the vector starting at ORIGIN and ending at DESTINATION 
 * storing the new vector in NORM */
void	normalize_vector(double *vector, double *norm)
{
	double	size;

	size = sqrt(pow(vector[X], 2) + pow(vector[Y], 2) + pow(vector[Z], 2));
	norm[X] = vector[X] / size;
	norm[Y] = vector[Y] / size;
	norm[Z] = vector[Z] / size;
}

int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
