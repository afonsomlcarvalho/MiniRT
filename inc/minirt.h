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

typedef	struct s_light
{
	float			brightness;
	float			position[3];
	int				type;
	float			color[3];
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	float	center[3];
	float	radius;
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
	float			(*check_hit)(void *self, float point[3], float origin[3], int flag);
	float			color[3];
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
	float	direction[3];
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
	t_light	*lights;
}	t_scene;

typedef struct s_aux
{
	float			t;
	int				color;
	struct s_aux	*next;
}	t_aux;

extern t_scene scene;

void	parser(int argc, char **argv);
int		coords_interpreter(char *coords, float *point);
void	free_array(char **array);
void	parsing_error(char *str);
int		rgb_to_color(float *rgb, float *light);
void	light_setup(char **info, int flag);
void	determine_light(float *light, float t, float *p);
void	setup_scene(void);
void	setup_camera(char **info);
void	setup_viewport(void);
void	canvas_to_viewport(int x, int y, float *p);
int		trace_ray(float *p);

float	dot(float *v1, float *v2);
void	vec(float *p1, float *p2, float *buff);
float	solve_quadratic(float a, float b, float c, int flag);

int		get_list_min(t_aux **lst);
void	add_to_list(float t, int color, t_aux **lst);
void	delete_list(t_aux **lst);



void	add_back_shape(t_shape *new_shape);

void	add_sphere(char **info);

void	add_plane(char **info);

#endif
