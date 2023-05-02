#include "../../inc/minirt.h"

void	set_vectors(double *w_vector, double *h_vector)
{
	double			up[3];

	up[1] = 1;
	up[0] = 0;
	up[2] = 0;
	cross_product(up, g_scene.camera.direction, w_vector);
	if (!g_scene.camera.direction[X] && !g_scene.camera.direction[Z] && \
	g_scene.camera.direction[Y])
	{
		w_vector[X] = 1;
		w_vector[Y] = 0;
		w_vector[Z] = 0;
	}
	cross_product(w_vector, g_scene.camera.direction, h_vector);
}
