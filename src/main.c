/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 13:13:43 by erigonza         ###   ########.fr       */
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

void	ft_init(t_data *data)
{
	data->ray_start = vDefine(0.0, 0.0, -5.0);		// Camera position (where our rays start from)	
    data->sphere_center = vDefine(0.0, 0.0, 0.0);   // Position of the sphere
    data->sphere_radius = 1.4;                   // Radius (size) of the sphere
}

int	main(int ac, char **av)
{
	t_data			data;
	mlx_t			*mlx;
    mlx_image_t		*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		return ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(ft_printf(2, "Failed to create image\n") * 0);

	ft_init(&data);
	ft_sphere(&data, img);
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}
