/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:23 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 14:54:45 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	get_normal_sphere(void *self, double *colision, double *normal, int cam_in)
{
	double		vector[3];
	t_sphere	*sphere;

	sphere = (t_sphere *) self;
	vec(sphere->center, colision, vector);
	normalize_vector(vector, normal);
	if (cam_in)
		mult_vecs(-1, normal, normal);
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
		*error += parsing_error("Invalid sphere colors.\n");
	copy_color(shape->color, shape->backup_color);
	shape->check_hit = check_hit_sphere;
	shape->get_normal = get_normal_sphere;
	shape->spec = DEF_SPEC;
	if (coords_interpreter(info[4], &shape->reflection) \
		|| shape->reflection < 0 || shape->reflection > 0.5)
		*error += parsing_error("Invalid sphere reflection.\n");
	if (coords_interpreter(info[1], sphere->center))
		*error += parsing_error("Invalid sphere center coords.\n");
	shape->next = NULL;
	if (coords_interpreter(info[2], &sphere->radius) || sphere->radius <= 0)
		*error += parsing_error("Invalid sphere radius.\n");
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
		error_handler();
	new_sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!new_sphere)
		error_handler();
	new_shape->shape = new_sphere;
	add_back_shape(new_shape);
	if (array_size(info) != 5)
		return (parsing_error("Invalid number of arguments for sphere.\n"));
	fill_sphere(info, &error, new_shape, new_sphere);
	new_shape->camera_in = 0;
	return (error);
}
