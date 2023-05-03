#include "../../inc/minirt.h"

static void	clear_shapes(void)
{
	t_shape	*temp;

	while (g_scene.shapes)
	{
		temp = g_scene.shapes->next;
		if (g_scene.shapes->type == CYLINDER)
		{
			free(((t_cylinder *)(g_scene.shapes->shape))->top_cap);
			free(((t_cylinder *)(g_scene.shapes->shape))->under_cap);
		}
		free(g_scene.shapes->shape);
		free(g_scene.shapes);
		g_scene.shapes = temp;
	}
	g_scene.shapes = NULL;
}

static void	clear_lights(void)
{
	t_light	*temp;

	while (g_scene.lights)
	{
		temp = g_scene.lights->next;
		free(g_scene.lights);
		g_scene.lights = temp;
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
		mlx_destroy_image(g_scene.mlx, g_scene.img.img_ptr);
		mlx_destroy_window(g_scene.mlx, g_scene.win);
		mlx_destroy_display(g_scene.mlx);
		free(g_scene.mlx);
	}
	exit(0);
}

int	end(void)
{
	printf("%s\n[Quitting...]\n%s", CYAN_TEXT, RESET_TEXT);
	free_all(1);
	return (0);
}
