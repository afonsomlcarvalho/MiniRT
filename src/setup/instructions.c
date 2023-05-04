/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:51 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:17:38 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_general_instructions(void)
{
	printf("%sUSAGE:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("    • To select a shape, click on it with the left mouse button\n");
	printf("    • To de-select a shape, press the right mouse button\n");
	printf("    \
	• If no shapes are selected, the camera is slected by default\n");
	printf("    \
	• To quit the program press ESC or close the window normally\n\n");
}

void	print_movements(void)
{
	printf("%sMOVEMENT:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("  Moving X axis:\n");
	printf("    • Left -> A\n");
	printf("    • Right -> D\n");
	printf("  Moving Y axis:\n");
	printf("    • Up -> W\n");
	printf("    • Down -> S\n");
	printf("  Moving Z axis:\n");
	printf("    • Forward -> E\n");
	printf("    • Backward -> Q\n\n");
}

void	print_rotations(void)
{
	printf("%sROTATION:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("  Rotating X axis:\n");
	printf("    • Clockwise Rotation -> J\n");
	printf("    • Counter-clockwise Rotation -> L\n");
	printf("  Rotating Y axis:\n");
	printf("    • Clockwise Rotation -> I\n");
	printf("    • Counter-clockwise Rotation -> K\n");
	printf("  Rotating Z axis:\n");
	printf("    • Clockwise Rotation -> U\n");
	printf("    • Counter-clockwise Rotation -> O\n\n");
}

void	print_surface(void)
{
	printf("%sSURFACE:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("    • Increase Reflection Depth -> +\n");
	printf("    • Decrease Reflection Depth -> -\n");
	printf("    • Increase Reflection Factor -> R\n");
	printf("    • Toggle Ruggedness -> Shift\n\n");
}

void	print_resize(void)
{
	printf("%sDIMENSION:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("    • Increase Radius -> Right Arrow\n");
	printf("    • Decrease Radius -> Left Arrow\n");
	printf("    • Increase Height -> Up Arrow\n");
	printf("    • Decrease Height -> Down Arrow\n");
}
