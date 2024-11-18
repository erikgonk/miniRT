/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/18 17:15:10 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#define RESET	"\033[0m"
#define BOLD	"\033[1m"
#define RED_BK	"\033[41m" // background
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

#define WINDOW_WIDTH 1580
#define WINDOW_HEIGHT 1080

#define WIDTH 500
#define HEIGHT 500

typedef struct s_v3
{
	float				x;
	float				y;
	float				z;
}			t_v3;

typedef struct s_light
{
    t_v3 				pos;
    float				br;		// brightness
	struct				s_light	*next;
}			t_light;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
}			t_cylinder;

typedef struct s_plane
{
	struct s_plane		*next;
}			t_plane;

typedef struct s_sphere
{
	t_v3				ray_start;
	t_v3				sphere_center;
	float				sphere_radius;
	uint32_t			color;
	struct s_sphere		*next;
}			t_sphere;

typedef struct s_data
{
	t_light				*light;
	t_plane				*pl;
	t_cylinder			*cy;
	t_sphere			*sp;
	struct s_data   	*next;
}			t_data;

// utils
int	er(char *s, char *av);

// lib
t_v3			subtract(t_v3 a, t_v3 b);
float			dot(t_v3 a, t_v3 b);
t_v3			vDefine(float x, float y, float z);

// mlx
void draw_pixel(mlx_image_t* img, int x, int y, uint32_t color);
void my_keyhook(mlx_key_data_t keydata, void* param);

// sphere
void	ft_sphere(t_sphere *sp, t_light *light, mlx_image_t *img);
float sphere_ray_intersect(t_v3 ray_start, t_v3 ray_direction,
		t_v3 sphere_center, float sphere_radius);
// ilumination
int is_in_shadow(t_sphere *sp, t_v3 point, t_light *light);
uint32_t	new_light(t_light *l, t_sphere *sp, t_v3 iPoint);

#endif
