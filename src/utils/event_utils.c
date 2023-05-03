#include "../../inc/minirt.h"

static void	change_reflection(void)
{
	if (!g_scene.selected)
		return ;
	g_scene.selected->reflection += 0.1;
	if (g_scene.selected->reflection > 0.5)
		g_scene.selected->reflection = 0.0;
	split_canva();
}

static void	change_texture(void)
{
	g_scene.texture += 10;
	if (g_scene.texture >= 70)
		g_scene.texture = 0;
	split_canva();
}

static void	change_sphere_radius(int keycode)
{
	t_sphere	*sphere;
	double		factor;

	if (keycode == 65451)
		factor = 0.1;
	else if (keycode == 65453)
		factor = -0.1;
	else
		return ;
	sphere = g_scene.selected->shape;
	if (sphere->radius < 0.1)
		return ;
	sphere->radius *= (1 + factor);
	split_canva();
}

static void	change_cylinder_radius(int keycode)
{
	t_cylinder	*cylinder;
	double		factor;

	factor = 0;
	if (keycode == 65451 || keycode == 65362)
		factor = 0.1;
	else if (keycode == 65453 || keycode == 65364)
		factor = -0.1;
	cylinder = g_scene.selected->shape;
	if (cylinder->radius < 0.1 || cylinder->height < 1)
		return ;
	if (keycode == 65451 || keycode == 65453)
		cylinder->radius *= (1 + factor);
	else
		cylinder->height *= (1 + factor);
	substitute_caps(cylinder);
	split_canva();
}

void	change_shape_size(int keycode)
{
	if (!g_scene.selected)
		return ;
	if (g_scene.selected->type == SPHERE)
		change_sphere_radius(keycode);
	else if (g_scene.selected->type == CYLINDER)
		change_cylinder_radius(keycode);
}

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];

	if (keycode == 65307)
		end();
	if (keycode == 114)
		change_reflection();
	else if (keycode == 65505)
		change_texture();
	else if (keycode == 65451 || keycode == 65453 || \
			keycode == 65362 || keycode == 65364)
		change_shape_size(keycode);
	else
	{
		vector[X] = ((keycode == 100) - (keycode == 97)) * 0.1;
		vector[Y] = ((keycode == 119) - (keycode == 115)) * 0.1;
		vector[Z] = ((keycode == 101) - (keycode == 113)) * 0.1;
		angle[X] = to_rad(((keycode == 108) - (keycode == 106)) * 15);
		angle[Y] = to_rad(((keycode == 105) - (keycode == 107)) * 15);
		angle[Z] = to_rad(((keycode == 111) - (keycode == 117)) * 15);
		apply_translation_and_rotation(g_scene.selected, vector, angle);
	}
	// printf("%d\n", keycode);
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
