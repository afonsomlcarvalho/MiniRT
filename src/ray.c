#include "../inc/minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	get_point(int t, float *vec, float *p)
{
	p[X] = scene.camera.origin[X] + t * (vec[X] - scene.camera.origin[X]);
	p[Y] = scene.camera.origin[Y] + t * (vec[Y] - scene.camera.origin[Y]);
	p[Z] = scene.camera.origin[Z] + t * (vec[Z] - scene.camera.origin[Z]);
}

int	trace_ray(float *p)
{
	float	a;
	float	b;
	float	c;
	float	co[3];
	float	D[3];
	t_shape	*tmp;

	vec(scene.camera.origin, p, D);
	a = dot(D, D);
	tmp = scene.shapes;
	while (tmp)
	{
		vec(tmp->center, scene.camera.origin, co);
		b = 2 * dot(co, D);
		c = dot(co, co) - pow(tmp->radius, 2);
		if ((pow(b, 2) - 4 * a * c) >= 0)
			return (tmp->color);
		tmp = tmp->next;
	}
	return (0xffffffff);
}
