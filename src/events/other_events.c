#include "../../inc/minirt.h"

void	change_reflection(void)
{
	if (!g_scene.selected)
		return ;
	g_scene.selected->reflection += 0.1;
	if (g_scene.selected->reflection > 0.5)
		g_scene.selected->reflection = 0.0;
	split_canva();
}

void	change_texture(void)
{
	g_scene.texture += 10;
	if (g_scene.texture >= 70)
		g_scene.texture = 0;
	split_canva();
}

void	change_depth(int keycode)
{
	if (keycode == 65451 && g_scene.reflection < 6)
		g_scene.reflection++;
	else if (keycode == 65453 && g_scene.reflection > 0)
		g_scene.reflection--;
	split_canva();
}
