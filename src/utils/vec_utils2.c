/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:49 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:50 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

/* Stores the result of the operation V1 + V2 in BUFF */
void	add_vecs(double *v1, double *v2, double *buff)
{
	buff[X] = v1[X] + v2[X];
	buff[Y] = v1[Y] + v2[Y];
	buff[Z] = v1[Z] + v2[Z];
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
