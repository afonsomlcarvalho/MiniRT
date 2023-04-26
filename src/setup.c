#include "../inc/minirt.h"

void	setup_scene(void)
{
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "test");
	scene.img.img_ptr = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	scene.img.address = mlx_get_data_addr(scene.img.img_ptr, &scene.img.bpp, &scene.img.line_length, &scene.img.endian);
	scene.selected = NULL;
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
double	to_rad(int deg)
{
	return (deg * M_PI / 180);
}

double	to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

/* Sets up the viewport taking into account the FOV */
void	setup_viewport(void)
{
	scene.viewport.distance = 1;
	scene.viewport.width = 2 * scene.viewport.distance * tan(to_rad(scene.camera.fov / 2));
	scene.viewport.height = scene.viewport.width * HEIGHT / WIDTH;
}

/* Maps point (X, Y) to the correponding point in viewport */
void	canvas_to_viewport(int x, int y, double *p)
{
	double			width_vector[3];
	double			height_vector[3];
	static double	up[3];

	up[1] = 1;
	cross_product(up, scene.camera.direction, width_vector);
	if (!scene.camera.direction[X] && !scene.camera.direction[Z] && scene.camera.direction[Y])
	{
		width_vector[X] = 1;
		width_vector[Y] = 0;
		width_vector[Z] = 0;
	}
	cross_product(width_vector, scene.camera.direction, height_vector);
	p[X] = scene.camera.origin[X] + scene.camera.direction[X] + (((double)x / WIDTH) * (scene.viewport.width / vector_size(width_vector))) * width_vector[X] + (((double)-y / HEIGHT) * (scene.viewport.height / vector_size(height_vector))) * height_vector[X];
	p[Y] = scene.camera.origin[Y] + scene.camera.direction[Y] + (((double)x / WIDTH) * (scene.viewport.width / vector_size(width_vector))) * width_vector[Y] + (((double)-y / HEIGHT) * (scene.viewport.height / vector_size(height_vector))) * height_vector[Y];
	p[Z] = scene.camera.origin[Z] + scene.camera.direction[Z] + (((double)x / WIDTH) * (scene.viewport.width / vector_size(width_vector))) * width_vector[Z] + (((double)-y / HEIGHT) * (scene.viewport.height / vector_size(height_vector))) * height_vector[Z];
	// if (x == 0 && y == 0)
		// printf("Origin: %f %f %f\nDirection: %f %f %f\nPoint: %f %f %f\nWidth: %f %f %f\nHeight: %f %f %f\n    \n", scene.camera.origin[X],scene.camera.origin[Y],scene.camera.origin[Z],scene.camera.direction[X],scene.camera.direction[Y],scene.camera.direction[Z],p[X],p[Y],p[Z], width_vector[X], width_vector[Y], width_vector[Z], height_vector[X], height_vector[Y], height_vector[Z]);
}
