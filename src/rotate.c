#include "../inc/minirt.h"

void	x_rotate(double *vector, double angle)
{
	double	new[3];
	int		i;

	new[X] = vector[X];
	new[Y] = cos(angle) * vector[Y] - sin(angle) * vector[Z];
	new[Z] = sin(angle) * vector[Y] + cos(angle) * vector[Z];
	i = -1;
	while (++i < 3)
		vector[i] = new[i];
}

void	y_rotate(double *vector, double angle)
{
	double	new[3];
	int		i;

	new[Y] = vector[Y];
	new[Z] = cos(angle) * vector[Z] - sin(angle) * vector[X];
	new[X] = sin(angle) * vector[Z] + cos(angle) * vector[X];
	i = -1;
	while (++i < 3)
		vector[i] = new[i];
}

void	z_rotate(double *vector, double angle)
{
	double	new[3];
	int		i;

	new[Z] = vector[Z];
	new[X] = cos(angle) * vector[X] - sin(angle) * vector[Y];
	new[Y] = sin(angle) * vector[X] + cos(angle) * vector[Y];
	i = -1;
	while (++i < 3)
		vector[i] = new[i];
}

void	rotate(double *vector, double *angle)
{
	x_rotate(vector, angle[0]);
	y_rotate(vector, angle[1]);
	z_rotate(vector, angle[2]);
}
