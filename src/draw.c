#include "../inc/minirt.h"

pthread_mutex_t	canva;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
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
			color = trace_ray(scene.camera.origin, p, REFLECTIONS);
			my_mlx_pixel_put(&scene.img, x + WIDTH/2, y + HEIGHT/2, color);
		}
	}
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img.img_ptr, 0, 0);
}

void	*draw_parcel(void *x)
{
	int		n;
	int		i;
	int		y;
	int		color;
	double	p[3];

	i = *((int *) x);
	free(x);
	y = -HEIGHT / 2;
	while (y < HEIGHT / 2)
	{
		n = 0;
		while (n < WIDTH / THREAD)
		{
			canvas_to_viewport(i + n, y, p);
			color = trace_ray(scene.camera.origin, p, REFLECTIONS);
			my_mlx_pixel_put(&scene.img, i + n + WIDTH/2, y + HEIGHT/2, color);
			n++;
		}
		y++;
	}
	return (NULL);
}

void	split_canva()
{
	pthread_t	parcel[THREAD];
	int			i;
	int			*x;

	i = 0;
	while (i < THREAD)
	{
		x = malloc(sizeof(int));
		*x = (WIDTH / THREAD) * i - (WIDTH / 2);
		pthread_create(&parcel[i++], NULL, draw_parcel, (void *) x);
	}
	i = 0;
	while (i < THREAD)
		pthread_join(parcel[i++], NULL);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img.img_ptr, 0, 0);
}
