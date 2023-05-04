/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:26 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 14:55:49 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	get_object_intersections(double *origin, double *p, t_aux **lst)
{
	t_shape		*tmp;
	t_lightaux	*lightaux;
	double		t;
	int			color;

	tmp = g_scene.shapes;
	lightaux = (t_lightaux *) ft_calloc(1, sizeof(t_lightaux));
	if (!lightaux)
		error_handler();
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, p, origin, 0);
		if (t > 0)
		{
			find_point(t, origin, p, lightaux->colision);
			tmp->get_normal(tmp->shape, lightaux->colision, lightaux->normal, tmp->camera_in);
			determine_light(lightaux, origin, tmp);
			color = rgb_to_color(tmp->color, lightaux->light);
			add_to_list(t, color, tmp, lst);
		}
		tmp = tmp->next;
	}
	free(lightaux);
}

static void	setup_recursion(t_rayaux *rayaux, double *origin, double *p)
{
	find_point(rayaux->closest->t, origin, p, rayaux->new_origin);
	vec(origin, p, rayaux->incoming_ray);
	rayaux->closest->self->get_normal(rayaux->closest->self->shape, \
		rayaux->new_origin, rayaux->normal, rayaux->closest->self->camera_in);
	get_reflected_ray(rayaux->incoming_ray, rayaux->normal, \
		rayaux->reflected_ray);
	add_vecs(rayaux->new_origin, rayaux->reflected_ray, rayaux->new_p);
}

static void	trace_ray_aux(int *local, int *ref, t_rayaux *rayaux, t_aux **lst)
{
	rayaux->closest = get_closest_object(lst);
	if (rayaux->closest)
		*local = rayaux->closest->color;
	*ref = -1;
	if (!rayaux->closest)
		*local = BACKGROUND;
}

int	trace_ray(double *origin, double *p, int recur)
{
	int			local_color;
	int			ref_color;
	double		r;
	t_aux		**lst;
	t_rayaux	*rayaux;

	lst = (t_aux **)ft_calloc(1, sizeof(t_aux *));
	rayaux = (t_rayaux *)ft_calloc(1, sizeof(t_rayaux));
	if (!lst || !rayaux)
		error_handler();
	get_object_intersections(origin, p, lst);
	trace_ray_aux(&local_color, &ref_color, rayaux, lst);
	if (rayaux->closest && rayaux->closest->self->reflection != 0 \
	&& recur != 0 && !g_scene.texture && !rayaux->closest->self->camera_in)
	{
		setup_recursion(rayaux, origin, p);
		ref_color = trace_ray(rayaux->new_origin, rayaux->new_p, recur - 1);
	}
	r = rayaux->closest->self->reflection;
	delete_list(lst);
	free(rayaux);
	if (ref_color == -1)
		return (local_color);
	return (get_full_color(local_color, ref_color, r));
}
