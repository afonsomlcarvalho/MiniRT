#include "../../inc/minirt.h"

void	setup_scene(void)
{
	g_scene.mlx = mlx_init();
	g_scene.win = mlx_new_window(g_scene.mlx, WIDTH, HEIGHT, "test");
	g_scene.img.img_ptr = mlx_new_image(g_scene.mlx, WIDTH, HEIGHT);
	g_scene.img.address = mlx_get_data_addr(g_scene.img.img_ptr, &g_scene.img.bpp, &g_scene.img.line_length, &g_scene.img.endian);
	g_scene.selected = NULL;
	// g_scene.shapes = NULL;
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
	static int	c;

	if (c)
		return (parsing_error("More than one camera.\n"));
	if (array_size(info) != 4)
		return (parsing_error("Invalid number of arguments for camera.\n"));
	coords_interpreter(info[1], g_scene.camera.origin);
	coords_interpreter(info[2], g_scene.camera.direction);
	g_scene.camera.fov = ft_atoi(info[3]);
	c++;
	setup_viewport();
	return (check_camera());
}

/* Sets up the viewport taking into account the FOV */
void	setup_viewport(void)
{
	g_scene.viewport.distance = 1;
	g_scene.viewport.width = 2 * g_scene.viewport.distance * tan(to_rad(g_scene.camera.fov / 2));
	g_scene.viewport.height = g_scene.viewport.width * HEIGHT / WIDTH;
}

/* Maps point (X, Y) to the correponding point in viewport */
void	canvas_to_viewport(int x, int y, double *p)
{
	double			width_vector[3];
	double			height_vector[3];
	double			up[3];

	up[1] = 1;
	up[0] = 0;
	up[2] = 0;
	cross_product(up, g_scene.camera.direction, width_vector);
	if (!g_scene.camera.direction[X] && !g_scene.camera.direction[Z] && g_scene.camera.direction[Y])
	{
		width_vector[X] = 1;
		width_vector[Y] = 0;
		width_vector[Z] = 0;
	}
	cross_product(width_vector, g_scene.camera.direction, height_vector);
	p[X] = g_scene.camera.origin[X] + g_scene.camera.direction[X] + (((double)x / WIDTH) * (g_scene.viewport.width / vector_size(width_vector))) * width_vector[X] + (((double)-y / HEIGHT) * (g_scene.viewport.height / vector_size(height_vector))) * height_vector[X];
	p[Y] = g_scene.camera.origin[Y] + g_scene.camera.direction[Y] + (((double)x / WIDTH) * (g_scene.viewport.width / vector_size(width_vector))) * width_vector[Y] + (((double)-y / HEIGHT) * (g_scene.viewport.height / vector_size(height_vector))) * height_vector[Y];
	p[Z] = g_scene.camera.origin[Z] + g_scene.camera.direction[Z] + (((double)x / WIDTH) * (g_scene.viewport.width / vector_size(width_vector))) * width_vector[Z] + (((double)-y / HEIGHT) * (g_scene.viewport.height / vector_size(height_vector))) * height_vector[Z];
}
