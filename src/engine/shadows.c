/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:31 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:05:32 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Checks if the COLISION point is in shadow */
int	is_in_shadow(double *colision, t_light *light)
{
	double	l[3];
	double	t;
	t_shape	*tmp;

	vec(colision, light->position, l);
	tmp = g_scene.shapes;
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, light->position, colision, 1);
		if (t > 0.00000001 && t < 0.99999999)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
