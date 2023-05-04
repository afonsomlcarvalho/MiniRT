/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:39 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 15:40:51 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	key_press_aux(double *vector, double *angle, double *light, int keycode)
{
	vector[X] = ((keycode == 100) - (keycode == 97)) * 0.1;
	vector[Y] = ((keycode == 119) - (keycode == 115)) * 0.1;
	vector[Z] = ((keycode == 101) - (keycode == 113)) * 0.1;
	angle[X] = to_rad(((keycode == 108) - (keycode == 106)) * 15);
	angle[Y] = to_rad(((keycode == 105) - (keycode == 107)) * 15);
	angle[Z] = to_rad(((keycode == 111) - (keycode == 117)) * 15);
	light[X] = ((keycode == 110) - (keycode == 118)) * 0.1;
	light[Y] = ((keycode == 103) - (keycode == 98)) * 0.1;
	light[Z] = ((keycode == 104) - (keycode == 102)) * 0.1;
}

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];
	double	light[3];

	if (keycode == 65307)
		end();
	if (keycode == 114)
		change_reflection();
	else if (keycode == 65505)
		change_texture();
	else if (keycode == 65361 || keycode == 65363 || \
			keycode == 65362 || keycode == 65364)
		change_shape_size(keycode);
	else if (keycode == 32)
		change_light();
	else if (keycode == 65451 || keycode == 65453)
		change_depth(keycode);
	else
	{
		key_press_aux(vector, angle, light, keycode);
		apply_translation_and_rotation(g_scene.selected, vector, angle);
		move_light(light);
	}
	return (0);
}

static void	select_piece_aux(double *point)
{
	double	t;
	t_shape	*cur;

	cur = g_scene.shapes;
	t = 0;
	while (cur)
	{
		if (cur->check_hit(cur->shape, point, g_scene.camera.origin, 0) && \
		(t == 0 || \
		cur->check_hit(cur->shape, point, g_scene.camera.origin, 0) < t))
		{
			g_scene.selected = cur;
			t = cur->check_hit(cur->shape, point, g_scene.camera.origin, 0);
		}
		cur = cur->next;
	}
}

int	select_piece(int button, int x, int y)
{
	double	point[3];

	if (button != 1 && button != 3)
		return (0);
	canvas_to_viewport(x - WIDTH / 2, y - HEIGHT / 2, point);
	if (button == 3 && g_scene.selected)
	{
		printf("\n");
		copy_color(g_scene.selected->backup_color, g_scene.selected->color);
		g_scene.selected = 0;
		split_canva();
	}
	else if (button == 1)
	{
		if (g_scene.selected)
			copy_color(g_scene.selected->backup_color, g_scene.selected->color);
		select_piece_aux(point);
		if (g_scene.selected)
		{
			apply_selection_color();
			split_canva();
		}
	}
	return (0);
}
