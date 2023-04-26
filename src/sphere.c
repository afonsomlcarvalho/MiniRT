#include "../inc/minirt.h"

void	get_normal_sphere(void *self, double t, double *p, double *normal)
{
	double		point[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	find_point(t, p, point);
	normalize_vector(sphere->center, point, normal);
}

double	check_hit_sphere(void *self, double p[3], double origin[3], int flag)
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

void	add_sphere(char **info)
{
	t_shape		*new_shape;
	t_sphere	*new_sphere;

	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return ;	//TODO: Error Handling

	new_shape->type = SPHERE;
	get_color(info[3], new_shape->color);
	new_shape->check_hit = check_hit_sphere;
	new_shape->get_normal = get_normal_sphere;
	new_shape->spec = DEF_SPEC;
	new_shape->next = NULL;

	new_sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!new_sphere)
		return ;	//TODO: Error Handling

	coords_interpreter(info[1], new_sphere->center);
	coords_interpreter(info[2], &new_sphere->radius);
	new_sphere->radius /= 2;
	new_shape->shape = new_sphere;
	add_back_shape(new_shape);
}
