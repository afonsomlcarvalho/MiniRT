/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:41 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 15:45:02 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	change_light(void)
{
	t_light	*cur;

	cur = g_scene.lights;
	while (g_scene.selected_light)
	{
		g_scene.selected_light = g_scene.selected_light->next;
		if (!g_scene.selected_light || g_scene.selected_light->type)
			break ;
	}
	if (!g_scene.selected_light)
	{
		while (cur && !g_scene.selected_light)
		{
			if (cur->type)
				g_scene.selected_light = cur;
			cur = cur->next;
		}
	}
	split_canva();
}

void	move_light(double *movement)
{
	double	new_position[3];

	if (!g_scene.selected_light)
	{
		if (movement[X] || movement[Y] || movement[Z])
			printf("%sError: No light point available%s\n", \
			RED_TEXT, RESET_TEXT);
		return ;
	}
	new_position[X] = g_scene.selected_light->position[X] + movement[X];
	new_position[Y] = g_scene.selected_light->position[Y] + movement[Y];
	new_position[Z] = g_scene.selected_light->position[Z] + movement[Z];
	if (is_inside_object(new_position))
	{
		printf("%sError: Light points can't be inside objects%s\n", \
		RED_TEXT, RESET_TEXT);
		return ;
	}
	g_scene.selected_light->position[X] = new_position[X];
	g_scene.selected_light->position[Y] = new_position[Y];
	g_scene.selected_light->position[Z] = new_position[Z];
}
