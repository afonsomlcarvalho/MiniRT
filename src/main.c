#include "../inc/minirt.h"

t_scene	g_scene;

int	main(int argc, char **argv)
{
	parser(argc, argv);
	setup_scene();
	split_canva();
	mlx_hook(g_scene.win, 2, 1L << 0, key_press, NULL);
	mlx_hook(g_scene.win, 17, 0, end, NULL);
	mlx_hook(g_scene.win, 4, (1L << 2), select_piece, NULL);
	mlx_loop(g_scene.mlx);
	return (0);
}
