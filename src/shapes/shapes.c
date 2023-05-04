/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:21 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 15:56:41 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Adds NEW_SHAPE to the end of the shapes list */
void	add_back_shape(t_shape *new_shape)
{
	t_shape	*tmp;

	if (!new_shape)
		return ;
	if (!g_scene.shapes)
	{
		g_scene.shapes = new_shape;
		return ;
	}
	tmp = g_scene.shapes;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_shape;
}

int	inside_sphere(t_sphere *self, double *point)
{
	double		left_hand;

	left_hand = pow((point[X] - self->center[X]), 2) + \
	pow((point[Y] - self->center[Y]), 2) + \
	pow((point[Z] - self->center[Z]), 2);
	return (left_hand < pow(self->radius, 2));
}

int	inside_cylinder(t_cylinder *self, double *point)
{
	double		alpha;
	double		cp[3];
	double		ap_size;
	double		ca_size;

	subtract_vecs(point, self->center, cp);
	alpha = acos(dot(cp, self->axis) / \
	(vector_size(cp) * vector_size(self->axis)));
	ap_size = sin(alpha) * vector_size(cp);
	ca_size = cos(alpha) * vector_size(cp);
	return ((ap_size < self->radius) && (ca_size < self->height / 2));
}

int	inside_cone(t_cone *self, double *point)
{
	double	axis_point[3];
	double	k;
	double	vector[3];
	double	radius;

	vec(point, self->vertix, vector);
	k = (-dot(vector, self->axis)) / dot(self->axis, self->axis);
	axis_point[X] = self->vertix[X] + k * self->axis[X];
	axis_point[Y] = self->vertix[Y] + k * self->axis[Y];
	axis_point[Z] = self->vertix[Z] + k * self->axis[Z];
	radius = tan(to_rad(self->angle / 2)) * distance(self->vertix, axis_point);
	return (distance(point, axis_point) < radius && \
	distance(self->vertix, axis_point) < self->height && k > 0);
}

int	is_inside_object(double *point)
{
	t_shape	*tmp;
	int		flag;

	flag = 0;
	tmp = g_scene.shapes;
	while (tmp)
	{
		if (tmp->type == SPHERE && \
		inside_sphere((t_sphere *) tmp->shape, point))
			tmp->camera_in = 1;
		else if (tmp->type == CYLINDER && \
		inside_cylinder((t_cylinder *) tmp->shape, point))
			tmp->camera_in = 1;
		else if (tmp->type == CONE && inside_cone((t_cone *)tmp->shape, point))
			tmp->camera_in = 1;
		else
			tmp->camera_in = 0;
		flag += tmp->camera_in;
		tmp = tmp->next;
	}
	return (flag);
}
