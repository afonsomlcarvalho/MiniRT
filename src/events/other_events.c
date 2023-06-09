/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:44 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:33:14 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	change_reflection(void)
{
	if (!g_scene.selected)
	{
		printf("%sError: No shape selected%s\n", RED_TEXT, RESET_TEXT);
		return ;
	}
	if (g_scene.texture)
	{
		printf("%sError: Remove ruggedness to apply reflection%s\n", \
		RED_TEXT, RESET_TEXT);
		return ;
	}
	g_scene.selected->reflection += 0.1;
	if (g_scene.selected->reflection > 0.5)
		g_scene.selected->reflection = 0.0;
	printf("%sReflection Factor: %.1f%s\n", \
	GREEN_TEXT, g_scene.selected->reflection, RESET_TEXT);
	fflush(stdout);
	split_canva();
}

void	change_texture(void)
{
	float	percentage;

	g_scene.texture += 10;
	if (g_scene.texture >= 70)
		g_scene.texture = 0;
	percentage = g_scene.texture / 60.0 * 100;
	printf("%sRuggedness: %.0f%%%s\n", GREEN_TEXT, percentage, RESET_TEXT);
	fflush(stdout);
	split_canva();
}

static int	change_depth_aux(int keycode)
{
	if (keycode == 65451)
	{
		if (g_scene.reflection < 6)
			g_scene.reflection++;
		else
		{
			printf("%sError: Reflection depth limit reached%s\n", \
		RED_TEXT, RESET_TEXT);
			return (1);
		}
	}
	else if (keycode == 65453)
	{
		if (g_scene.reflection > 0)
			g_scene.reflection--;
		else
		{
			printf("%sError: Reflection depth limit reached%s\n", \
		RED_TEXT, RESET_TEXT);
			return (1);
		}
	}
	return (0);
}

void	change_depth(int keycode)
{
	if (g_scene.texture)
	{
		printf("%sError: Remove ruggedness to apply reflection%s\n", \
		RED_TEXT, RESET_TEXT);
		return ;
	}
	if (change_depth_aux(keycode))
		return ;
	printf("%sReflection Depth: %d%s\n", \
	GREEN_TEXT, g_scene.reflection, RESET_TEXT);
	fflush(stdout);
	split_canva();
}
