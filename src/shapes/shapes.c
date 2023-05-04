/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:21 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 13:01:47 by gda-cruz         ###   ########.fr       */
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

int	inside_sphere(void *self)
{
	t_sphere	*sphere;
	double		left_hand;

	sphere = (t_sphere *)self;
	left_hand = pow((g_scene.camera.origin[X] - sphere->center[X]), 2) + \
	pow((g_scene.camera.origin[Y] - sphere->center[Y]), 2) + \
	pow((g_scene.camera.origin[Z] - sphere->center[Z]), 2);
	return (left_hand < pow(sphere->radius, 2));
}

int	inside_cylinder(void *self)
{
	t_cylinder	*cylinder;
	double		alpha;
	double		cp[3];
	double		ap_size;
	double		ca_size;

	cylinder = (t_cylinder *)self;
	subtract_vecs(g_scene.camera.origin, cylinder->center, cp);
	alpha = acos(dot(cp, cylinder->axis) / (vector_size(cp) * vector_size(cylinder->axis)));
	ap_size = sin(alpha) * vector_size(cp);
	ca_size = cos(alpha) * vector_size(cp);
	return ((ap_size < cylinder->radius) && (ca_size < cylinder->height / 2));
}

int	is_inside_object(void)
{
	t_shape	*tmp;

	tmp = g_scene.shapes;
	while (tmp)
	{
		if (tmp->type == SPHERE && inside_sphere(tmp->shape))
			return (1);
		else if (tmp->type == CYLINDER && inside_cylinder(tmp->shape))
			return (1);
		// else if (tmp->type == CONE && inside_cylinder(tmp->shape))
		// 	return (1);
		tmp = tmp->next;
	}
	return (0);
}
