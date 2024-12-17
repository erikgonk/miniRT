/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/17 18:01:08 by shurtado         ###   ########.fr       */
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
# include "console.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define WIDTH WINDOW_WIDTH
# define HEIGHT WINDOW_HEIGHT
# define SP 0
# define PL 1
# define CY 2

//		utils
int					er(char *s, char *av);
t_obj				*new_obj(t_obj *obj);
float				ft_atof(char *str, int i);
float				ft_atof_normi(char *str, int i);
void				objadd_back(t_obj **lst, t_obj *new);

//		parsing
void				parse(t_data *data, char **av, int fd);
void				correct_file(char *name);
//		checker
void				check_end(t_obj *obj, char *str);
void				check_obj(t_obj *obj);
void				check_light(t_alight *aL, t_slight *sL);
void				check_params_acl(t_alight *aL, t_slight *sL, t_cam *cam);
void				check_params(t_data *data);
//		obj
t_obj				*create_obj(t_data *data, char *str, int type);
//		parseACLUtils
int					random_sum_parse(char *str, int i);
void				create_cam(t_data *data, char *str, int type);
void				create_alight(t_data *data, char *str, int type);
void				create_slight(t_slight **s_light, char *str, int type);

//		parse sum to i
int					skip_color(char *str, int i, int j, int flag);
int					skip_floats(char *str, int i, int j, int k);
int					skip_float(char *str, int i, int j, int flag);
int					sum_parse(char *str, int i, int flag, int j);
//		parseUtils
int					type_obj(t_data *data, char *str);
char				*floats_parse(t_obj *obj, char *str, int i, int flag);
int					ft_atoi_parse(char *str, int i, int flag);
t_rgb				colors_parse(char *str);

//		mlx
void				draw_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void				my_keyhook(mlx_key_data_t keydata, void *param);
void				fill_image(uint32_t *pixels, uint32_t **img_rgb);

//		sphere
void				ft_sphere(t_obj *sp, t_slight *light, mlx_image_t *img);
float				sphere_ray_intersect(t_v3 ray_start, t_v3 ray_direction,
						t_v3 sphere_center, float sphere_radius);
//		ilumination
int					is_in_shadow(t_obj *sp, t_v3 point, t_slight *light);
uint32_t			new_light(t_slight *l, t_obj *sp, t_v3 iPoint);

//debug
t_data				*init_example_data(void);
void				print_ambient_light(t_alight *a_light);
void				print_camera(t_cam *cam);
void				print_spot_lights(t_slight *s_light);
void				print_objects(t_obj *obj);
void				print_t_data(t_data *data);
void				print_t_v3(const char *label, t_v3 vec);
void				print_t_rgb(const char *label, t_rgb rgb);

//Main
void				render_to_mlx(t_data *data);

#endif
