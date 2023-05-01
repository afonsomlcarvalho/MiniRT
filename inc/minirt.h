#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#include "../lib/libft/inc/libft.h"
#include "../lib/mlx_linux/mlx.h"

# define X	0
# define Y	1
# define Z	2

# define WIDTH		1080
# define HEIGHT		1080
# define DEF_SPEC	200

# define BACKGROUND	0xffffffff
# define THREAD		20
# define REFLECTIONS 0

enum e_type
{
	SPHERE,
	CYLLINDER,
	PLANE,
	CONE
};

enum e_reflection
{
	DIFFUSE,
	SPECULAR,
	BOTH
};

enum e_light
{
	AMBIENT,
	POINT
};

typedef	struct s_light
{
	double			brightness;
	double			position[3];
	int				type;
	int				color[3];
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	double	center[3];
	double	radius;
}	t_sphere;

typedef struct s_cone
{
	double	vertix[3];
	double	axis[3];
	double	angle;
	double	height;
	void	*base;
}	t_cone;

typedef struct s_plane
{
	double	point[3];
	double	normal[3];
}	t_plane;

typedef struct s_cyllinder
{
	double	center[3];
	double	radius;
	double	axis[3];
	double 	height;
	void	*top_cap;
	void	*under_cap;
}	t_cyllinder;

typedef struct s_shape
{
	int				type;
	void			*shape;
	double			(*check_hit)(void *self, double point[3], double origin[3], int flag);
	void			(*get_normal)(void *self, double t, double *origin, double *p, double *normal);
	int				color[3];
	int				spec;
	double			reflection;
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
	double	origin[3];
	double	direction[3];
	int		fov;
}	t_cam;

typedef struct s_vpt
{
	double		height;
	double		width;
	double		distance;
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
	t_shape	*selected;
}	t_scene;

typedef struct s_aux
{
	double			t;
	int				color;
	t_shape			*self;
	struct s_aux	*next;
}	t_aux;

extern t_scene scene;

void	parser(int argc, char **argv);
int		coords_interpreter(char *coords, double *point);
void	free_array(char **array);
int		parsing_error(char *str);
int		rgb_to_color(int *rgb, double *light);
int		light_setup(char **info, int flag);
void	determine_light(double *light, double t, double *origin, double *p, double *normal, t_shape *shape);
void	setup_scene(void);
int		setup_camera(char **info);
void	setup_viewport(void);
void	canvas_to_viewport(int x, int y, double *p);
int		trace_ray(double *origin, double *p, int recur);
double	to_rad(int deg);
double	to_deg(double rad);

void	split_canva();
void	draw_canvas();

double	dot(double *v1, double *v2);
void	vec(double *p1, double *p2, double *buff);
double	solve_quadratic(double a, double b, double c, int flag);
double	distance(double *p1, double *p2);
double	vector_size(double *vector);
double	min(double n1, double n2);
void	normalize_vector(double *vector, double *norm);
void	mult_vecs(double factor, double *vec, double *buff);
void	subtract_vecs(double *v1, double *v2, double *buff);
void	translate(double *point, double *vector);
void	cross_product(double *v1, double *v2, double *buf);

t_aux	*get_closest_object(t_aux **lst);
void	add_to_list(double t, int color, t_shape *shape, t_aux **lst);
void	delete_list(t_aux **lst);

void	x_rotate(double *vector, double angle);
void	y_rotate(double *vector, double angle);
void	z_rotate(double *vector, double angle);
void	rotate(double *vector, double *angle);

void	add_back_shape(t_shape *new_shape);

int		add_sphere(char **info);

int		add_plane(char **info);
double	check_hit_plane(void *self, double p[3], double origin[3], int flag);

int		add_cyllinder(char **info);
void	substitute_caps(t_cyllinder *self);

int		add_cone(char **info);

int		end();
void	free_all(int flag);

void	find_point(double t, double *origin, double *p, double *buf);
int		get_color(char *coords, int *colors);
int		array_size(char **array);
int		check_normalized_vector(double *vector);

void	diffuse_reflection(double *colision, double *normal, t_light *cur, double *light);
void	specular_reflection(double *origin, double *colision, double *normal, t_light *cur, double *light, t_shape *shape);
void	get_reflected_ray(double *incoming_ray, double *normal, double *reflected_ray);
int		is_in_shadow(double *colision, t_light *light);

void	free_array(char **array);

#endif
