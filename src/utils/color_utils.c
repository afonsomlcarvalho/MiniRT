/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:27 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:28 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_color(char *coords, int *colors)
{
	int		red;
	int		green;
	int		blue;
	char	**arr;

	arr = ft_split(coords, ',');
	if (!arr)
		error_handler();
	red = ft_atoi(arr[0]);
	green = ft_atoi(arr[1]);
	blue = ft_atoi(arr[2]);
	free_array(arr);
	if (red < 0 || red > 255 || \
		green < 0 || green > 255 || \
		blue < 0 || blue > 255)
		return (1);
	colors[0] = red;
	colors[1] = green;
	colors[2] = blue;
	return (0);
}

int	rgb_to_color(int *rgb, double *light)
{
	int	red;
	int	green;
	int	blue;

	red = rgb[0] * light[0];
	green = rgb[1] * light[1];
	blue = rgb[2] * light[2];
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return ((red << 16) + (green << 8) + blue);
}

int	get_full_color(int local_color, int reflected_color, double r)
{
	int	local[3];
	int	reflected[3];
	int	full[3];

	local[0] = (local_color >> 16) & 255;
	local[1] = (local_color >> 8) & 255;
	local[2] = local_color & 255;
	reflected[0] = (reflected_color >> 16) & 255;
	reflected[1] = (reflected_color >> 8) & 255;
	reflected[2] = reflected_color & 255;
	full[0] = local[0] * (1 - r) + reflected[0] * r;
	full[1] = local[1] * (1 - r) + reflected[1] * r;
	full[2] = local[2] * (1 - r) + reflected[2] * r;
	if (full[0] > 255)
		full[0] = 255;
	if (full[1] > 255)
		full[1] = 255;
	if (full[2] > 255)
		full[2] = 255;
	return ((full[0] << 16) + (full[1] << 8) + full[2]);
}

void	copy_color(int *original, int *copy)
{
	copy[0] = original[0];
	copy[1] = original[1];
	copy[2] = original[2];
}

void	apply_selection_color(void)
{
	int		i;
	double	new_color[3];

	new_color[0] = g_scene.selected->color[0] + 85 * \
		(1 + ((255 - g_scene.selected->color[0]) / 255));
	new_color[1] = g_scene.selected->color[1] + 85 * \
		(1 + ((255 - g_scene.selected->color[1]) / 255));
	new_color[2] = g_scene.selected->color[2] + 85 * \
		(1 + ((255 - g_scene.selected->color[2]) / 255));
	if (new_color[0] > 255)
		new_color[0] = 255;
	if (new_color[1] > 255)
		new_color[1] = 255;
	if (new_color[2] > 255)
		new_color[2] = 255;
	i = -1;
	while (++i < 3)
		g_scene.selected->color[i] = (int) new_color[i];
}
