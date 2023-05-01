#include "../inc/minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	get_object_intersections(double *origin, double *p, t_aux **lst)
{
	t_shape	*tmp;
	double	t;
	double	light[3];
	double	normal[3];
	int		color;

	tmp = scene.shapes;
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, p, origin, 0);
		if (t > 0)
		{
			tmp->get_normal(tmp->shape, t, origin, p, normal);
			determine_light(light, t, origin, p, normal, tmp);
			color = rgb_to_color(tmp->color, light);
			add_to_list(t, color, tmp, lst);
		}
		tmp = tmp->next;
	}
}

int	get_full_color(int	local_color, int reflected_color, double r)
{
	int	local[3];
	int	reflected[3];
	int	full[3];

	local[0] = (local_color >> 16) & 255;
	local[1] = (local_color >> 8) & 255;
	local[2] = local_color & 255;
	reflected[0] = (reflected_color >> 16) & 255;
	reflected[1] = (reflected_color >> 8) & 255;
	reflected[2] = reflected_color & 255;

	full[0] = local[0] * (1 - r) + reflected[0] * r;
	full[1] = local[1] * (1 - r) + reflected[1] * r;
	full[2] = local[2] * (1 - r) + reflected[2] * r;
	if (full[0] > 255)
		full[0] = 255;
	if (full[1] > 255)
		full[1] = 255;
	if (full[2] > 255)
		full[2] = 255;
	return ((full[0] << 16) + (full[1] << 8) + full[2]);

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
			closest->self->get_normal(closest->self->shape, closest->t, origin, p, normal);
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
