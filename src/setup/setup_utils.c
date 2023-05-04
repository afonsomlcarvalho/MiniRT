/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:55 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:53:17 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_vectors(double *w_vector, double *h_vector)
{
	double			up[3];

	up[1] = 1;
	up[0] = 0;
	up[2] = 0;
	cross_product(up, g_scene.camera.direction, w_vector);
	if (!g_scene.camera.direction[X] && !g_scene.camera.direction[Z] && \
	g_scene.camera.direction[Y])
	{
		w_vector[X] = 1;
		w_vector[Y] = 0;
		w_vector[Z] = 0;
	}
	cross_product(w_vector, g_scene.camera.direction, h_vector);
}

void	verify_parse(int *error)
{
	t_light	*cur;

	if (!g_scene.cam_counter)
		*error += parsing_error("No camera.\n");
	if (!g_scene.lights)
		*error += parsing_error("No ambient light.\n");
	else
	{
		cur = g_scene.lights;
		while (cur && cur->type)
			cur = cur->next;
		if (!cur)
			*error += parsing_error("No ambient light.\n");
	}
}
