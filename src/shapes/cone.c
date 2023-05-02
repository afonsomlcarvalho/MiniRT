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
	new_shape->check_hit = check_hit_cone;
	new_shape->spec = DEF_SPEC;
	new_shape->next = NULL;
	new_shape->get_normal = get_normal_cone;
	if (coords_interpreter(info[1], new_cone->vertix))
		*error += parsing_error("Invalid cone vertix.\n");
	if (coords_interpreter(info[3], &new_cone->angle))
		*error += parsing_error("Invalid cone angle.\n");
	if (coords_interpreter(info[2], new_cone->axis) || \
	check_normalized_vector(new_cone->axis))
		*error += parsing_error("Invalid cone axis.\n");
	normalize_vector(new_cone->axis, new_cone->axis);
	if (coords_interpreter(info[4], &new_cone->height))
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
		return (0);	//TODO: Error Handling
	new_cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!new_cone)
		return (0);	//TODO: Error Handling
	new_shape->shape = new_cone;
	add_back_shape(new_shape);
	if (array_size(info) != 6)
		return (parsing_error("Invalid number of arguments for cone.\n"));
	fill_cone(info, &error, new_shape, new_cone);
	return (error);
}
