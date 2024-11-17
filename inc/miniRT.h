/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 17:59:50 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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
	float	x;
	float	y;
	float	z;
}			t_v3;

typedef struct s_data
{
	t_v3		ray_start;
	t_v3		sphere_center;
	float		sphere_radius;
	uint32_t	color;
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
void	ft_sphere(t_data *data, mlx_image_t *img);
float sphere_ray_intersect(t_v3 ray_start, t_v3 ray_direction,
		t_v3 sphere_center, float sphere_radius);

#endif
