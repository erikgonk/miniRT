/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/02 10:30:59 by shurtado         ###   ########.fr       */
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
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"
# include "libvct.h"
# include "data.h"
# include "render.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define WIDTH 500
# define HEIGHT 500
# define SP 0
# define PL 1
# define CY 2

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

//debug
void				print_t_data(t_data *data);

#endif
