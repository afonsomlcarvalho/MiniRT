#include "../inc/minirt.h"

int	coords_interpreter(char *coords, double *point)
{
	int	i;
	int	axis;
	int	sign;
	int	decimal;

	i = 0;
	axis = 0;
	while (coords[i])
	{
		decimal = 1;
		sign = coords[i] == '-';
		if (sign)
			i++;
		while (coords[i] && coords[i] != '.' && coords[i] != ',')
		{
			if (!ft_isdigit(coords[i]))
				return (0);
			point[axis] = point[axis] * 10 + (coords[i++] - '0');
		}
		if (coords[i] == '.' && i++)
		{
			while (coords[i] && coords[i] != ',')
			{
				if (!ft_isdigit(coords[i]))
					return (0);
				point[axis] += (coords[i++] - '0') / pow(10, decimal++);
			}
		}
		point[axis++] *= (sign == 0) - (sign != 0);
		i += coords[i] == ',';
	}
	return (1);
}

void	get_color(char *coords, int *colors)
{
	int		red;
	int		green;
	int		blue;
	char	**arr;

	arr = ft_split(coords, ',');
	if (!arr)
		return ;	// TODO: ERROR HANDLING
	red = ft_atoi(arr[0]);
	green = ft_atoi(arr[1]);
	blue = ft_atoi(arr[2]);
	if (red < 0 || red > 255 ||
		green < 0 || green > 255 ||
		blue < 0 || blue > 255)
		return ;	// TODO: ERROR HANDLING
	colors[0] = red;
	colors[1] = green;
	colors[2] = blue;
	free_array(arr);
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
