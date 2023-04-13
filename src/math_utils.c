#include "../inc/minirt.h"

/* Returns the dot product between V1 and V2 */
float	dot(float *v1, float *v2)
{
	return ((v1[X] * v2[X]) + (v1[Y] * v2[Y]) + (v1[Z] * v2[Z]));
}

/* Calculates the vector starting at P1 and passing 
 * through P2, storing it in buff */
void	vec(float *p1, float *p2, float *buff)
{
	buff[X] = p2[X] - p1[X];
	buff[Y] = p2[Y] - p1[Y];
	buff[Z] = p2[Z] - p1[Z];
}
