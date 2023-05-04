/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:40 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:20:19 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	x_rotate(double *vector, double angle)
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

static void	y_rotate(double *vector, double angle)
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

static void	z_rotate(double *vector, double angle)
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

void	apply_translation_and_rotation(t_shape *selected, \
	double *vector, double *angle)
{
	if (!selected)
	{
		translate(g_scene.camera.origin, vector);
		rotate(g_scene.camera.direction, angle);
	}
	else if (selected->type == SPHERE)
		translate(((t_sphere *)(selected->shape))->center, vector);
	else if (selected->type == CYLINDER)
	{
		translate(((t_cylinder *)(selected->shape))->center, vector);
		rotate(((t_cylinder *)(selected->shape))->axis, angle);
		substitute_caps((t_cylinder *)(selected->shape));
	}
	else if (selected->type == PLANE)
	{
		translate(((t_plane *)(selected->shape))->point, vector);
		rotate(((t_plane *)(selected->shape))->normal, angle);
	}
	else if (selected->type == CONE)
	{
		translate(((t_cone *)(selected->shape))->vertix, vector);
		rotate(((t_cone *)(selected->shape))->axis, angle);
		substitute_cone_base((t_cone *)(selected->shape));
	}
	split_canva();
}
