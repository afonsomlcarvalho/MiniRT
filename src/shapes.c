#include "../inc/minirt.h"

/* Adds shape of type TYPE to the shape list with the 
 * properties passed as arguments */
void	add_shape(int type, int color, float *center, int radius)
{
	if (type == SPHERE)
		add_sphere(color, center, radius);
}

/* Adds NEW_SHAPE to the end of the shapes list */
void	add_back_shape(t_shape *new_shape)
{
	t_shape	*tmp;

	if (!new_shape)
		return ;
	if (!scene.shapes)
	{
		scene.shapes = new_shape;
		return ;
	}
	tmp = scene.shapes;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_shape;
}

