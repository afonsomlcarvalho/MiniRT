#include "../inc/minirt.h"

int	check_hit(t_shape *self, float p[3])
{
	return (pow(p[X] - self->center[X], 2) + pow(p[Y] - self->center[Y], 2) \
			+ pow(p[Z] - self->center[Z], 2) <= pow(self->radius, 2));
}

void	add_back_shape(t_shape *new)
{
	t_shape	*tmp;

	if (!new)
		return ;
	if (!scene.shapes)
	{
		scene.shapes = new;
		return ;
	}
	tmp = scene.shapes;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_sphere(int color, float *center, int radius)
{
	t_shape	*new_shape;

	new_shape = malloc(sizeof(t_shape));
	if (!new_shape)
		return ; //TODO: exit cleanly
	new_shape->type = SPHERE;
	new_shape->color = color;
	new_shape->center[X] = center[X];
	new_shape->center[Y] = center[Y];
	new_shape->center[Z] = center[Z];
	new_shape->radius = radius;
	new_shape->check_hit = check_hit;
	new_shape->next = NULL;
	add_back_shape(new_shape);
}

void	add_shape(int type, int color, float *center, int radius)
{
	if (type == SPHERE)
		add_sphere(color, center, radius);
}
