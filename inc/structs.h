/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:15 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:22:23 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
 * Light Struct
 *		brightness	=> floating point from 0.0 to 1.0
 *		position	=> coordinates of the light point
 *		type		=> light type from enum e_light
 *		color		=> RGB color of the light
 *		next		=> pointer to the next light struct
 */
typedef struct s_light
{
	double			brightness;
	double			position[3];
	int				type;
	int				color[3];
	struct s_light	*next;
}	t_light;

/*
 * Sphere Struct
 *		center	=> coordinates of the center of the sphere
 *		radius	=> radius of the sphere
 */
typedef struct s_sphere
{
	double	center[3];
	double	radius;
}	t_sphere;

/* 
 * Cone Struct
 *		vertix	=> coordinates of the vertix of the cone
 *		axis	=> vector from the vertix to the center of the base
 *		angle	=> angle of the vertix of the cone
 *		height	=> height of the cone
 *		base	=> pointer to the plane instance that makes up the base
 */
typedef struct s_cone
{
	double	vertix[3];
	double	axis[3];
	double	angle;
	double	radius;
	double	height;
	void	*base;
}	t_cone;

/*
 * Plane Struct
 *		point	=> coordinates of a point that is part of the plane
 *		normal	=> vector normal to the plane
 */
typedef struct s_plane
{
	double	point[3];
	double	normal[3];
}	t_plane;

/*
 * Cylinder Struct
 *		center		=> coordinates of the center of the cylinder
 *		radius		=> radius of the bases of the cylinder
 *		axis		=> orientation of the cylinder
 *		height		=> height of the cylinder
 *		top_cap		=> pointer to the plane instance that makes up the top
 *		under_cap	=> pointer to the plane instance that makes up the bottom
 */
typedef struct s_cylinder
{
	double	center[3];
	double	radius;
	double	axis[3];
	double	height;
	void	*top_cap;
	void	*under_cap;
}	t_cylinder;

/*
 * Shape Struct
 *		type		=> type of the shape according to e_type
 *		shape		=> pointer to one of the 4 previous structs, depending on TYPE
 *		check_hit	=> function that checks whether a ray hits the shape
 *		get_normal	=> calculates the normal vector at a point in the surface
 *		color		=> RGB color of the shape
 *		spec		=> factor for the specular reflection of the shape
 *		reflection	=> reflaction factor of the shape, from 0.0 to 1.0
 *		next		=> pointer to the next shape in the scene
 */
typedef struct s_shape
{
	int				type;
	void			*shape;
	double			(*check_hit)(void *self, double point[3], \
					double origin[3], int flag);
	void			(*get_normal)(void *self, double *colision, double *normal);
	int				color[3];
	int				backup_color[3];
	int				spec;
	double			reflection;
	struct s_shape	*next;
}	t_shape;

/*
 * Camera Struct
 *		origin		=> coordinates of the camera
 *		direction	=> vector representing the direction in which the camera is looking
 *		fov			=> field-of-view of the camera in degrees
 */
typedef struct s_cam
{
	double	origin[3];
	double	direction[3];
	int		fov;
}	t_cam;

/*
 * Viewport Struct
 *		height		=> height of the viewport
 *		width		=> width of the viewport
 *		distance	=> distance from the camera to the vpt as a function of the FOV
 */
typedef struct s_vpt
{
	double		height;
	double		width;
	double		distance;
}	t_vpt;

/*
 * Image Struct => normal mlx_img info
 */
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

/*
 * Scene Struct
 *		mlx			=> mlx server
 *		win			=> mlx window
 *		img			=> image struct
 *		camera		=> camera struct
 *		viewport	=> viewport struct
 *		shapes		=> list of shape structs
 *		lights		=> list of light structs
 *		selected	=> currently selected shape
 */
typedef struct s_scene
{
	void	*mlx;
	void	*win;
	t_img	img;

	int		texture;
	int		reflection;
	t_cam	camera;
	t_vpt	viewport;
	t_shape	*shapes;
	t_light	*lights;
	t_shape	*selected;
	t_light	*selected_light;
}	t_scene;

/*
 * Auxiliary Struct
 *		t		=> factor from the ray colision equation
 *		color	=> color of the point in question
 *		self	=> pointer to a shape struct
 *		next	=> next node of the list
 */
typedef struct s_aux
{
	double			t;
	int				color;
	t_shape			*self;
	struct s_aux	*next;
}	t_aux;

typedef struct s_lightaux
{
	double	light[3];
	double	normal[3];
	double	colision[3];
}	t_lightaux;

typedef struct s_specaux
{
	double	l[3];
	double	r[3];
	double	v[3];
	double	ln[3];
	double	lp[3];
}	t_specaux;

typedef struct s_rayaux
{
	int		local_color;
	int		reflected_color;
	double	new_origin[3];
	double	new_p[3];
	double	reflected_ray[3];
	double	incoming_ray[3];
	double	normal[3];
	t_aux	*closest;
}	t_rayaux;

#endif
