#include "../inc/minirt.h"

void	get_normal_plane(void *self, double t, double *p, double *normal)
{
	t_plane		*plane;

	(void) t;
	(void) p;
	plane = (t_plane *) self;
	normalize_vector(plane->normal, normal);
}

int	check_side(double *light, t_plane *plane)
{
	double	c_vector[3];
	double	l_vector[3];
	double	c_dot;
	double	l_dot;

	vec(plane->point, scene.camera.origin, c_vector);
	vec(plane->point, light, l_vector);
	c_dot = dot(plane->normal, c_vector);
	l_dot = dot(plane->normal, l_vector);
	if ((c_dot > 0 && l_dot < 0) || (c_dot < 0 && l_dot > 0))
		return (1);
	return (0);
}

double	check_hit_plane(void *self, double p[3], double origin[3], int flag)
{
	t_plane	*plane;
	double	t;
	double	oq[3];
	double	D[3];

	(void)flag;
	plane = (t_plane *) self;
	vec(origin, p, D);
	vec(origin, plane->point, oq);
	if (dot(plane->normal, D) == 0)
		return (0.0);
	t = dot(plane->normal, oq) / dot(plane->normal, D);
	if (!flag && t < 1)
		return (0.0);
	if (flag == 1 && check_side(origin, plane))
		return (0.2);
	return (t);
}

void	add_plane(char **info)
{
	t_shape		*new_shape;
	t_plane		*new_plane;

	new_shape = ft_calloc(1, sizeof(t_shape));
	if (!new_shape)
		return ;	//TODO: Error Handling

	new_shape->type = PLANE;
	get_color(info[3], new_shape->color);
	new_shape->check_hit = check_hit_plane;
	new_shape->get_normal = get_normal_plane;
	new_shape->spec = -1;
	new_shape->next = NULL;

	new_plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	new_shape->shape = new_plane;
	if (!new_plane)
		return ;	//TODO: Error Handling

	coords_interpreter(info[1], new_plane->point);
	coords_interpreter(info[2], new_plane->normal);
	add_back_shape(new_shape);
}

