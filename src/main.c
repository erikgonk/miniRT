/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/16 19:39:16 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#define WINDOW_WIDTH 1580
#define WINDOW_HEIGHT 1080

#define WIDTH 500
#define HEIGHT 500

t_v3	vDefine(float x, float y, float z)
{
	t_v3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
}

int	main(int ac, char **av)
{
	mlx_t	*mlx;
    mlx_image_t		*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		return ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img) {
        fprintf(stderr, "Failed to create image\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}
