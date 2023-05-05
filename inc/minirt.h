/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:12 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/05 10:46:34 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <pthread.h>

# include "../lib/libft/inc/libft.h"
# include "../lib/mlx_linux/mlx.h"
# include "macros.h"
# include "structs.h"
# include "enums.h"

extern t_scene	g_scene;

//////////////////////////////
/********** SETUP ***********/
//////////////////////////////

/********* parser.c *********/
int		parsing_error(char *str);
void	parser(int argc, char **argv);

/********** setup.c *********/
int		setup_camera(char **info);
void	setup_scene(void);
void	setup_viewport(void);
void	canvas_to_viewport(int x, int y, double *p);
void	verify_parse(int *error);
int		is_zero(double n);

/********** draw.c **********/
void	draw_canvas(void);
void	split_canva(void);

/****** instructions.c ******/
void	print_instructions(void);
void	print_resize(void);
void	print_surface(void);
void	print_rotations(void);
void	print_movements(void);
void	print_general_instructions(void);

//////////////////////////////
/********** SHAPES **********/
//////////////////////////////

/********** cone.c **********/
int		add_cone(char **info);
void	substitute_cone_base(t_cone *cone);
double	check_hit_cone(void *self, double p[3], double origin[3], int flag);

/******** cylinder.c ********/
int		add_cylinder(char **info);
double	find_t(double *t);
double	check_hit_cylinder(void *self, double p[3], double origin[3], int flag);
void	add_caps(t_cylinder *self);
void	substitute_caps(t_cylinder *self);

/******** cylinder2.c *******/
int		check_plane(t_plane *plane, t_cylinder *self, \
		double *point, double *normal);
double	check_height(t_cylinder *self, double t, double *origin, \
		double *vector);
double	check_width(t_cylinder *self, double t, double *origin, \
		double *vector);
void	side_normal(t_cylinder *self, double *point, double *normal);
void	get_normal_cylinder(void *self, double *colision, double *normal);

/********** plane.c *********/
int		add_plane(char **info);
int		check_side(double *light, t_plane *plane);
double	check_hit_plane(void *self, double p[3], double origin[3], int flag);

/********* shapes.c *********/
void	add_back_shape(t_shape *new_shape);
int		inside_cone(void *self, double *point);
int		inside_cylinder(void *self, double *point);
int		inside_sphere(void *self, double *point);
int		inside_plane(void *self, double *point);

/********* sphere.c *********/
int		add_sphere(char **info);

//////////////////////////////
/********** ENGINE **********/
//////////////////////////////

/********* lights.c *********/
int		light_setup(char **info, int flag);
void	determine_light(t_lightaux *lightaux, double *origin, t_shape *shape);

/********** ray.c ***********/
int		trace_ray(double *origin, double *p, int recur);

/******* reflections.c ******/
void	diffuse_reflection(t_lightaux *lightaux, t_light *cur);
void	specular_reflection(t_lightaux *lightaux, double *origin, \
		t_light *cur, t_shape *shape);

/********* shadows.c ********/
int		is_in_shadow(double *colision, t_light *light, t_shape *shape);

/********* texture.c ********/
void	apply_texture(int *buff);

//////////////////////////////
/********** EVENTS **********/
//////////////////////////////

/********* events.c *********/
int		key_press(int keycode);
int		select_piece(int button, int x, int y);

/****** light_events.c ******/
void	change_light(void);
void	move_light(double *movement);

/****** other_events.c ******/
void	change_texture(void);
void	change_reflection(void);
void	change_depth(int keycode);

/****** resize_events.c *****/
void	change_shape_size(int keycode);

//////////////////////////////
/*********** UTILS **********/
//////////////////////////////

/******* free_utils.c *******/
int		end(void);
void	free_all(int flag);
void	free_array(char **array);
void	error_handler(void);
void	is_error(int error);

/******* setup_utils.c ******/

void	set_vectors(double *w_vector, double *h_vector);

/******* list_utils.c *******/
void	delete_list(t_aux **lst);
void	add_to_list(double t, int color, t_shape *shape, t_aux **lst);
t_aux	*get_closest_object(t_aux **lst);

/******* math_utils.c *******/
double	to_rad(int deg);
double	to_deg(double rad);
double	min(double n1, double n2);
double	distance(double *p1, double *p2);
double	solve_quadratic(double a, double b, double c, int flag);

/******** vec_utils.c *******/
int		array_size(char **array);
double	dot(double *v1, double *v2);
double	vector_size(double *vector);
void	vec(double *p1, double *p2, double *buff);
void	normalize_vector(double *vector, double *norm);

/******* vec_utils2.c *******/
void	translate(double *point, double *vector);
void	add_vecs(double *v1, double *v2, double *buff);
void	cross_product(double *v1, double *v2, double *buf);
void	mult_vecs(double factor, double *vec, double *buff);
void	subtract_vecs(double *v1, double *v2, double *buff);

/***** rotation_utils.c *****/
void	rotate(double *vector, double *angle);
void	apply_translation_and_rotation(t_shape *selected, double *vector, \
		double *angle);

/******* color_utils.c ******/
int		get_color(char *coords, int *colors);
int		rgb_to_color(int *rgb, double *light);
int		get_full_color(int local_color, int reflected_color, double r);
void	apply_selection_color(void);
void	copy_color(int *original, int *copy);

/********** utils.c *********/
int		check_normalized_vector(double *vector);
int		coords_interpreter(char *coords, double *point);
void	find_point(double t, double *origin, double *p, double *buf);
void	get_reflected_ray(double *incoming_ray, double *normal, \
		double *reflected_ray);

#endif
