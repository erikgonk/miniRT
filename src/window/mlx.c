/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/17 11:12:03 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	fill_image(uint32_t *pixels, uint32_t **img_rgb)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			index = y * WINDOW_WIDTH + x;
			pixels[index] = img_rgb[y][x];
			x++;
		}
		y++;
	}
}

void	draw_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		mlx_put_pixel(img, x, y, color);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	static bool	mode;

	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
	else if (keydata.action == MLX_PRESS)
	{
		run_console((t_data *) param, keydata.key);
		if (mode || keydata.key == MLX_KEY_R)
			render_to_mlx((t_data *) param);
		if (keydata.key == MLX_KEY_R)
			mode = !mode;
	}
}
