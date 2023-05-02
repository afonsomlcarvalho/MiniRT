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
	double		a;
	double		b;
	double		c;
	t_cylinder	*cylinder;
	double		v[3];
	double		d[3];
	double		t[3];

	cylinder = (t_cylinder *) self;
	vec(origin, p, v);
	vec(cylinder->center, origin, d);
	a = dot(v, v) * pow(vector_size(cylinder->axis), 2) - pow(dot(v, cylinder->axis), 2);
	b = 2 * dot(d, v) * pow(vector_size(cylinder->axis), 2) - 2 * dot(v, cylinder->axis) * dot(d, cylinder->axis);
	c = (dot(d, d) - pow(cylinder->radius, 2)) * pow(vector_size(cylinder->axis), 2) - pow(dot(d, cylinder->axis), 2);
	t[0] = check_height(cylinder, solve_quadratic(a, b, c, flag), origin, v);
	t[1] = check_width(cylinder, check_hit_plane(cylinder->top_cap, p, origin, flag * 2), origin, v);
	t[2] = check_width(cylinder, check_hit_plane(cylinder->under_cap, p, origin, flag * 2), origin, v);
	return (find_t(t));
}

void	add_caps(t_cylinder *self)
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

void	substitute_caps(t_cylinder *self)
{
	free(self->top_cap);
	free(self->under_cap);
	add_caps(self);
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
	new_shape->type = CYLINDER;
	if (get_color(info[5], new_shape->color))
		error += parsing_error("Invalid cylinder colour.\n");
	new_shape->check_hit = check_hit_cylinder;
	new_shape->spec = DEF_SPEC;
	new_shape->next = NULL;
	new_shape->get_normal = get_normal_cylinder;
	if (coords_interpreter(info[1], new_cylinder->center))
		error += parsing_error("Invalid cylinder center.\n");
	if (coords_interpreter(info[3], &new_cylinder->radius))
		error += parsing_error("Invalid cylinder radius.\n");
	if (coords_interpreter(info[2], new_cylinder->axis) || check_normalized_vector(new_cylinder->axis))
		error += parsing_error("Invalid cylinder axis.\n");
	if (coords_interpreter(info[4], &new_cylinder->height))
		error += parsing_error("Invalid cylinder height.\n");
	new_cylinder->radius /= 2;
	add_caps(new_cylinder);
	return (error);
}
