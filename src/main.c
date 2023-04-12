#include "../inc/minirt.h"

t_all	*all(void)
{
	static t_all all;

	return (&all);
}

void	cam_setup()
{
	(all())->cam.position[X] = 0;
	(all())->cam.position[Y] = 0;
	(all())->cam.position[Z] = 0;
	(all())->cam.direction[X] = 0;
	(all())->cam.direction[Y] = 0;
	(all())->cam.direction[Z] = 1;
	(all())->cam.FOV = 53;
}

void	viewport_setup()
{
	(all())->viewport.width = 2 * tan(((all())->cam.FOV * M_PI / 180) / 2);
	(all())->viewport.height = (all())->viewport.width * HEIGHT / WIDTH;
}

float	canva_to_vp(int x, int y, int flag)
{
	float	coords[3];

	coords[X] = x * ((all())->viewport.width / WIDTH);
	coords[Y] = y * ((all())->viewport.height / HEIGHT);
	coords[Z] = 1; 

	return (coords[flag]);
}

int	get_ray_color(int x, int y)
{
	float	vector[3];
	float	point[3];
	int	t;
	t_object	*cur;

	vector[X] = canva_to_vp(x, y, X) - (all())->cam.position[X];
	vector[Y] = canva_to_vp(x, y, Y) - (all())->cam.position[Y];
	vector[Z] = canva_to_vp(x, y, Z) - (all())->cam.position[Z];
	t = 1;
	while (t < 1000)
	{
		point[X] = (all())->cam.position[X] + t * (vector[X] - (all())->cam.position[X]);
		point[Y] = (all())->cam.position[Y] + t * (vector[Y] - (all())->cam.position[Y]);
		point[Z] = (all())->cam.position[Z] + t * (vector[Z] - (all())->cam.position[Z]);
		cur = (all())->objects;
		while (cur)
		{
			if (cur->is_object(cur, point[X], point[Y], point[Z]))
				return (cur->color);
			cur = cur->next;
		}
		t++;
	}
	return (0xffffffff);
}

void	draw_canva()
{
	int	x;
	int	y;

	y = -(HEIGHT / 2);
	while (y < HEIGHT / 2)
	{
		x = -(WIDTH / 2);
		while (x < WIDTH / 2)
		{
			my_mlx_pixel_put(&(all())->canva, x + WIDTH / 2, y + HEIGHT / 2, get_ray_color(x, -y));
			x++;
		}
		y++;
	}
}

int	main()
{
	(all())->mlx = mlx_init();
	(all())->wind = mlx_new_window((all())->mlx, WIDTH, HEIGHT, "MiniRT");
	(all())->canva.img = mlx_new_image((all())->mlx, WIDTH, HEIGHT);
	(all())->canva.addr = mlx_get_data_addr((all())->canva.img, &(all())->canva.bpp, &(all())->canva.ll, &(all())->canva.endian);
	cam_setup();
	viewport_setup();
	add_sphere(-2, 0, 3, 1, 0x0000ff00);
	add_sphere(0, 0, 10, 1, 0x00ff0000);
	add_sphere(2, 0, 3, 1, 0x000000ff);
	// add_plane(0, 0, 1, 1, 0, 1, 0x00ffff00);
	draw_canva();
	mlx_put_image_to_window((all())->mlx, (all())->wind, (all())->canva.img, 0, 0);
	mlx_loop((all())->mlx);
}
