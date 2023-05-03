#include "../../inc/minirt.h"

void	change_light(void)
{
	t_light	*cur;

	cur = g_scene.lights;
	while (g_scene.selected_light)
	{
		g_scene.selected_light = g_scene.selected_light->next;
		if (!g_scene.selected_light || g_scene.selected_light->type)
			break ;
	}
	if (!g_scene.selected_light)
	{
		while (cur && !g_scene.selected_light)
		{
			if (cur->type)
				g_scene.selected_light = cur;
			cur = cur->next;
		}
	}
	split_canva();
}

void	move_light(double *movement)
{
	g_scene.selected_light->position[X] += movement[X];
	g_scene.selected_light->position[Y] += movement[Y];
	g_scene.selected_light->position[Z] += movement[Z];
}
