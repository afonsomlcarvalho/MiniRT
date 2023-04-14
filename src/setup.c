#include "../inc/minirt.h"

void	setup_scene(void)
{
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "test");
	scene.img.img_ptr = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	scene.img.address = mlx_get_data_addr(scene.img.img_ptr, &scene.img.bpp, &scene.img.line_length, &scene.img.endian);
	// scene.shapes = NULL;
}

void	setup_camera(char **info)
{
	static int	c;
	int			i;

	if (c)
		parsing_error("More than one camera.\n");
	coords_interpreter(info[1], scene.camera.origin);
	coords_interpreter(info[2], scene.camera.direction);
	scene.camera.fov = ft_atoi(info[3]);
	i = 0;
	while (i < 3)
	{
		if (scene.camera.direction[i] > 1 || scene.camera.direction[i] < -1)
			parsing_error("Invalid camera direction.\n");
		i++;
	}
	if (scene.camera.fov > 180 || scene.camera.fov < 0)
		parsing_error("Invalid FOV.\n");
	c++;
	setup_viewport();
}

/* Converts degrees to radians */
float	to_rad(int deg)
{
	return (deg * M_PI / 180);
}

/* Sets up the viewport taking into account the FOV */
void	setup_viewport(void)
{
	scene.viewport.distance = 1;
	scene.viewport.width = 2 * scene.viewport.distance * tan(to_rad(scene.camera.fov / 2));
	scene.viewport.height = scene.viewport.width * HEIGHT / WIDTH;
	//scene.viewport.width = 1;
	//scene.viewport.height = 1;
}

/* Maps point (X, Y) to the correponding point in viewport */
void	canvas_to_viewport(int x, int y, float *p)
{
	p[X] = x * (scene.viewport.width / WIDTH) + scene.camera.origin[X];
	p[Y] = -y * (scene.viewport.height / HEIGHT) + scene.camera.origin[Y];
	p[Z] = scene.viewport.distance + scene.camera.origin[Z];
}
