#include "../inc/minirt.h"

double	check_hit_cyllinder(void *self, double p[3], double origin[3], int flag)
{
	double		a;
	double		b;
	double		c;
	double		D[3];
	double		V[3];
	t_cyllinder	*cyllinder;

	cyllinder = (t_cyllinder *) self;
	vec(origin, p, D);
	vec(cyllinder->center, origin, V);
	a = dot(D, D) - pow(dot(D, cyllinder->axis), 2);
	b = 2 * (dot(D, V) - (dot(D, cyllinder->axis) * dot(V, cyllinder->axis)));
	c = dot(V, V) - pow(dot(V, cyllinder->axis), 2) - pow(cyllinder->radius, 2);

	return (solve_quadratic(a, b, c, flag));
}

void	add_cyllinder(char **info)
{
	t_shape		*new_shape;
	t_cyllinder	*new_cyllinder;

	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return ;	//TODO: Error Handling

	new_shape->type = CYLLINDER;
	coords_interpreter(info[5], new_shape->color);
	new_shape->check_hit = check_hit_cyllinder;
	new_shape->next = NULL;

	new_cyllinder = (t_cyllinder *)ft_calloc(1, sizeof(t_cyllinder));
	if (!new_cyllinder)
		return ;	//TODO: Error Handling

	coords_interpreter(info[1], new_cyllinder->center);
	coords_interpreter(info[3], &new_cyllinder->radius);
	coords_interpreter(info[2], new_cyllinder->axis);
	coords_interpreter(info[4], &new_cyllinder->height);
	new_cyllinder->radius /= 2;
	new_shape->shape = new_cyllinder;
	add_back_shape(new_shape);
}
