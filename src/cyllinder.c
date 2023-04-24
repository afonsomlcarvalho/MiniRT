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

double	check_width(t_cyllinder *self, double t, double *origin, double *vector)
{
	double	point[3];
	double	v[3];
	t_plane	*top;
	t_plane	*down;

	top = (t_plane *)self->top_cap;
	down = (t_plane *)self->under_cap;
	point[X] = origin[X] + t * vector[X];
	point[Y] = origin[Y] + t * vector[Y];
	point[Z] = origin[Z] + t * vector[Z];
	v[X] = top->point[X] - point[X];
	v[Y] = top->point[Y] - point[Y];
	v[Z] = top->point[Z] - point[Z];
	if (dot(v, self->axis) > 0.0000001 || dot(v, self->axis) < -0.0000001)
	{
		v[X] = down->point[X] - point[X];
		v[Y] = down->point[Y] - point[Y];
		v[Z] = down->point[Z] - point[Z];
	}
	return (t * (vector_size(v) <= self->radius));
}

double	find_t(double *t)
{
	if (t[0] <= 0)
	{
		if (t[1] <= 0 || t[2] <= 0)
			return (t[(t[2] > 0) + 1]);
		return (min(t[1], t[2]));
	}
	if (t[1] <= 0)
	{
		if (t[0] <= 0 || t[2] <= 0)
			return (t[(t[2] > 0) * 2]);
		return (min(t[0], t[2]));
	}
	if (t[2] <= 0)
	{
		if (t[1] <= 0 || t[0] <= 0)
			return (t[(t[1] > 0)]);
		return (min(t[1], t[0]));
	}
	return (min(min(t[1], t[0]), t[2]));
}

double	check_hit_cyllinder(void *self, double p[3], double origin[3], int flag)
{
	double		a;
	double		b;
	double		c;
	t_cyllinder	*cyllinder;
	double		v[3];
	double		d[3];
	double		t[3];

	cyllinder = (t_cyllinder *) self;
	vec(origin, p, v);
	vec(cyllinder->center, origin, d);
	a = dot(v, v) * pow(vector_size(cyllinder->axis), 2) - pow(dot(v, cyllinder->axis), 2);
	b = 2 * dot(d, v) * pow(vector_size(cyllinder->axis), 2) - 2 * dot(v, cyllinder->axis) * dot(d, cyllinder->axis);
	c = (dot(d, d) - pow(cyllinder->radius, 2)) * pow(vector_size(cyllinder->axis), 2) - pow(dot(d, cyllinder->axis), 2);
	t[0] = check_height(cyllinder, solve_quadratic(a, b, c, flag), origin, v);
	t[1] = check_width(cyllinder, check_hit_plane(cyllinder->top_cap, p, origin, flag), origin, v);
	t[2] = check_width(cyllinder, check_hit_plane(cyllinder->under_cap, p, origin, flag), origin, v);
	return (find_t(t));
}

void	add_caps(t_cyllinder *self)
{
	int		i;
	double	t[2];
	double	quadratic[3];
	t_plane	*top_cap;
	t_plane	*down_cap;

	top_cap = (t_plane *)ft_calloc(1, sizeof(t_plane));
	down_cap = (t_plane *)ft_calloc(1, sizeof(t_plane));
	i = -1;
	while (++i < 3)
	{
		top_cap->normal[i] = self->axis[i];
		down_cap->normal[i] = self->axis[i];
	}
	quadratic[0] = dot(self->axis, self->axis);
	quadratic[1] = 0;
	quadratic[2] =  -(pow(self->height, 2) / 4);
	t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	i = -1;
	while (++i < 3)
	{
		down_cap->point[i] = self->center[i] + t[0] * self->axis[i];
		top_cap->point[i] = self->center[i] + t[1] * self->axis[i];
	}
	self->top_cap = top_cap;
	self->under_cap = down_cap;
}

void	substitute_caps(t_cyllinder *self)
{
	free(self->top_cap);
	free(self->under_cap);
	add_caps(self);
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
	add_caps(new_cyllinder);
	new_shape->shape = new_cyllinder;
	add_back_shape(new_shape);
}
