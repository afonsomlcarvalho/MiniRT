#include "../../inc/minirt.h"

/* Adds NEW_SHAPE to the end of the shapes list */
void	add_back_shape(t_shape *new_shape)
{
	t_shape	*tmp;

	if (!new_shape)
		return ;
	if (!g_scene.shapes)
	{
		g_scene.shapes = new_shape;
		return ;
	}
	tmp = g_scene.shapes;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_shape;
}
