/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/01 19:11:03 by shurtado         ###   ########.fr       */
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
# include "../lib/libvector/libvct.h"
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
# define SP 0
# define PL 1
# define CY 2

// t_rgb[800][600] image;

typedef struct s_rgb
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
}					t_rgb;

typedef struct s_cam
{
	t_v3			pos;
	int				fov;
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
	int				i;			// just to use it on the parser
	char			type;		// in case I want to separate the parser and the exec
	t_v3			pos;		// cp pl cy
	t_v3			axis;		// pl cy | orientation
	t_rgb			rgb;		// sp pl cy
	float			size;		// sp radius | cy diameter
	float			height;		// cy
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
}					t_data;

//		utils
int					er(char *s, char *av);
t_obj				*newObj(t_obj *obj);
float				ft_atof(char *str, int i);
float				ft_atof_normi(char *str, int i);
void				objadd_back(t_obj **lst, t_obj *new);

//		parsing
void				parse(t_data *data, char **av, int fd);
void				correct_file(char *name);

//		parseACLUtils
// void				createACL(t_data *data, char *str, int type);

void				createCam(t_data *data, char *str, int type);
void				createALight(t_data *data, char *str, int type);
void				createSLight(t_data *data, char *str, int type);

//		parse sum to i
int					skipColor(char *str, int i, int j, int flag);
int					skipFloats(char *str, int i, int j, int k);
int					skipFloat(char *str, int i, int j);
int					sumParse(char *str, int i, int flag, int j);
//		parseUtils
int					checkObj(t_data *data, char *str);
char				*floatsParse(t_obj *obj, char *str, int i, int flag);
int					ft_atoiParse(char *str, int i, int flag);
t_rgb				colorsParse(char *str);
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
