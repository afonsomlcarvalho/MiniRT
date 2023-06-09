/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:00 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 15:57:32 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
	if (dot(vector, cone->axis) > -0.00000001 \
		&& dot(vector, cone->axis) < 0.00000001)
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
	if (!plane)
		error_handler();
	plane->normal[X] = cone->axis[X];
	plane->normal[Y] = cone->axis[Y];
	plane->normal[Z] = cone->axis[Z];
	t = cone->height / vector_size(cone->axis);
	plane->point[X] = cone->vertix[X] + t * cone->axis[X];
	plane->point[Y] = cone->vertix[Y] + t * cone->axis[Y];
	plane->point[Z] = cone->vertix[Z] + t * cone->axis[Z];
	cone->base = (void *) plane;
}

void	substitute_cone_base(t_cone *cone)
{
	free(cone->base);
	add_cone_base(cone);
}

void	fill_cone(char **info, int *error, t_shape *new_shape, t_cone *new_cone)
{
	new_shape->type = CONE;
	if (get_color(info[5], new_shape->color))
		*error += parsing_error("Invalid cone colour.\n");
	copy_color(new_shape->color, new_shape->backup_color);
	new_shape->check_hit = check_hit_cone;
	new_shape->spec = DEF_SPEC;
	new_shape->next = NULL;
	new_shape->get_normal = get_normal_cone;
	if (coords_interpreter(info[6], &new_shape->reflection) \
	|| new_shape->reflection < 0 || new_shape->reflection >= 0.5)
		*error += parsing_error("Invalid cone reflection.\n");
	if (coords_interpreter(info[1], new_cone->vertix))
		*error += parsing_error("Invalid cone vertix.\n");
	if (coords_interpreter(info[3], &new_cone->angle) || \
	new_cone->angle < 0 || new_cone->angle > 179)
		*error += parsing_error("Invalid cone angle.\n");
	if (coords_interpreter(info[2], new_cone->axis) || \
	check_normalized_vector(new_cone->axis))
		*error += parsing_error("Invalid cone axis.\n");
	normalize_vector(new_cone->axis, new_cone->axis);
	if (coords_interpreter(info[4], &new_cone->height) || new_cone->height <= 0)
		*error += parsing_error("Invalid cone height.\n");
	if (!*error)
		new_cone->radius = tan(to_rad(new_cone->angle / 2)) * new_cone->height;
	add_cone_base(new_cone);
}

int	add_cone(char **info)
{
	t_shape	*new_shape;
	t_cone	*new_cone;
	int		error;

	error = 0;
	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		error_handler();
	new_cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!new_cone)
		error_handler();
	new_shape->shape = new_cone;
	add_back_shape(new_shape);
	if (array_size(info) != 7)
		return (parsing_error("Invalid number of arguments for cone.\n"));
	fill_cone(info, &error, new_shape, new_cone);
	new_shape->is_inside = inside_cone;
	return (error);
}
