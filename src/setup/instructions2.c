/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:14:32 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:15:01 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_instructions(void)
{
	printf("\n%s----------------------------------------\n", CYAN_BOLD);
	printf("##########    INSTRUCTIONS    ##########\n");
	printf("----------------------------------------%s\n", CYAN_TEXT);
	print_general_instructions();
	print_movements();
	print_rotations();
	print_surface();
	print_resize();
	printf("----------------------------------------%s\n\n", RESET_TEXT);
}
