#include "../../inc/minirt.h"

static void	get_normal_sphere(void *self, double *colision, double *normal)
{
	double		vector[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(sphere->center, colision, vector);
	normalize_vector(vector, normal);
}

static double	check_hit_sphere(void *self, double p[3], double origin[3], int flag)
{
	double		a;
	double		b;
	double		c;
	double		D[3];
	double		co[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(origin, p, D);
	a = dot(D, D);
	vec(sphere->center, origin, co);
	b = 2 * dot(co, D);
	c = dot(co, co) - pow(sphere->radius, 2);

	return (solve_quadratic(a, b, c, flag));
}

int	add_sphere(char **info)
{
	t_shape		*new_shape;
	t_sphere	*new_sphere;
	int			error;

	error = 0;
	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return 0;	//TODO: Error Handling

	new_sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!new_sphere)
		return 0;	//TODO: Error Handling

	new_shape->shape = new_sphere;
	add_back_shape(new_shape);
	if (array_size(info) != 4)
		return (parsing_error("Invalid number of arguments for sphere.\n"));
	new_shape->type = SPHERE;
	if (get_color(info[3], new_shape->color))
		error += parsing_error("Invalid sphere colors.\n");
	new_shape->check_hit = check_hit_sphere;
	new_shape->get_normal = get_normal_sphere;
	new_shape->spec = DEF_SPEC;
	new_shape->reflection = 0.3;
	new_shape->next = NULL;

	if (coords_interpreter(info[1], new_sphere->center))
		error += parsing_error("Invalid sphere center coords.\n");
	if (coords_interpreter(info[2], &new_sphere->radius))
		error += parsing_error("Invalid sphere radius.\n");
	else
		new_sphere->radius /= 2;
	return (error);
}
