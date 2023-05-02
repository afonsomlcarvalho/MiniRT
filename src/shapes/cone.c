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

static double	check_hit_cone(void *self, double p[3], double origin[3], int flag)
{
	double	quadratic[3];
	t_cone	*cone;
	double	ray_direction[3];
	double	vector[3];
	double	t;

	cone = (t_cone *) self;
	vec(origin, p, ray_direction);
	vec(cone->vertix, origin, vector);
	quadratic[0] = pow(dot(ray_direction, cone->axis), 2) - pow(cos(to_rad(cone->angle / 2)), 2);
	quadratic[1] = 2 * (dot(ray_direction, cone->axis) * dot(vector, cone->axis) - dot(ray_direction, vector) * pow(cos(to_rad(cone->angle / 2)), 2));
	quadratic[2] = pow(dot(vector, cone->axis), 2) - dot(vector, vector) * pow(cos(to_rad(cone->angle / 2)), 2);
	t = check_height_cone(cone, solve_quadratic(quadratic[0], quadratic[1], quadratic[2], flag), origin, p);
	return (t);
}

static void	get_normal_cone(void *self, double *colision, double *normal)
{
	(void) self;
	(void) normal;
	(void) colision;
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
	if (coords_interpreter(info[4], &new_cone->height))
		error += parsing_error("Invalid cone height.\n");
	return (error);
}
