#include "../inc/minirt.h"

void	add_back_light(t_light *new_light)
{
	t_light	*tmp;

	if (!new_light)
		return ;
	if (!scene.lights)
	{
		scene.lights = new_light;
		return ;
	}
	tmp = scene.lights;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_light;
}

void	light_setup(char **info, int flag)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	coords_interpreter(info[1 + flag], &light->brightness);
	if (light->brightness < 0 || light->brightness > 1)
		parsing_error("Invalid brightness\n");
	rgb_to_color(info[2 + flag], &light->color);
	light->type = flag;
	light->next = NULL;
	if (flag)
		coords_interpreter(info[1], light->position);
	add_back_light(light);
}