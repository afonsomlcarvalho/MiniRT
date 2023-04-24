#include "../inc/minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	get_point(int t, double *vec, double *p)
{
	p[X] = scene.camera.origin[X] + t * (vec[X] - scene.camera.origin[X]);
	p[Y] = scene.camera.origin[Y] + t * (vec[Y] - scene.camera.origin[Y]);
	p[Z] = scene.camera.origin[Z] + t * (vec[Z] - scene.camera.origin[Z]);
}

int	trace_ray(double *p)
{
	double	t;
	t_aux	**lst;
	t_shape	*tmp;
	int		color;
	double	light[3];
	
	lst = (t_aux **)ft_calloc(1, sizeof(t_aux));
	if (!lst)
		return (-1);	//TODO: Error Handling
	tmp = scene.shapes;
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, p, scene.camera.origin, 0);
		if (t > 0)
		{
			determine_light(light, t, p);
			color = rgb_to_color(tmp->color, light);
			add_to_list(t, color, lst);
		}
		tmp = tmp->next;
	}
	if (!*lst)
		color = 0;
	else
		color = get_list_min(lst);
	delete_list(lst);
	return (color);
}
