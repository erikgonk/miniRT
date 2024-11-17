/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 15:20:42 by erigonza         ###   ########.fr       */
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
}			Vector3;

typedef struct s_data
{
	Vector3	ray_start;
	Vector3	sphere_center;
	float	sphere_radius;
}			t_data;

// lib
Vector3			subtract(Vector3 a, Vector3 b);
float			dot(Vector3 a, Vector3 b);
Vector3			vDefine(float x, float y, float z);

// mlx
void draw_pixel(mlx_image_t* img, int x, int y, uint32_t color);

// sphere
void	ft_sphere(t_data *data, mlx_image_t *img);
float sphere_ray_intersect(Vector3 ray_start, Vector3 ray_direction,
		Vector3 sphere_center, float sphere_radius);

#endif
