#include "../inc/minirt.h"

double	check_height(t_cyllinder *self, double t, double *origin, double *vector)
{
	double	point[3];
	double	k;
	double	p1[3];

	point[X] = origin[X] + t * vector[X];
	point[Y] = origin[Y] + t * vector[Y];
	point[Z] = origin[Z] + t * vector[Z];
	k = (dot(point, self->axis) - dot(self->center, self->axis)) / dot(self->axis, self->axis);
	p1[X] = self->center[X] + k * self->axis[X];
	p1[Y] = self->center[Y] + k * self->axis[Y];
	p1[Z] = self->center[Z] + k * self->axis[Z];
	if (distance(p1, self->center) > self->height / 2)
		return (0);
	return (t);
}

/* void	rotate(t_cyllinder *self, double *D, double *V)
{
	double angle;
	double orientation;
	double origin;

	orientation[X] = 0;
	orientation[Y] = 1;
	orientation[Z] = 0;
	origin[X] = 0;
	origin[Y] = 0;
	origin[Z] = 0;
	angle = acos(dot(self->axis, orientation) / (distance(origin, self->axis) * distance(origin, orientation)));
} */

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

	return (check_height(cyllinder, solve_quadratic(a, b, c, flag), origin, D));
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
