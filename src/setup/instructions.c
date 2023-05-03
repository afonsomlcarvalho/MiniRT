#include "../../inc/minirt.h"

static void	print_general_instructions(void)
{
	printf("Usage:\n");
	printf("  • To select a shape, press the left mouse button\n");
	printf("  • If no shapes are selected, the camera is slected by default\n");
	printf("  • To quit the program press ESC or close the window normally\n\n");
}

static void	print_movements(void)
{
	printf("Moving:\n");
	printf("  • Up - W\n");
	printf("  • Down - D\n");
	printf("  • Left - A\n");
	printf("  • Right - D\n");
	printf("  • Forward - E\n");
	printf("  • Backward - Q\n");
}

static void	print_rotations(void)
{
	printf("Rotating X axis:\n");
	printf("  • Clockwise Rotation - J\n");
	printf("  • Counter-clockwise Rotation - L\n");
	printf("Rotating Y axis:\n");
	printf("  • Clockwise Rotation - I\n");
	printf("  • Counter-clockwise Rotation - K\n");
	printf("Rotating Z axis:\n");
	printf("  • Clockwise Rotation - U\n");
	printf("  • Counter-clockwise Rotation - O");
}

void	print_instructions(void)
{
	printf("\n%s----------------\n", CYAN_TEXT);
	printf("| INSTRUCTIONS |\n");
	printf("----------------\n");
	print_general_instructions();
	print_movements();
	print_rotations();
	printf("\n%s", RESET_TEXT);
}