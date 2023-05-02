#include "../../inc/minirt.h"

int	check_plane(t_plane *plane, t_cylinder *self, double *point, double *normal)
{
	double	vector[3];

	vec(point, plane->point, vector);
	if (dot(vector, plane->normal) < 0.0000001 && \
	dot(vector, plane->normal) > -0.0000001)
	{
		vec(self->center, plane->point, vector);
		normalize_vector(vector, normal);
		return (1);
	}
	return (0);
}

void	side_normal(t_cylinder *self, double *point, double *normal)
{
	double	k;
	double	vector[3];
	double	axis_point[3];

	vec(point, self->center, vector);
	k = -dot(vector, self->axis) / dot(self->axis, self->axis);
	axis_point[X] = self->center[X] + k * self->axis[X];
	axis_point[Y] = self->center[Y] + k * self->axis[Y];
	axis_point[Z] = self->center[Z] + k * self->axis[Z];
	vec(axis_point, point, vector);
	normalize_vector(vector, normal);
}

void	get_normal_cylinder(void *self, double *colision, double *normal)
{
	t_cylinder	*cylinder;
	t_plane		*top;
	t_plane		*under;

	cylinder = (t_cylinder *) self;
	top = (t_plane *) cylinder->top_cap;
	under = (t_plane *) cylinder->under_cap;
	if (check_plane(top, cylinder, colision, normal) || \
	check_plane(under, cylinder, colision, normal))
		return ;
	side_normal(cylinder, colision, normal);
}

double	check_height(t_cylinder *self, double t, double *origin, double *vector)
{
	double	point[3];
	double	k;
	double	p1[3];

	point[X] = origin[X] + t * vector[X];
	point[Y] = origin[Y] + t * vector[Y];
	point[Z] = origin[Z] + t * vector[Z];
	k = (dot(point, self->axis) - \
	dot(self->center, self->axis)) / dot(self->axis, self->axis);
	p1[X] = self->center[X] + k * self->axis[X];
	p1[Y] = self->center[Y] + k * self->axis[Y];
	p1[Z] = self->center[Z] + k * self->axis[Z];
	if (distance(p1, self->center) > self->height / 2)
		return (0);
	return (t);
}

double	check_width(t_cylinder *self, double t, double *origin, double *vector)
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
