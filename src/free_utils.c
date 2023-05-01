#include "../inc/minirt.h"

void	clear_shapes()
{
	t_shape	*temp;

	while (scene.shapes)
	{
		temp = scene.shapes->next;
		if (scene.shapes->type == CYLLINDER)
		{
			free(((t_cyllinder *)(scene.shapes->shape))->top_cap);
			free(((t_cyllinder *)(scene.shapes->shape))->under_cap);
		}
		free(scene.shapes->shape);
		free(scene.shapes);
		scene.shapes = temp;
	}
	scene.shapes = NULL;
}

void	clear_lights()
{
	t_light	*temp;

	while (scene.lights)
	{
		temp = scene.lights->next;
		free(scene.lights);
		scene.lights = temp;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void	free_all(int flag)
{
	clear_shapes();
	clear_lights();
	if (flag)
	{
		mlx_destroy_image(scene.mlx, scene.img.img_ptr);
		mlx_destroy_window(scene.mlx, scene.win);
		mlx_destroy_display(scene.mlx);
		free(scene.mlx);
	}
	exit(0);
}

int	end()
{
	free_all(1);
	return (0);
}