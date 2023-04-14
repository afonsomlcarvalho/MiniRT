#include "../inc/minirt.h"

float	check_hit_plane(void *self, float p[3])
{
	t_plane	*plane;
	float	t;
	float	oq[3];
	float	D[3];

	plane = (t_plane *) self;
	vec(scene.camera.origin, p, D);
	vec(scene.camera.origin, plane->point, oq);
	if (dot(plane->normal, D) == 0)
		return (0.0);
	t = dot(plane->normal, oq) / dot(plane->normal, D);
	if (t < 1)
		return (0.0);
	return (t);
}

void	add_plane(int color, float *point, float *normal)
{
	t_shape		*new_shape;
	t_plane		*new_plane;

	new_shape = malloc(sizeof(t_shape));
	if (!new_shape)
		return ;	//TODO: Error Handling

	new_shape->type = PLANE;
	new_shape->color = color;
	new_shape->check_hit = check_hit_plane;
	new_shape->next = NULL;

	new_plane = (t_plane *)malloc(sizeof(t_plane));
	new_shape->shape = new_plane;
	if (!new_plane)
		return ;	//TODO: Error Handling

	new_plane->point[X] = point[X];
	new_plane->point[Y] = point[Y];
	new_plane->point[Z] = point[Z];
	new_plane->normal[X] = normal[X];
	new_plane->normal[Y] = normal[Y];
	new_plane->normal[Z] = normal[Z];
	add_back_shape(new_shape);
}

