/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:58 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/05 10:57:42 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	setup_scene(void)
{
	t_light	*cur;

	g_scene.mlx = mlx_init();
	g_scene.win = mlx_new_window(g_scene.mlx, WIDTH, HEIGHT, "test");
	g_scene.img.img_ptr = mlx_new_image(g_scene.mlx, WIDTH, HEIGHT);
	g_scene.img.address = mlx_get_data_addr(g_scene.img.img_ptr, \
	&g_scene.img.bpp, &g_scene.img.line_length, &g_scene.img.endian);
	g_scene.selected = NULL;
	g_scene.texture = RUGGED;
	g_scene.reflection = REFLECTIONS;
	g_scene.selected_light = NULL;
	cur = g_scene.lights;
	while (cur && !g_scene.selected_light)
	{
		if (cur->type)
			g_scene.selected_light = cur;
		cur = cur->next;
	}
}

static int	check_camera(void)
{
	int	error;

	error = 0;
	if (g_scene.camera.fov < 0 || g_scene.camera.fov > 180)
		error += parsing_error("Invalid camera FOV.\n");
	if (check_normalized_vector(g_scene.camera.direction))
		error += parsing_error("Invalid camera direction.\n");
	return (error);
}

int	setup_camera(char **info)
{
	if (g_scene.cam_counter)
		return (parsing_error("More than one camera.\n"));
	if (array_size(info) != 4)
		return (parsing_error("Invalid number of arguments for camera.\n"));
	coords_interpreter(info[1], g_scene.camera.origin);
	coords_interpreter(info[2], g_scene.camera.direction);
	g_scene.camera.fov = ft_atoi(info[3]);
	g_scene.cam_counter++;
	setup_viewport();
	return (check_camera());
}

/* Sets up the viewport taking into account the FOV */
void	setup_viewport(void)
{
	g_scene.viewport.distance = 1;
	g_scene.viewport.width = 2 * g_scene.viewport.distance * \
	tan(to_rad(g_scene.camera.fov / 2));
	g_scene.viewport.height = g_scene.viewport.width * HEIGHT / WIDTH;
}

/* Maps point (X, Y) to the correponding point in viewport */
void	canvas_to_viewport(int x, int y, double *p)
{
	double			w_vector[3];
	double			h_vector[3];

	set_vectors(w_vector, h_vector);
	p[X] = g_scene.camera.origin[X] + g_scene.camera.direction[X] + \
	(((double)x / WIDTH) * (g_scene.viewport.width / \
	vector_size(w_vector))) * w_vector[X] + (((double)y / HEIGHT) \
	* (g_scene.viewport.height / vector_size(h_vector))) * h_vector[X];
	p[Y] = g_scene.camera.origin[Y] + g_scene.camera.direction[Y] + \
	(((double)x / WIDTH) * (g_scene.viewport.width / \
	vector_size(w_vector))) * w_vector[Y] + (((double)y / HEIGHT) \
	* (g_scene.viewport.height / vector_size(h_vector))) * h_vector[Y];
	p[Z] = g_scene.camera.origin[Z] + g_scene.camera.direction[Z] + \
	(((double)x / WIDTH) * (g_scene.viewport.width / \
	vector_size(w_vector))) * w_vector[Z] + (((double)y / HEIGHT) \
	* (g_scene.viewport.height / vector_size(h_vector))) * h_vector[Z];
}
