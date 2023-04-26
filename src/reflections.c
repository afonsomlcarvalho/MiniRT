#include "../inc/minirt.h"

/* Adds diffuse reflection to the COLISION point according to the 
 * NORMAL vector and light CUR, storing the results in LIGHT */
void	diffuse_reflection(double *colision, double *normal, t_light *cur, double *light)
{
	double	L[3];
	double	prod;
	int		i;

	vec(colision, cur->position, L);
	prod = dot(normal, L);
	// if (colision[X] == 0 && colision[Y] == 0 && colision[Z] == 8)
	// 		printf("colision: 0 0 8\ncur->position: %f %f %f\nnormal: %f %f %f\nprod: %f\n", cur->position[X], cur->position[Y], cur->position[Z], normal[X], normal[Y], normal[Z], prod);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			light[i] += 0.9 * (cur->brightness * prod / (vector_size(normal) * vector_size(L))) * (cur->color[i] / 255);
	}
}

void	specular_reflection(double *colision, double *normal, t_light *cur, double *light)
{
	double	L[3];
	double	Ln[3];
	double	Lp[3];
	double	R[3];
	double	V[3];
	double	prod;
	int		i;

	if (scene.cur->spec == -1)
		return ;
	vec(colision, cur->position, L);
	vec(colision, scene.camera.origin, V);
	mult_vecs(dot(normal, L), normal, Ln);
	subtract_vecs(L, Ln, Lp);
	subtract_vecs(Ln, Lp, R);
	prod = dot(R, V);
	if (prod > 0)
	{
		i = -1;
		while (++i < 3)
			light[i] += cur->brightness * pow(prod / (vector_size(R) * vector_size(V)), \
					scene.cur->spec) * (cur->color[i] / 255);
	}
}

