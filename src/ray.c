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
	float	t;
	t_aux	**lst;
	float	a;
	float	b;
	float	c;
	float	D[3];
	float	co[3];
	t_shape	*tmp;
	int		color;

	vec(scene.camera.origin, p, D);
	a = dot(D, D);

	lst = (t_aux **)ft_calloc(1, sizeof(t_aux));
	if (!lst)
		return (-1);	//TODO: Error Handling
	tmp = scene.shapes;
	while (tmp)
	{
		vec(tmp->center, scene.camera.origin, co);
		b = 2 * dot(co, D);
		c = dot(co, co) - pow(tmp->radius, 2);
		t = solve_quadratic(a, b, c);
		if (t)
		{
			color = tmp->color;
			add_to_list(t, color, lst);
		}
		tmp = tmp->next;
	}
	if (!*lst)
		color = 0xffffffff;
	else
		color = get_list_min(lst);
	delete_list(lst);
	return (color);
}
