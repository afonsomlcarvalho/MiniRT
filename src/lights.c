#include "../inc/minirt.h"
#include <stdio.h>

void	add_back_light(t_light *new_light)
{
	t_light	*tmp;

	if (!new_light)
		return ;
	if (!scene.lights)
	{
		scene.lights = new_light;
		return ;
	}
	tmp = scene.lights;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_light;
}

void	light_setup(char **info, int flag)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	coords_interpreter(info[1 + flag], &light->brightness);
	if (light->brightness < 0 || light->brightness > 1)
		parsing_error("Invalid brightness\n");
	coords_interpreter(info[2 + flag], light->color);
	light->type = flag;
	light->next = NULL;
	if (flag)
		coords_interpreter(info[1], light->position);
	add_back_light(light);
}

/* Finds the intersection point of the ray from the camera passing
 * through point p according to t */
void	find_point(double t, double *p, double *buf)
{
	buf[X] = scene.camera.origin[X] + t * (p[X] - scene.camera.origin[X]);
	buf[Y] = scene.camera.origin[Y] + t * (p[Y] - scene.camera.origin[Y]);
	buf[Z] = scene.camera.origin[Z] + t * (p[Z] - scene.camera.origin[Z]);
}

/* void new_point(t_light *light, double *colision)
{
	colision[X] = colision[X] + 0.1 * (light->position[X] - colision[X]);
	colision[Y] = colision[Y] + 0.1 * (light->position[Y] - colision[Y]);
	colision[Z] = colision[Z] + 0.1 * (light->position[Z] - colision[Z]);
} */

int	check_all(t_light *light, double *colision)
{
	t_shape	*cur;
	double	t;

	cur = scene.shapes;
	while (cur)
	{
		t = cur->check_hit(cur->shape, colision, light->position, 1);
		if (t < 0.999999999 && t > 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}

void	determine_light(double *light, double t, double *p, double *normal)
{
	t_light	*cur;
	double	colision[3];
	int		i;

	light[0] = 0;
	light[1] = 0;
	light[2] = 0;
	cur = scene.lights;
	find_point(t, p, colision);
	while (cur)
	{
		if (cur->type == AMBIENT)
		{
			i = -1;
			while (++i < 3)
				light[i] += cur->brightness * (cur->color[i] / 255);
		}
		else if (!is_in_shadow(colision, cur))
		{
			diffuse_reflection(colision, normal, cur, light);
			specular_reflection(colision, normal, cur, light);
		}
		cur = cur->next;
	}
}
