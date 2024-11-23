/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/23 15:23:57 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED_BK "\033[41m" // background
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

# define WINDOW_WIDTH 1580
# define WINDOW_HEIGHT 1080

# define WIDTH 500
# define HEIGHT 500

# define SP 32
# define PL 33
# define CY 34

typedef struct s_v3
{
	float			x;
	float			y;
	float			z;
}					t_v3;

typedef struct s_rgb
{
	char			r;
	char			g;
	char			b;
}					t_rgb;

typedef struct s_cam
{
	int				fov;
	t_v3			pos;
	t_v3			axis; // orientation
}					t_cam;

typedef struct s_aLight
{
	float			br; // brightness
	t_rgb			rgb;
}					t_aLight;

typedef struct s_sLight
{
	t_v3			pos;
	float			br; // brightness
	t_rgb			rgb;
	struct s_light	*next;
}					t_sLight;

typedef struct s_obj
{
	uint32_t		color;
	char			type;
	t_v3			pos;
	t_v3			axis; // orientation pl & cy
	t_rgb			rgb;
//	
	float			sphere_radius; // size
	t_v3			ray_start; // Camera position
	t_v3			sphere_center;
	struct s_obj	*next;
}					t_obj;

typedef struct s_data
{
	t_aLight		*aLight;
	t_cam			*cam;
	t_sLight		*sLight;
	t_obj			*obj;
	struct s_data	*next;
}					t_data;

//		utils
int					er(char *s, char *av);
t_obj				*newObj(t_obj *obj);
float				ft_atof(char *str, int i);
float				ft_atof_normi(char *str, int i);

//		parsing
t_obj				*parse(t_data *data, t_obj *obj, char **av, int fd);
void				correct_file(char *name);

//		lib
t_v3				subtract(t_v3 a, t_v3 b);
float				dot(t_v3 a, t_v3 b);
t_v3				vDefine(float x, float y, float z);

//		mlx
void				draw_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void				my_keyhook(mlx_key_data_t keydata, void *param);

//		sphere
void				ft_sphere(t_obj *sp, t_sLight *light, mlx_image_t *img);
float				sphere_ray_intersect(t_v3 ray_start, t_v3 ray_direction,
						t_v3 sphere_center, float sphere_radius);
//		ilumination
int					is_in_shadow(t_obj *sp, t_v3 point, t_sLight *light);
uint32_t			new_light(t_sLight *l, t_obj *sp, t_v3 iPoint);

#endif
