/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:46 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:13:38 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	change_sphere(int keycode)
{
	t_sphere	*sphere;
	double		factor;

	if (keycode == 65363)
		factor = 0.1;
	else if (keycode == 65361)
		factor = -0.1;
	else
		return ;
	sphere = g_scene.selected->shape;
	if (sphere->radius < 0.1 && keycode == 65361)
		return ;
	sphere->radius *= (1 + factor);
	split_canva();
}

static void	change_cylinder(int keycode)
{
	t_cylinder	*cylinder;
	double		factor;

	factor = 0;
	if (keycode == 65363 || keycode == 65362)
		factor = 0.1;
	else if (keycode == 65361 || keycode == 65364)
		factor = -0.1;
	cylinder = g_scene.selected->shape;
	if ((cylinder->radius < 1 && keycode == 65361) || \
	(cylinder->height < 1 && keycode == 65364))
		return ;
	if (keycode == 65363 || keycode == 65361)
		cylinder->radius *= (1 + factor);
	else
		cylinder->height *= (1 + factor);
	substitute_caps(cylinder);
	split_canva();
}

static void	change_cone(int keycode)
{
	t_cone	*cone;
	double	factor;

	factor = 0;
	cone = g_scene.selected->shape;
	if (keycode == 65362 || keycode == 65363)
		factor = 0.1;
	else if (keycode == 65364 || keycode == 65361)
		factor = -0.1;
	if ((cone->radius < 1 && keycode == 65361) || \
	(cone->height < 1 && keycode == 65364))
		return ;
	if (keycode == 65361 || keycode == 65363)
		cone->radius *= (1 + factor);
	else
		cone->height *= (1 + factor);
	substitute_cone_base(cone);
	split_canva();
}

void	change_shape_size(int keycode)
{
	if (!g_scene.selected)
	{
		printf("%sError: No shape selected%s\n", RED_TEXT, RESET_TEXT);
		fflush(stdout);
		return ;
	}
	if (g_scene.selected->type == SPHERE)
		change_sphere(keycode);
	else if (g_scene.selected->type == CYLINDER)
		change_cylinder(keycode);
	else if (g_scene.selected->type == CONE)
		change_cone(keycode);
}
