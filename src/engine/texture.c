#include "../../inc/minirt.h"

static double	get_rand(void)
{
	double	positive;
	double	negative;
	double	total;

	positive = ((double)(rand() % 21)) / 21 * 1;
	negative = ((double)(rand() % 21)) / 21 * -1;
	total = positive + negative;
	return (total * RUGGED);
}

static void	get_color_weights(int *colors, double *buff)
{
	buff[0] = colors[0] / 255.0;
	buff[1] = colors[1] / 255.0;
	buff[2] = colors[2] / 255.0;
}

void	apply_texture(int *buff)
{
	int		original_color;
	int		new_color[3];
	double	texture;
	double	weights[3];

	texture = get_rand();
	original_color = *buff;
	new_color[0] = (original_color >> 16) & 255;
	new_color[1] = (original_color >> 8) & 255;
	new_color[2] = original_color & 255;
	get_color_weights(new_color, weights);
	new_color[0] += texture * weights[0];
	new_color[1] += texture * weights[1];
	new_color[2] += texture * weights[2];
	if (new_color[0] > 255)
		new_color[0] = 255;
	if (new_color[1] > 255)
		new_color[1] = 255;
	if (new_color[2] > 255)
		new_color[2] = 255;
	*buff = (new_color[0] << 16) + (new_color[1] << 8) + new_color[2];
}
