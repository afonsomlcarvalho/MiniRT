#include "../../inc/minirt.h"
#include <stdio.h>

/* Adds diffuse reflection to the COLISION point according to the 
 * NORMAL vector and light CUR, storing the results in LIGHT */
void	diffuse_reflection(t_lightaux *lightaux, t_light *cur)
{
	double	L[3];
	double	prod;
	int		i;

	vec(lightaux->colision, cur->position, L);
	prod = dot(lightaux->normal, L);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			lightaux->light[i] += 0.9 * (cur->brightness * prod / \
			(vector_size(lightaux->normal) * vector_size(L))) * (cur->color[i] / 255);
	}
}

void	specular_reflection(t_lightaux *lightaux, double *origin, t_light *cur, t_shape *shape)
{
	double	L[3];

	double	R[3];
	double	V[3];
	double	prod;
	int		i;	
	double	Ln[3];
	double	Lp[3];


	if (shape->spec == -1)
		return ;
	vec(lightaux->colision, cur->position, L);
	vec(lightaux->colision, origin, V);
	mult_vecs(dot(lightaux->normal, L), lightaux->normal, Ln);
	subtract_vecs(L, Ln, Lp);
	subtract_vecs(Ln, Lp, R);
	prod = dot(R, V);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			lightaux->light[i] += cur->brightness * pow(prod / \
			(vector_size(R) * vector_size(V)), shape->spec) * (cur->color[i] / 255);
	}
}

