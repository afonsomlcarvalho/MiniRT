#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/mlx_linux/mlx.h"
# include <math.h>

# define X 0
# define Y 1
# define Z 2

# define WIDTH 400
# define HEIGHT 400

typedef struct s_object
{
	int			color;
	float		point[3];
	int			radius;
	int			height;
	float		vector[3];
	int			(*is_object)(struct s_object *self, float x, float y, float z);
	struct s_object	*next;
}				t_object;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*path;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img;

typedef	struct	s_cam
{
	float	position[3];
	float	direction[3];
	int		FOV;
}				t_cam;

typedef	struct	s_viewport
{
	float	width;
	float	height;
}				t_viewport;

typedef struct	s_all
{
	void		*mlx;
	void		*wind;
	t_img		canva;
	t_cam		cam;
	t_viewport	viewport;
	t_object	*objects;
}				t_all;


t_all	*all(void);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	add_sphere(float x, float y, float z, float radius, int color);
#endif