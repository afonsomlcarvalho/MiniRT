#include "../../inc/minirt.h"

int	get_color(char *coords, int *colors)
{
	int		red;
	int		green;
	int		blue;
	char	**arr;

	arr = ft_split(coords, ',');
	if (!arr)
		return (0);	// TODO: ERROR HANDLING
	red = ft_atoi(arr[0]);
	green = ft_atoi(arr[1]);
	blue = ft_atoi(arr[2]);
	free_array(arr);
	if (red < 0 || red > 255 || \
		green < 0 || green > 255 || \
		blue < 0 || blue > 255)
		return (1);
	colors[0] = red;
	colors[1] = green;
	colors[2] = blue;
	return (0);
}

int	rgb_to_color(int *rgb, double *light)
{
	int	red;
	int	green;
	int	blue;

	red = rgb[0] * light[0];
	green = rgb[1] * light[1];
	blue = rgb[2] * light[2];
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return ((red << 16) + (green << 8) + blue);
}

int	get_full_color(int local_color, int reflected_color, double r)
{
	int	local[3];
	int	reflected[3];
	int	full[3];

	local[0] = (local_color >> 16) & 255;
	local[1] = (local_color >> 8) & 255;
	local[2] = local_color & 255;
	reflected[0] = (reflected_color >> 16) & 255;
	reflected[1] = (reflected_color >> 8) & 255;
	reflected[2] = reflected_color & 255;
	full[0] = local[0] * (1 - r) + reflected[0] * r;
	full[1] = local[1] * (1 - r) + reflected[1] * r;
	full[2] = local[2] * (1 - r) + reflected[2] * r;
	if (full[0] > 255)
		full[0] = 255;
	if (full[1] > 255)
		full[1] = 255;
	if (full[2] > 255)
		full[2] = 255;
	return ((full[0] << 16) + (full[1] << 8) + full[2]);
}
