/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:24 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 16:19:14 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	add_back_light(t_light *new_light)
{
	t_light	*tmp;

	if (!new_light)
		return ;
	if (!g_scene.lights)
	{
		g_scene.lights = new_light;
		return ;
	}
	tmp = g_scene.lights;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_light;
}

int	light_setup(char **info, int flag)
{
	t_light		*light;
	static int	c;
	int			error;

	if (!flag && c)
		return (parsing_error("More than one ambient light.\n"));
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		error_handler();
	error = 0;
	add_back_light(light);
	if (array_size(info) != 3 + flag)
		return (parsing_error("Invalid number of arguments for lights.\n"));
	if (coords_interpreter(info[1 + flag], &light->brightness) \
		|| light->brightness < 0 || light->brightness > 1)
		error += parsing_error("Invalid light brightness.\n");
	if (get_color(info[2 + flag], light->color))
		error += parsing_error("Invalid light colour.\n");
	light->type = flag;
	c += (flag == 0);
	light->next = NULL;
	if (flag && coords_interpreter(info[1], light->position))
		error += parsing_error("Invalid light position.\n");
	return (error);
}

void	determine_light(t_lightaux *lightaux, double *origin, t_shape *shape)
{
	t_light	*cur;
	int		i;

	lightaux->light[0] = 0;
	lightaux->light[1] = 0;
	lightaux->light[2] = 0;
	cur = g_scene.lights;
	while (cur)
	{
		if (cur->type == AMBIENT)
		{
			i = -1;
			while (++i < 3)
				lightaux->light[i] += cur->brightness * \
				((double) cur->color[i] / 255);
		}
		else if (!is_in_shadow(lightaux->colision, cur, shape))
		{
			diffuse_reflection(lightaux, cur);
			specular_reflection(lightaux, origin, cur, shape);
		}
		cur = cur->next;
	}
}
