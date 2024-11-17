/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 16:58:58 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// Draw a single pixel at position (x, y) with the specified color if within bounds
void draw_pixel(mlx_image_t* img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        mlx_put_pixel(img, x, y, color);			// Draw the pixel
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
}
