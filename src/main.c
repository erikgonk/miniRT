/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 17:13:42 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	er(char *s, char *argv)
{
	while (*s)
		write(2, s++, 1);
	if (argv)
		while (*argv)
			write(2, argv++, 1);
	write(2, "\n", 1);
	return (1);
}

void	ft_init(t_data *data)
{
	data->ray_start = vDefine(0.0, 2.0, -4.0);		// Camera position (where our rays start from)	
    data->sphere_center = vDefine(0.0, 2.0, 0.0);	// Position of the sphere
    data->sphere_radius = 1.4;						// Radius (size) of the sphere
	data->color = ((int)(255) << 16) | ((int)(230) << 8) | (int)(123);
}

int	main(int ac, char **av)
{
	// if (ac != 4)
	// 	exit(er("error: 4 args needed", NULL));
	(void)ac;
	(void)av;
	t_data			data;
	mlx_t			*mlx;
    mlx_image_t		*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);

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
