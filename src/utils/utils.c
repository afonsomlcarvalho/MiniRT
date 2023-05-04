/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:43 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:44 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	coords_interpreter_aux(char *coords, double *point, int *i, int axis)
{
	int	decimal;

	decimal = 1;
	while (coords[*i] && coords[*i] != '.' && coords[*i] != ',')
	{
		if (!ft_isdigit(coords[*i]))
			return (1);
		point[axis] = point[axis] * 10 + (coords[(*i)++] - '0');
	}
	if (coords[*i] == '.' && (*i)++)
	{
		while (coords[*i] && coords[*i] != ',')
		{
			if (!ft_isdigit(coords[*i]))
				return (1);
			point[axis] += (coords[(*i)++] - '0') / pow(10, decimal++);
		}
	}
	return (0);
}

int	coords_interpreter(char *coords, double *point)
{
	int	i;
	int	axis;
	int	sign;

	i = 0;
	axis = 0;
	while (coords[i])
	{
		sign = coords[i] == '-';
		if (sign)
			i++;
		if (coords_interpreter_aux(coords, point, &i, axis))
			return (1);
		point[axis++] *= (sign == 0) - (sign != 0);
		i += coords[i] == ',';
	}
	return (0);
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
void	get_reflected_ray(double *incoming_ray, \
double *normal, double *reflected_ray)
{
	double	ln[3];
	double	lp[3];
	double	tmp[3];

	mult_vecs(1, normal, tmp);
	if (dot(incoming_ray, normal) < 0)
		mult_vecs(-1, normal, tmp);
	mult_vecs(dot(tmp, incoming_ray), tmp, ln);
	subtract_vecs(incoming_ray, ln, lp);
	subtract_vecs(lp, ln, reflected_ray);
}
