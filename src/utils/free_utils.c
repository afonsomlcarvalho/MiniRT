/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:32 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:33 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	clear_shapes(void)
{
	t_shape	*temp;

	while (g_scene.shapes)
	{
		temp = g_scene.shapes->next;
		if (g_scene.shapes->type == CYLINDER)
		{
			if (((t_cylinder *)(g_scene.shapes->shape))->top_cap)
				free(((t_cylinder *)(g_scene.shapes->shape))->top_cap);
			if (((t_cylinder *)(g_scene.shapes->shape))->under_cap)
				free(((t_cylinder *)(g_scene.shapes->shape))->under_cap);
		}
		if (g_scene.shapes->shape)
			free(g_scene.shapes->shape);
		free(g_scene.shapes);
		g_scene.shapes = temp;
	}
	g_scene.shapes = NULL;
}

static void	clear_lights(void)
{
	t_light	*temp;

	while (g_scene.lights)
	{
		temp = g_scene.lights->next;
		free(g_scene.lights);
		g_scene.lights = temp;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void	free_all(int flag)
{
	clear_shapes();
	clear_lights();
	if (flag)
	{
		if (g_scene.img.img_ptr)
			mlx_destroy_image(g_scene.mlx, g_scene.img.img_ptr);
		if (g_scene.win)
			mlx_destroy_window(g_scene.mlx, g_scene.win);
		if (g_scene.mlx)
		{
			mlx_destroy_display(g_scene.mlx);
			free(g_scene.mlx);
		}
	}
}

int	end(void)
{
	printf("%s\n[Quitting...]\n\n%s", CYAN_TEXT, RESET_TEXT);
	free_all(1);
	exit(0);
	return (0);
}
