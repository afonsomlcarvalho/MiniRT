#include "../../inc/minirt.h"

static double	check_height_cone(t_cone *self, double t, double *origin, double *p)
{
	double	point[3];
	double	k;
	double	b[3];
	double	axis_point[3];

	find_point(t, origin, p, point);
	vec(point, self->vertix, b);
	k = -(dot(b, self->axis)) / dot(self->axis, self->axis);
	axis_point[X] = self->vertix[X] + k * self->axis[X];
	axis_point[Y] = self->vertix[Y] + k * self->axis[Y];
	axis_point[Z] = self->vertix[Z] + k * self->axis[Z];
	vec(self->vertix, axis_point, axis_point);
	return (t * (vector_size(axis_point) <= self->height && k > 0));
}

double	check_width_cone(t_cone *self, double t, double *origin, double *ray_direction)
{
	double	point[3];
	t_plane	*base;

	base = (t_plane *)self->base;
	point[X] = origin[X] + t * ray_direction[X];
	point[Y] = origin[Y] + t * ray_direction[Y];
	point[Z] = origin[Z] + t * ray_direction[Z];
	return ((distance(base->point, point) <= self->radius) * t);
}

double	check_hit_cone(void *self, double p[3], double origin[3], int flag)
{
	double	quadratic[3];
	t_cone	*cone;
	double	ray_direction[3];
	double	v_to_o[3];
	double	t[2];

	cone = (t_cone *) self;
	vec(origin, p, ray_direction);
	vec(cone->vertix, origin, v_to_o);
	quadratic[0] = dot(ray_direction, ray_direction) - (pow(cone->radius, 2) / pow(cone->height, 2) + 1) * pow(dot(ray_direction, cone->axis), 2);
	quadratic[1] = 2 * (dot(ray_direction, v_to_o) - (pow(cone->radius, 2) / pow(cone->height, 2) + 1) * dot(ray_direction, cone->axis) * dot(v_to_o, cone->axis));
	quadratic[2] = dot(v_to_o, v_to_o) - (pow(cone->radius, 2) / pow(cone->height, 2) + 1) * pow(dot(v_to_o, cone->axis), 2);
	t[0] = check_height_cone(cone, solve_quadratic(quadratic[0], quadratic[1], quadratic[2], flag), origin, p);
	t[1] = check_width_cone(cone, check_hit_plane(cone->base, p, origin, flag * 2), origin, ray_direction);
	return (t[0] * (t[1] < 0.9999999) + t[1] * (t[0] < 0.9999999) + min(t[0], t[1]) * (t[0] > 0.9999999 && t[1] > 0.9999999));
}

void	get_normal_cone(void *self, double *colision, double *normal)
{
	t_cone	*cone;
	t_plane	*base;
	double	k;
	double	vector[3];
	double	axis_point[3];

	cone = (t_cone *) self;
	base = (t_plane *) cone->base;
	vec(colision, base->point, vector);
	if (!dot(vector, cone->axis))
	{
		vec(cone->vertix, base->point, normal);
		return ;
	}
	vec(colision, cone->vertix, vector);
	k = -dot(vector, vector) / dot(cone->axis, vector);
	axis_point[X] = cone->vertix[X] + k * cone->axis[X];
	axis_point[Y] = cone->vertix[Y] + k * cone->axis[Y];
	axis_point[Z] = cone->vertix[Z] + k * cone->axis[Z];
	vec(axis_point, colision, normal);
}

void	add_cone_base(t_cone *cone)
{
	t_plane	*plane;
	double	t;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->normal[X] = cone->axis[X];
	plane->normal[Y] = cone->axis[Y];
	plane->normal[Z] = cone->axis[Z];
	t = cone->height / vector_size(cone->axis);
	plane->point[X] = cone->vertix[X] + t * cone->axis[X];
	plane->point[Y] = cone->vertix[Y] + t * cone->axis[Y];
	plane->point[Z] = cone->vertix[Z] + t * cone->axis[Z];
	cone->base = (void *) plane;
}

int	add_cone(char **info)
{
	t_shape	*new_shape;
	t_cone	*new_cone;
	int		error;

	error = 0;
	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return 0;	//TODO: Error Handling
	new_cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!new_cone)
		return 0;	//TODO: Error Handling

	new_shape->shape = new_cone;
	add_back_shape(new_shape);
	if (array_size(info) != 6)
		return (parsing_error("Invalid number of arguments for cone.\n"));
	new_shape->type = CONE;
	if (get_color(info[5], new_shape->color))
		error += parsing_error("Invalid cone colour.\n");
	new_shape->check_hit = check_hit_cone;
	new_shape->spec = DEF_SPEC;
	new_shape->next = NULL;
	new_shape->get_normal = get_normal_cone;
	if (coords_interpreter(info[1], new_cone->vertix))
		error += parsing_error("Invalid cone vertix.\n");
	if (coords_interpreter(info[3], &new_cone->angle))
		error += parsing_error("Invalid cone angle.\n");
	if (coords_interpreter(info[2], new_cone->axis) || check_normalized_vector(new_cone->axis))
		error += parsing_error("Invalid cone axis.\n");
	normalize_vector(new_cone->axis, new_cone->axis);
	if (coords_interpreter(info[4], &new_cone->height))
		error += parsing_error("Invalid cone height.\n");
	if (!error)
		new_cone->radius = tan(to_rad(new_cone->angle / 2)) * new_cone->height;
	add_cone_base(new_cone);
	return (error);
}
