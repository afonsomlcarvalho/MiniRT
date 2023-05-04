#include "../../inc/minirt.h"

void	error_handler(void)
{
	parsing_error("Dynamic memory allocation failed\n");
	free_all(1);
	exit(EXIT_FAILURE);
}
