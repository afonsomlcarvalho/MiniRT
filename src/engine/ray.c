#include "../../inc/minirt.h"
#include <stdio.h>
#include <stdlib.h>

static void	get_object_intersections(double *origin, double *p, t_aux **lst)
{
	t_shape		*tmp;
	t_lightaux	*lightaux;
	double		t;
	int			color;

	tmp = g_scene.shapes;
	lightaux = (t_lightaux *) ft_calloc(1,sizeof(t_lightaux));
	if (!lightaux)
		return ;	//TODO: Error Handling
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, p, origin, 0);
		if (t > 0)
		{
			find_point(t, origin, p, lightaux->colision);
			tmp->get_normal(tmp->shape, lightaux->colision, lightaux->normal);
			determine_light(lightaux, origin, tmp);
			color = rgb_to_color(tmp->color, lightaux->light);
			add_to_list(t, color, tmp, lst);
		}
		tmp = tmp->next;
	}
	free(lightaux);
}

int	trace_ray(double *origin, double *p, int recur)
{
	t_aux	**lst;
	t_aux	*closest;
	int		color;
	int		local_color;
	int		reflected_color = -1;
	double	new_origin[3];
	double	new_p[3];
	double	reflected_ray[3];
	double	incoming_ray[3];
	double	normal[3];
	double	r;
	//(void) recur;
	
	lst = (t_aux **)ft_calloc(1, sizeof(t_aux *));
	if (!lst)
		return (-1);	//TODO: Error Handling
	get_object_intersections(origin, p, lst);
	closest = get_closest_object(lst);
	if (!closest)
		local_color = BACKGROUND;
	else
	{
		
		local_color = closest->color;
		if (closest->self->reflection != 0 && recur != 0)
		{
			// get the new origin, which is the current colision point
			find_point(closest->t, origin, p, new_origin);

			// get the new p, which is obtained by adding the new_origin to the reflected vector
			vec(origin, p, incoming_ray);

			closest->self->get_normal(closest->self->shape, new_origin, normal);
			get_reflected_ray(incoming_ray, normal, reflected_ray);

			new_p[X] = new_origin[X] + reflected_ray[X];
			new_p[Y] = new_origin[Y] + reflected_ray[Y];
			new_p[Z] = new_origin[Z] + reflected_ray[Z];

			reflected_color = trace_ray(new_origin, new_p, recur - 1);
		}
	}
	r = closest->self->reflection;
	delete_list(lst);
	if (reflected_color == -1)
		return (local_color);
	color = get_full_color(local_color, reflected_color, r);
	return (color);
}
