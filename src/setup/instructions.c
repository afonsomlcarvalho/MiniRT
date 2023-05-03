#include "../../inc/minirt.h"

static void	print_general_instructions(void)
{
	printf("%sUSAGE:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("  • To select a shape, click on it with the left mouse button\n");
	printf("  • To de-select a shape, press the right mouse button\n");
	printf("  • If no shapes are selected, the camera is slected by default\n");
	printf("  • To quit the program press ESC or close the window normally\n\n");
}

static void	print_movements(void)
{
	printf("%sMOVEMENT:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("Moving X axis:\n");
	printf("  • Up - W\n");
	printf("  • Down - D\n");
	printf("Moving Y axis:\n");
	printf("  • Left - A\n");
	printf("  • Right - D\n");
	printf("Moving Z axis:\n");
	printf("  • Forward - E\n");
	printf("  • Backward - Q\n\n");
}

static void	print_rotations(void)
{
	printf("%sROTATION:%s\n", CYAN_BOLD, CYAN_TEXT);
	printf("  • Clockwise Rotation - J\n");
	printf("  • Counter-clockwise Rotation - L\n");
	printf("Rotating Y axis:\n");
	printf("  • Clockwise Rotation - I\n");
	printf("  • Counter-clockwise Rotation - K\n");
	printf("Rotating Z axis:\n");
	printf("  • Clockwise Rotation - U\n");
	printf("  • Counter-clockwise Rotation - O\n%s", RESET_TEXT);
}

void	print_instructions(void)
{
	printf("\n%s----------------\n", CYAN_BOLD);
	printf("| INSTRUCTIONS |\n");
	printf("----------------%s\n", CYAN_TEXT);
	print_general_instructions();
	print_movements();
	print_rotations();
	printf("\n");
}