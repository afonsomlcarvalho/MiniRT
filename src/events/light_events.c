/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:41 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:05:42 by amorais-         ###   ########.fr       */
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
	if (!g_scene.selected_light)
	{
		if (movement[X] || movement[Y] || movement[Z])
			printf("%sError: No light point available%s\n", RED_TEXT, RESET_TEXT);
		return ;
	}
	g_scene.selected_light->position[X] += movement[X];
	g_scene.selected_light->position[Y] += movement[Y];
	g_scene.selected_light->position[Z] += movement[Z];
}
