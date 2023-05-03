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

	if (keycode == 65363)
		factor = 0.1;
	else if (keycode == 65361)
		factor = -0.1;
	else
		return ;
	sphere = g_scene.selected->shape;
	if (sphere->radius < 0.1 && keycode == 65361)
		return ;
	sphere->radius *= (1 + factor);
	split_canva();
}

static void	change_cylinder_radius(int keycode)
{
	t_cylinder	*cylinder;
	double		factor;

	factor = 0;
	if (keycode == 65363 || keycode == 65362)
		factor = 0.1;
	else if (keycode == 65361 || keycode == 65364)
		factor = -0.1;
	cylinder = g_scene.selected->shape;
	if ((cylinder->radius < 1 && keycode == 65361) || (cylinder->height < 1 && keycode == 65364))
		return ;
	if (keycode == 65363 || keycode == 65361)
		cylinder->radius *= (1 + factor);
	else
		cylinder->height *= (1 + factor);
	substitute_caps(cylinder);
	split_canva();
}

void	change_cone(int keycode)
{
	t_cone	*cone;
	double	factor;

	factor = 0;
	cone = g_scene.selected->shape;
	if (keycode == 65362 || keycode == 65363)
		factor = 0.1;
	else if (keycode == 65364 || keycode == 65361)
		factor = -0.1;
	if ((cone->radius < 1 && keycode == 65361) || (cone->height < 1 && keycode == 65364))
			return ;
	if (keycode == 65361 || keycode == 65363)
		cone->radius *= (1 + factor);
	else
		cone->height *= (1 + factor);
	substitute_cone_base(cone);
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
	else if (g_scene.selected->type == CONE)
		change_cone(keycode);
}

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
	split_canva();
}

void	move_light(double *movement)
{
	g_scene.selected_light->position[X] += movement[X];
	g_scene.selected_light->position[Y] += movement[Y];
	g_scene.selected_light->position[Z] += movement[Z];
}

void	change_depth(int keycode)
{
	if (keycode == 65451 && g_scene.reflection < 6)
		g_scene.reflection++;
	else if (keycode == 65453 && g_scene.reflection > 0)
		g_scene.reflection--;
	split_canva();
}

int	key_press(int keycode)
{
	double	vector[3];
	double	angle[3];
	double	light[3];

	// printf("%d\n", keycode);
	if (keycode == 65307)
		end();
	if (keycode == 114)
		change_reflection();
	else if (keycode == 65505)
		change_texture();
	else if (keycode == 65361 || keycode == 65363 || \
			keycode == 65362 || keycode == 65364)
		change_shape_size(keycode);
	else if (keycode == 32)
		change_light();
	else if (keycode == 65451 || keycode == 65453)
		change_depth(keycode);
	else
	{
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
	}
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
	{
		copy_color(g_scene.selected->backup_color, g_scene.selected->color);
		g_scene.selected = 0;
		split_canva();
	}
	else
	{
		select_piece_aux(point);
		if (g_scene.selected)
		{
			apply_selection_color();
			split_canva();
		}
	}
	return (0);
}
