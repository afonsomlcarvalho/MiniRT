/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:29 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 16:22:29 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

/* Adds diffuse reflection to the COLISION point according to the 
 * NORMAL vector and light CUR, storing the results in LIGHT */
void	diffuse_reflection(t_lightaux *lightaux, t_light *cur)
{
	double	l[3];
	double	prod;
	int		i;

	vec(lightaux->colision, cur->position, l);
	prod = dot(lightaux->normal, l);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			lightaux->light[i] += 0.9 * (cur->brightness * prod / 
			(vector_size(lightaux->normal) * vector_size(l))) * \
			(cur->color[i] / 255);
	}
}

void	specular_reflection(t_lightaux *lightaux, double *origin, \
		t_light *cur, t_shape *shape)
{
	t_specaux	*specaux;
	double		prod;
	int			i;	

	if (shape->spec == -1)
		return ;
	specaux = (t_specaux *) ft_calloc(1, sizeof(t_specaux));
	if (!specaux)
		error_handler();
	vec(lightaux->colision, cur->position, specaux->l);
	vec(lightaux->colision, origin, specaux->v);
	mult_vecs(dot(lightaux->normal, specaux->l), lightaux->normal, specaux->ln);
	subtract_vecs(specaux->l, specaux->ln, specaux->lp);
	subtract_vecs(specaux->ln, specaux->lp, specaux->r);
	prod = dot(specaux->r, specaux->v);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			lightaux->light[i] += cur->brightness * pow(prod / \
			(vector_size(specaux->r) * vector_size(specaux->v)), \
			shape->spec) * (cur->color[i] / 255);
	}
	free(specaux);
}
