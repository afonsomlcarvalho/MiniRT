/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:52 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:53 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_scene	g_scene;

int	main(int argc, char **argv)
{
	parser(argc, argv);
	setup_scene();
	split_canva();
	print_instructions();
	mlx_hook(g_scene.win, 2, 1L << 0, key_press, NULL);
	mlx_hook(g_scene.win, 17, 0, end, NULL);
	mlx_hook(g_scene.win, 4, (1L << 2), select_piece, NULL);
	mlx_loop(g_scene.mlx);
	return (0);
}
