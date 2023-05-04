/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:21 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 15:39:25 by amorais-         ###   ########.fr       */
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

int	inside_sphere(void *self, double *point)
{
	double		left_hand;
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	left_hand = pow((point[X] - sphere->center[X]), 2) + \
	pow((point[Y] - sphere->center[Y]), 2) + \
	pow((point[Z] - sphere->center[Z]), 2);
	return (left_hand < pow(sphere->radius, 2));
}

int	inside_cylinder(void *self, double *point)
{
	double		alpha;
	double		cp[3];
	double		ap_size;
	double		ca_size;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *) self;
	subtract_vecs(point, cylinder->center, cp);
	alpha = acos(dot(cp, cylinder->axis) / \
	(vector_size(cp) * vector_size(cylinder->axis)));
	ap_size = sin(alpha) * vector_size(cp);
	ca_size = cos(alpha) * vector_size(cp);
	return ((ap_size < cylinder->radius) && (ca_size < cylinder->height / 2));
}

int	inside_cone(void *self, double *point)
{
	double	axis_point[3];
	double	k;
	double	vector[3];
	double	radius;
	t_cone	*cone;

	cone = (t_cone *) self;
	vec(point, cone->vertix, vector);
	k = (-dot(vector, cone->axis)) / dot(cone->axis, cone->axis);
	axis_point[X] = cone->vertix[X] + k * cone->axis[X];
	axis_point[Y] = cone->vertix[Y] + k * cone->axis[Y];
	axis_point[Z] = cone->vertix[Z] + k * cone->axis[Z];
	radius = tan(to_rad(cone->angle / 2)) * distance(cone->vertix, axis_point);
	return (distance(point, axis_point) < radius && \
	distance(cone->vertix, axis_point) < cone->height && k > 0);
}

int	is_inside_object(double *point)
{
	t_shape	*tmp;

	tmp = g_scene.shapes;
	while (tmp)
	{
		if (tmp->type == SPHERE && \
		inside_sphere((t_sphere *) tmp->shape, point))
			return (1);
		else if (tmp->type == CYLINDER && \
		inside_cylinder((t_cylinder *) tmp->shape, point))
			return (1);
		else if (tmp->type == CONE && inside_cone((t_cone *)tmp->shape, point))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
