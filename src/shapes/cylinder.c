#include "../../inc/minirt.h"

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

double	check_hit_cylinder(void *self, double p[3], double origin[3], int flag)
{
	double		quadratic[3];
	t_cylinder	*cylinder;
	double		v[3];
	double		d[3];
	double		t[3];

	cylinder = (t_cylinder *) self;
	vec(origin, p, v);
	vec(cylinder->center, origin, d);
	quadratic[0] = dot(v, v) * pow(vector_size(cylinder->axis), 2) - \
	pow(dot(v, cylinder->axis), 2);
	quadratic[1] = 2 * dot(d, v) * pow(vector_size(cylinder->axis), 2) \
	- 2 * dot(v, cylinder->axis) * dot(d, cylinder->axis);
	quadratic[2] = (dot(d, d) - pow(cylinder->radius, 2)) * \
	pow(vector_size(cylinder->axis), 2) - pow(dot(d, cylinder->axis), 2);
	t[0] = check_height(cylinder, solve_quadratic(quadratic[0], \
	quadratic[1], quadratic[2], flag), origin, v);
	t[1] = check_width(cylinder, check_hit_plane(cylinder->top_cap, \
	p, origin, flag * 2), origin, v);
	t[2] = check_width(cylinder, check_hit_plane(cylinder->under_cap, \
	p, origin, flag * 2), origin, v);
	return (find_t(t));
}

void	substitute_caps(t_cylinder *self)
{
	free(self->top_cap);
	free(self->under_cap);
	add_caps(self);
}

void	fill_cylinder(char **info, int *error, t_shape *shape, t_cylinder *cyli)
{
	shape->type = CYLINDER;
	if (get_color(info[5], shape->color))
		error += parsing_error("Invalid cylinder colour.\n");
	shape->check_hit = check_hit_cylinder;
	shape->spec = DEF_SPEC;
	shape->next = NULL;
	shape->get_normal = get_normal_cylinder;
	if (coords_interpreter(info[1], cyli->center))
		error += parsing_error("Invalid cylinder center.\n");
	if (coords_interpreter(info[3], &cyli->radius))
		error += parsing_error("Invalid cylinder radius.\n");
	if (coords_interpreter(info[2], cyli->axis) || \
	check_normalized_vector(cyli->axis))
		error += parsing_error("Invalid cylinder axis.\n");
	if (coords_interpreter(info[4], &cyli->height))
		error += parsing_error("Invalid cylinder height.\n");
	cyli->radius /= 2;
	add_caps(cyli);
}

int	add_cylinder(char **info)
{
	t_shape		*new_shape;
	t_cylinder	*new_cylinder;
	int			error;

	error = 0;
	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return 0;	//TODO: Error Handling
	new_cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (!new_cylinder)
		return 0;	//TODO: Error Handling
	new_shape->shape = new_cylinder;
	add_back_shape(new_shape);
	if (array_size(info) != 6)
		return (parsing_error("Invalid number of arguments for cylinder.\n"));
	fill_cylinder(info, &error, new_shape, new_cylinder);
	return (error);
}
