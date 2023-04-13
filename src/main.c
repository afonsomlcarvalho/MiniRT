#include "../inc/minirt.h"

t_scene	scene;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

float	*to_point(int x, int y, int z)
{
	static float point[3];
	point[X] = x;
	point[Y] = y;
	point[Z] = z;
	return (point);
}

void	draw_canvas()
{
	float	p[3];
	int		color;

	for (int x = -WIDTH/2; x < WIDTH/2; x++)
	{
		for (int y = -HEIGHT/2; y < HEIGHT/2; y++)
		{
			canvas_to_viewport(x, y, p);
			color = trace_ray(p);
			my_mlx_pixel_put(&scene.img, x + WIDTH/2, y + HEIGHT/2, color);
		}
	}
}

int	main()
{
	setup_scene();
	setup_camera();
	setup_viewport();

	add_shape(SPHERE, 0x00ff0000, to_point(0, -1, -3), 1);
	add_shape(SPHERE, 0x000000ff, to_point(2, 0, 4), 1);
	add_shape(SPHERE, 0x0000ff00, to_point(-2, 0, 4), 1);

	draw_canvas();

	mlx_put_image_to_window(scene.mlx, scene.win, scene.img.img_ptr, 0, 0);
	mlx_loop(scene.mlx);
	return (0);
}
