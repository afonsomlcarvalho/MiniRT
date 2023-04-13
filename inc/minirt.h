#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "../lib/libft/inc/libft.h"
#include "../lib/mlx_linux/mlx.h"

# define X	0
# define Y	1
# define Z	2

# define WIDTH	1080
# define HEIGHT	1080

enum e_type
{
	SPHERE,
	CILINDER,
	PLANE
};

typedef struct s_sphere
{
	float	center[3];
	int		radius;
}	t_sphere;

typedef struct s_plane
{
	float	point[3];
	float	normal[3];
}	t_plane;

typedef struct s_shape
{
	int				type;
	void			*shape;
	float			(*check_hit)(void *self, float point[3]);
	int				color;
	struct s_shape	*next;
}	t_shape;

typedef struct s_img
{
	void	*img_ptr;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_cam
{
	float	origin[3];
	float	direcion[3];
	int		fov;
}	t_cam;

typedef struct s_vpt
{
	float		height;
	float		width;
	float		distance;
}	t_vpt;

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	t_img	img;

	t_cam	camera;
	t_vpt	viewport;
	t_shape	*shapes;
}	t_scene;

typedef struct s_aux
{
	float			t;
	int				color;
	struct s_aux	*next;
}	t_aux;

extern t_scene scene;

void	setup_scene(void);
void	setup_camera(void);
void	setup_viewport(void);
void	canvas_to_viewport(int x, int y, float *p);
int		trace_ray(float *p);
void	add_shape(int type, int color, float *center, int radius);

float	dot(float *v1, float *v2);
void	vec(float *p1, float *p2, float *buff);
int		get_list_min(t_aux **lst);
void	add_to_list(float t, int color, t_aux **lst);
void	delete_list(t_aux **lst);
float	solve_quadratic(float a, float b, float c);

void	add_back_shape(t_shape *new_shape);

void	add_sphere(int color, float *center, int radius);

void	add_plane(int color, float *point, float *normal);

#endif
