#include "../inc/minirt.h"

void	add_back(t_object *to_add)
{
	t_object	*cur;

	if (!(all())->objects)
	{
		(all())->objects = to_add;
		return ;
	}
	cur = (all())->objects;
	while (cur->next)
		cur = cur->next;
	cur->next = to_add;
}

int	is_sphere(t_object *sphere, float x, float y, float z)
{
	return (pow(x - sphere->point[X], 2) + pow(y - sphere->point[Y], 2) + pow(z - sphere->point[Z], 2) <= pow(sphere->radius, 2));
}

int	is_plane(t_object *plane, float x, float y, float z)
{
	float	vector[3];

	vector[X] = x - plane->point[X];
	vector[Y] = y - plane->point[Y];
	vector[Z] = z - plane->point[Z];
	return (vector[X] * plane->vector[X] + vector[Y] * plane->vector[Y] + vector[Z] * plane->vector[Z] == 0);
}

void	add_sphere(float x, float y, float z, float radius, int color)
{
	t_object	*sphere;
	
	sphere = malloc(sizeof(t_object));
	sphere->color = color;
	sphere->point[X] = x;
	sphere->point[Y] = y;
	sphere->point[Z] = z;
	sphere->radius = radius;
	sphere->is_object = is_sphere;
	sphere->next = NULL;
	add_back(sphere);
}

void	add_plane(float x, float y, float z, float vector_x, float vector_y, float vector_z, int color)
{
	t_object	*plane;
	
	plane = malloc(sizeof(t_object));
	plane->color = color;
	plane->point[X] = x;
	plane->point[Y] = y;
	plane->point[Z] = z;
	plane->vector[X] = vector_x;
	plane->vector[Y] = vector_y;
	plane->vector[Z] = vector_z;
	plane->is_object = is_plane;
	plane->next = NULL;
	add_back(plane);
}
