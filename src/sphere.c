#include "../inc/minirt.h"

float	check_hit_sphere(void *self, float p[3])
{
	float		a;
	float		b;
	float		c;
	float		D[3];
	float		co[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(scene.camera.origin, p, D);
	a = dot(D, D);
	vec(sphere->center, scene.camera.origin, co);
	b = 2 * dot(co, D);
	c = dot(co, co) - pow(sphere->radius, 2);
	return (solve_quadratic(a, b, c));
}

void	add_sphere(int color, float *center, int radius)
{
	t_shape		*new_shape;
	t_sphere	*new_sphere;

	new_shape = malloc(sizeof(t_shape));
	if (!new_shape)
		return ;	//TODO: Error Handling

	new_shape->type = SPHERE;
	new_shape->color = color;
	new_shape->check_hit = check_hit_sphere;
	new_shape->next = NULL;

	new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	new_shape->shape = new_sphere;
	if (!new_sphere)
		return ;	//TODO: Error Handling

	new_sphere->center[X] = center[X];
	new_sphere->center[Y] = center[Y];
	new_sphere->center[Z] = center[Z];
	new_sphere->radius = radius;
	add_back_shape(new_shape);
}

