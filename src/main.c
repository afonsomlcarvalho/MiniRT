#include "../inc/minirt.h"

t_scene	scene;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

double	*to_point(int x, int y, int z)
{
	static double point[3];
	point[X] = x;
	point[Y] = y;
	point[Z] = z;
	return (point);
}

void	draw_canvas()
{
	double	p[3];
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
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img.img_ptr, 0, 0);
}

void	apply_translation_and_rotation(t_shape *selected, double *vector, double *angle)
{
	if (selected->type == SPHERE)
		translate(((t_sphere *)(selected->shape))->center, vector);
	else if (selected->type == CYLLINDER)
	{
		translate(((t_cyllinder *)(selected->shape))->center, vector);
		translate(((t_plane *)(((t_cyllinder *)(selected->shape))->top_cap))->point, vector);
		translate(((t_plane *)(((t_cyllinder *)(selected->shape))->under_cap))->point, vector);
		rotate(((t_cyllinder *)(selected->shape))->axis, angle);
		substitute_caps((t_cyllinder *)(selected->shape));
	}
	else if (selected->type == PLANE)
	{
		translate(((t_plane *)(selected->shape))->point, vector);
		rotate(((t_plane *)(selected->shape))->normal, angle);
	}
	draw_canvas();
}

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];

	if (keycode == 65307)
		end();
	if (!scene.selected)
		return (0);
	vector[X] = ((keycode == 100) - (keycode == 97)) * 0.1;
	vector[Y] = ((keycode == 119) - (keycode == 115)) * 0.1;
	vector[Z] = ((keycode == 101) - (keycode == 113)) * 0.1;
	angle[X] = to_rad(((keycode == 108) - (keycode == 106)) * 15);
	angle[Y] = to_rad(((keycode == 105) - (keycode == 107)) * 15);
	angle[Z] = to_rad(((keycode == 111) - (keycode == 117)) * 15);
	apply_translation_and_rotation(scene.selected, vector, angle);
	return (0);
}

int	select_piece(int button, int x, int y)
{
	double	t;
	t_shape			*cur;
	double			point[3];

	if (button != 1)
		return (0);
	cur = scene.shapes;
	t = 0;
	canvas_to_viewport(x - WIDTH / 2, y - HEIGHT / 2, point);
	if (scene.selected)
		scene.selected = 0;
	else
	{
		while (cur && !scene.selected)
		{
			if (cur->check_hit(cur->shape, point, scene.camera.origin, 0) && (t == 0 || cur->check_hit(cur->shape, point, scene.camera.origin, 0) < t))
			{
				scene.selected = cur;
				t = cur->check_hit(cur->shape, point, scene.camera.origin, 0);
			}
			cur = cur->next;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	parser(argc, argv);
	setup_scene();

	draw_canvas();

	mlx_hook(scene.win, 2, 1L<<0, key_press, NULL);
	mlx_hook(scene.win, 17, 0, end, NULL);
	mlx_hook(scene.win, 4, (1L<<2), select_piece, NULL);
	mlx_loop(scene.mlx);
	return (0);
}
