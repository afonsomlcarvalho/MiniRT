#include "../inc/minirt.h"

int	coords_interpreter(char *coords, float *point)
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

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int	rgb_to_color(float *rgb, float *light)
{
	int		i;
	int		color;

	i = 0;
	color = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		color += rgb[i] * light[i] * pow(16, 4 - 2 * i);
		i++;
	}
	return (color);
}
