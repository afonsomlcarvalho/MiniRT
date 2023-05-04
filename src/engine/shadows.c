/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:31 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 16:17:06 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Checks if the COLISION point is in shadow */
int	is_in_shadow(double *colision, t_light *light, t_shape *shape)
{
	double	l[3];
	double	t;
	t_shape	*tmp;

	vec(colision, light->position, l);
	tmp = g_scene.shapes;
	if (shape->is_inside(shape->shape, light->position) != \
	shape->is_inside(shape->shape, g_scene.camera.origin))
		return (1);
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, light->position, colision, 1);
		if (t > 0.00000001 && t < 0.99999999)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
