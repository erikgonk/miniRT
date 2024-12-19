/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 13:49:18 by shurtado         ###   ########.fr       */
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
# include <sys/time.h>
# include "libft.h"
# include "libvct.h"
# include "data.h"
# include "render.h"
# include "console.h"
# include "parser.h"
# include "debug.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define WIDTH WINDOW_WIDTH
# define HEIGHT WINDOW_HEIGHT
# define SP 0
# define PL 1
# define CY 2

typedef long long	t_ll;

//		mlx
void				draw_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void				my_keyhook(mlx_key_data_t keydata, void *param);
void				fill_image(uint32_t *pixels, uint32_t **img_rgb);

//Main
void				render_to_mlx(t_data *data);

#endif
