#include "../../inc/minirt.h"

static void	get_normal_sphere(void *self, double *colision, double *normal)
{
	double		vector[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(sphere->center, colision, vector);
	normalize_vector(vector, normal);
}

double	check_hit_sphere(void *self, double p[3], double origin[3], int flag)
{
	double		quadratic[3];
	double		d[3];
	double		co[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(origin, p, d);
	quadratic[0] = dot(d, d);
	vec(sphere->center, origin, co);
	quadratic[1] = 2 * dot(co, d);
	quadratic[2] = dot(co, co) - pow(sphere->radius, 2);
	return (solve_quadratic(quadratic[0], quadratic[1], quadratic[2], flag));
}

void	fill_sphere(char **info, int *error, t_shape *shape, t_sphere *sphere)
{
	shape->type = SPHERE;
	if (get_color(info[3], shape->color))
		error += parsing_error("Invalid sphere colors.\n");
	shape->check_hit = check_hit_sphere;
	shape->get_normal = get_normal_sphere;
	shape->spec = DEF_SPEC;
	shape->reflection = 0.3;
	shape->next = NULL;
	if (coords_interpreter(info[1], sphere->center))
		error += parsing_error("Invalid sphere center coords.\n");
	if (coords_interpreter(info[2], &sphere->radius))
		error += parsing_error("Invalid sphere radius.\n");
	else
		sphere->radius /= 2;
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
	fill_sphere(info, &error, new_shape, new_sphere);
	return (error);
}
