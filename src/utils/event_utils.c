#include "../../inc/minirt.h"

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];

	if (keycode == 65307)
		end();
	vector[X] = ((keycode == 100) - (keycode == 97)) * 0.1;
	vector[Y] = ((keycode == 119) - (keycode == 115)) * 0.1;
	vector[Z] = ((keycode == 101) - (keycode == 113)) * 0.1;
	angle[X] = to_rad(((keycode == 108) - (keycode == 106)) * 15);
	angle[Y] = to_rad(((keycode == 105) - (keycode == 107)) * 15);
	angle[Z] = to_rad(((keycode == 111) - (keycode == 117)) * 15);
	apply_translation_and_rotation(g_scene.selected, vector, angle);
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
