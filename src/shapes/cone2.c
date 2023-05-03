#include "../../inc/minirt.h"

double	check_height_cone(t_cone *self, double t, double *origin, double *p)
{
	double	point[3];
	double	k;
	double	b[3];
	double	axis_point[3];

	find_point(t, origin, p, point);
	vec(point, self->vertix, b);
	k = (-dot(b, self->axis)) / dot(self->axis, self->axis);
	axis_point[X] = self->vertix[X] + k * self->axis[X];
	axis_point[Y] = self->vertix[Y] + k * self->axis[Y];
	axis_point[Z] = self->vertix[Z] + k * self->axis[Z];
	// printf("%f\n", b[2]);
	// printf("%f %d %d\n", t, distance(axis_point, self->vertix) <= self->height, k >= 0);
	return (t * (distance(axis_point, self->vertix) <= self->height && k >= 0));
}

double	check_width_cone(t_cone *self, double t, double *origin, double *dir)
{
	double	point[3];
	t_plane	*base;

	base = (t_plane *)self->base;
	point[X] = origin[X] + t * dir[X];
	point[Y] = origin[Y] + t * dir[Y];
	point[Z] = origin[Z] + t * dir[Z];
	return ((distance(base->point, point) <= self->radius) * t);
}

double	check_hit_cone(void *self, double p[3], double origin[3], int flag)
{
	double	quadratic[3];
	t_cone	*cone;
	double	ray_direction[3];
	double	v_to_o[3];
	double	t[3];

	cone = (t_cone *) self;
	vec(origin, p, ray_direction);
	vec(cone->vertix, origin, v_to_o);
	quadratic[0] = dot(ray_direction, ray_direction) - (pow(cone->radius, 2) \
	/ pow(cone->height, 2) + 1) * pow(dot(ray_direction, cone->axis), 2);
	quadratic[1] = 2 * (dot(ray_direction, v_to_o) - (pow(cone->radius, 2) / \
	pow(cone->height, 2) + 1) * dot(ray_direction, cone->axis) * \
	dot(v_to_o, cone->axis));
	quadratic[2] = dot(v_to_o, v_to_o) - (pow(cone->radius, 2) / \
	pow(cone->height, 2) + 1) * pow(dot(v_to_o, cone->axis), 2);
	t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - \
	4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - \
	4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[0] = check_height_cone(cone, t[0], origin, p);
	t[1] = check_height_cone(cone, t[1], origin, p);
	t[2] = check_width_cone(cone, check_hit_plane(cone->base, p, \
	origin, flag * 2), origin, ray_direction);
	return (find_t(t));
}
