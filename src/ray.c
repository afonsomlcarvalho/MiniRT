#include "../inc/minirt.h"

void	get_point(int t, float *vec, float *p)
{
	p[X] = scene.camera.origin[X] + t * (vec[X] - scene.camera.origin[X]);
	p[Y] = scene.camera.origin[Y] + t * (vec[Y] - scene.camera.origin[Y]);
	p[Z] = scene.camera.origin[Z] + t * (vec[Z] - scene.camera.origin[Z]);
}

int	trace_ray(float *vec)
{
	float	p[3];
	t_shape	*tmp;

	for (int t = 1; t < 100; t++)
	{
		get_point(t, vec, p);	
		tmp = scene.shapes;
		for (; tmp; tmp = tmp->next)
		{
			if (tmp->check_hit(tmp, p))
				return (tmp->color);
		}
	}
	return (0xffffffff);
}
