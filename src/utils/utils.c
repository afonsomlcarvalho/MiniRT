#include "../../inc/minirt.h"

int	coords_interpreter(char *coords, double *point)
{
	int	i;
	int	axis;
	int	sign;
	int	decimal;

	i = 0;
	axis = 0;
	while (coords[i])
	{
		decimal = 1;
		sign = coords[i] == '-';
		if (sign)
			i++;
		while (coords[i] && coords[i] != '.' && coords[i] != ',')
		{
			if (!ft_isdigit(coords[i]))
				return (1);
			point[axis] = point[axis] * 10 + (coords[i++] - '0');
		}
		if (coords[i] == '.' && i++)
		{
			while (coords[i] && coords[i] != ',')
			{
				if (!ft_isdigit(coords[i]))
					return (1);
				point[axis] += (coords[i++] - '0') / pow(10, decimal++);
			}
		}
		point[axis++] *= (sign == 0) - (sign != 0);
		i += coords[i] == ',';
	}
	return (0);
}

int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	check_normalized_vector(double *vector)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (vector[i] < -1 || vector[i] > 1)
			return (1);
		i++;
	}
	return (0);
}

/* Finds the intersection point of the ray from the camera passing
 * through point p according to t */
void	find_point(double t, double *origin, double *p, double *buf)
{
	buf[X] = origin[X] + t * (p[X] - origin[X]);
	buf[Y] = origin[Y] + t * (p[Y] - origin[Y]);
	buf[Z] = origin[Z] + t * (p[Z] - origin[Z]);
}

/* Calculates the reflection of INCOMING_RAY according ro the surface NORMAL
 * and stores the resulting vector in REFLECTED_RAY */
void	get_reflected_ray(double *incoming_ray, double *normal, double *reflected_ray)
{
	double	Ln[3];
	double	Lp[3];

	mult_vecs(dot(normal, incoming_ray), normal, Ln);
	subtract_vecs(incoming_ray, Ln, Lp);
	subtract_vecs(Lp, Ln, reflected_ray);
}
