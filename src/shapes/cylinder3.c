/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:10 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:18:34 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	t_discover(double *t, t_cylinder *self)
{
	double	quadratic[3];

	quadratic[0] = dot(self->axis, self->axis);
	quadratic[1] = 0;
	quadratic[2] = -(pow(self->height, 2) / 4);
	t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - 4 * \
	quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - 4 * \
	quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
}

void	add_caps_aux(t_plane *top_cap, t_plane *down_cap, t_cylinder *self)
{
	int		i;
	double	t[2];

	i = -1;
	while (++i < 3)
	{
		top_cap->normal[i] = self->axis[i];
		down_cap->normal[i] = self->axis[i];
	}
	t_discover(t, self);
	i = -1;
	while (++i < 3)
	{
		down_cap->point[i] = self->center[i] + t[0] * self->axis[i];
		top_cap->point[i] = self->center[i] + t[1] * self->axis[i];
	}
	self->top_cap = top_cap;
	self->under_cap = down_cap;
}

void	add_caps(t_cylinder *self)
{
	t_plane	*top_cap;
	t_plane	*down_cap;

	top_cap = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (!top_cap)
		error_handler();
	down_cap = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (!down_cap)
		error_handler();
	add_caps_aux(top_cap, down_cap, self);
}
