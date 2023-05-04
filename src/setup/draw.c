#include "../../inc/minirt.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

static void	*draw_parcel(void *x)
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
			color = trace_ray(g_scene.camera.origin, p, g_scene.reflection);
			apply_texture(&color);
			my_mlx_pixel_put(&g_scene.img, i + n + WIDTH / 2, \
			y + HEIGHT / 2, color);
			n++;
		}
		y++;
	}
	return (NULL);
}

void	split_canva(void)
{
	pthread_t	parcel[THREAD];
	int			i;
	int			*x;

	i = 0;
	while (i < THREAD)
	{
		x = malloc(sizeof(int));
		if (!x)
			error_handler();
		*x = (WIDTH / THREAD) * i - (WIDTH / 2);
		pthread_create(&parcel[i++], NULL, draw_parcel, (void *) x);
	}
	i = 0;
	while (i < THREAD)
		pthread_join(parcel[i++], NULL);
	mlx_put_image_to_window(g_scene.mlx, g_scene.win, \
	g_scene.img.img_ptr, 0, 0);
}
