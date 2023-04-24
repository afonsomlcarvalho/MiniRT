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
	double	angle[3];

	p[X] = x * (scene.viewport.width / WIDTH) + scene.camera.origin[X];
	p[Y] = -y * (scene.viewport.height / HEIGHT) + scene.camera.origin[Y];
	p[Z] = scene.viewport.distance + scene.camera.origin[Z];
	angle[0] = 0;
	angle[1] = 0;
	if (sqrt(pow(scene.camera.direction[Z], 2) + pow(scene.camera.direction[Y], 2)))
		angle[0] = acos(scene.camera.direction[Z] / sqrt(pow(scene.camera.direction[Z], 2) + pow(scene.camera.direction[Y], 2)));
	if (sqrt(pow(scene.camera.direction[Z], 2) + pow(scene.camera.direction[X], 2)))
		angle[1] = acos(scene.camera.direction[Z] / sqrt(pow(scene.camera.direction[Z], 2) + pow(scene.camera.direction[X], 2)));
	angle[2] = 0;
	rotate(p, angle); 
	if (x == 0 && y == 0)
		printf("%lf %lf\n%lf %lf %lf\n", to_deg(angle[0]), to_deg(angle[1]), p[X], p[Y], p[Z]);
}
