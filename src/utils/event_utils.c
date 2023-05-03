#include "../../inc/minirt.h"

void	change_light(void)
{
	t_light	*cur;

	cur = g_scene.lights;
	while (g_scene.selected_light)
	{
		g_scene.selected_light = g_scene.selected_light->next;
		if (!g_scene.selected_light || g_scene.selected_light->type)
			break ;
	}
	if (!g_scene.selected_light)
	{
		while (cur && !g_scene.selected_light)
		{
			if (cur->type)
				g_scene.selected_light = cur;
			cur = cur->next;
		}
	}
}

void	move_light(double *movement)
{
	g_scene.selected_light->position[X] += movement[X];
	g_scene.selected_light->position[Y] += movement[Y];
	g_scene.selected_light->position[Z] += movement[Z];
}

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];
	double	light[3];

	if (keycode == 65307)
		end();
	if (keycode == 32)
		change_light();
	vector[X] = ((keycode == 100) - (keycode == 97)) * 0.1;
	vector[Y] = ((keycode == 119) - (keycode == 115)) * 0.1;
	vector[Z] = ((keycode == 101) - (keycode == 113)) * 0.1;
	angle[X] = to_rad(((keycode == 108) - (keycode == 106)) * 15);
	angle[Y] = to_rad(((keycode == 105) - (keycode == 107)) * 15);
	angle[Z] = to_rad(((keycode == 111) - (keycode == 117)) * 15);
	light[X] = ((keycode == 110) - (keycode == 118)) * 0.1;
	light[Y] = ((keycode == 103) - (keycode == 98)) * 0.1;
	light[Z] = ((keycode == 104) - (keycode == 102)) * 0.1;
	apply_translation_and_rotation(g_scene.selected, vector, angle);
	move_light(light);
	return (0);
}

static void	select_piece_aux(double *point)
{
	double	t;
	t_shape	*cur;

	cur = g_scene.shapes;
	t = 0;
	while (cur)
	{
		if (cur->check_hit(cur->shape, point, g_scene.camera.origin, 0) && \
		(t == 0 || \
		cur->check_hit(cur->shape, point, g_scene.camera.origin, 0) < t))
		{
			g_scene.selected = cur;
			t = cur->check_hit(cur->shape, point, g_scene.camera.origin, 0);
		}
		cur = cur->next;
	}
}

int	select_piece(int button, int x, int y)
{
	double	point[3];

	if (button != 1)
		return (0);
	canvas_to_viewport(x - WIDTH / 2, y - HEIGHT / 2, point);
	if (g_scene.selected)
		g_scene.selected = 0;
	else
		select_piece_aux(point);
	return (0);
}
