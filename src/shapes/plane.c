#include "../../inc/minirt.h"

void	get_normal_plane(void *self, double *colision, double *normal)
{
	t_plane		*plane;

	(void) colision;
	plane = (t_plane *) self;
	normalize_vector(plane->normal, normal);
}

int	check_side(double *light, t_plane *plane)
{
	double	c_vector[3];
	double	l_vector[3];
	double	c_dot;
	double	l_dot;

	vec(plane->point, g_scene.camera.origin, c_vector);
	vec(plane->point, light, l_vector);
	c_dot = dot(plane->normal, c_vector);
	l_dot = dot(plane->normal, l_vector);
	if ((c_dot > 0.000000001 && l_dot < -0.000000001) || (c_dot < -0.000000001 && l_dot > 0.000000001))
		return (1);
	return (0);
}

double	check_hit_plane(void *self, double p[3], double origin[3], int flag)
{
	t_plane	*plane;
	double	t;
	double	oq[3];
	double	d[3];

	(void)flag;
	plane = (t_plane *) self;
	vec(origin, p, d);
	vec(origin, plane->point, oq);
	if (dot(plane->normal, d) == 0)
		return (0.0);
	t = dot(plane->normal, oq) / dot(plane->normal, d);
	if (!flag && t < 1)
		return (0.0);
	if (flag == 1 && check_side(origin, plane))
		return (0.2);
	return (t);
}

void	fill_plane(char **info, int *error, t_shape *new_shape, t_plane *plane)
{
	new_shape->type = PLANE;
	if (get_color(info[3], new_shape->color))
		*error += parsing_error("Invalid plane colour.\n");
	new_shape->check_hit = check_hit_plane;
	new_shape->get_normal = get_normal_plane;
	new_shape->spec = -1;
	if (coords_interpreter(info[4], &new_shape->reflection) || new_shape->reflection < 0 || new_shape->reflection >= 0.5)
		*error += parsing_error("Invalid plane reflection.\n");
	new_shape->next = NULL;
	if (coords_interpreter(info[1], plane->point))
		*error += parsing_error("Invalid plane position.\n");
	if (coords_interpreter(info[2], plane->normal) || \
	check_normalized_vector(plane->normal))
		*error += parsing_error("Invalid plane normal vector.\n");
	if (dot(g_scene.camera.direction, plane->normal) > 0)
		mult_vecs(-1, plane->normal, plane->normal);
}

int	add_plane(char **info)
{
	t_shape	*new_shape;
	t_plane	*new_plane;
	int		error;

	new_shape = ft_calloc(1, sizeof(t_shape));
	error = 0;
	if (!new_shape)
		return 0;	//TODO: Error Handling
	add_back_shape(new_shape);
	new_plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	new_shape->shape = new_plane;
	if (!new_plane)
		return 0;	//TODO: Error Handling
	if (array_size(info) != 5)
		return (parsing_error("Invalid number of arguments for plane.\n"));
	fill_plane(info, &error, new_shape, new_plane);
	return (error);
}
