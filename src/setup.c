#include "../inc/minirt.h"

void	setup_scene(void)
{
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "test");
	scene.img.img_ptr = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	scene.img.address = mlx_get_data_addr(scene.img.img_ptr, &scene.img.bpp, &scene.img.line_length, &scene.img.endian);
	scene.shapes = NULL;
}

void	setup_camera(void)
{
	scene.camera.origin[X] = 0;
	scene.camera.origin[Y] = 0;
	scene.camera.origin[Z] = 0;

	scene.camera.direcion[X] = 0;
	scene.camera.direcion[Y] = 0;
	scene.camera.direcion[Z] = 1;

	scene.camera.fov = 53;
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
	scene.viewport.width = 2 * scene.viewport.distance * tan(to_rad(scene.camera.fov) / 2);
	scene.viewport.height = scene.viewport.width * HEIGHT / WIDTH;
	//scene.viewport.width = 1;
	//scene.viewport.height = 1;
}

/* Maps point (X, Y) to the correponding point in viewport */
void	canvas_to_viewport(int x, int y, float *p)
{
	p[X] = x * (scene.viewport.width / WIDTH);
	p[Y] = y * (scene.viewport.height / HEIGHT);
	p[Z] = scene.viewport.distance;
}

