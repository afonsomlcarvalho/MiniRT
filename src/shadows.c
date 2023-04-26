#include "../inc/minirt.h"

/* Checks if the COLISION point is in shadow */
int	is_in_shadow(double *colision, t_light *light)
{
	double	L[3];
	double	t;
	t_shape	*tmp;

	vec(colision, light->position, L);
	tmp = scene.shapes;
	while (tmp)
	{
		t = tmp->check_hit(tmp->shape, light->position, colision, 1);
		if (t > 0 && t < 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
