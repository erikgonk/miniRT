/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 18:00:16 by erigonza         ###   ########.fr       */
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

void	ft_init(t_data *data, char **av)
{
	// data->color = ((int)(255) << 16) | ((int)(230) << 8) | (int)(123);
 //    data->sphere_center = vDefine(0.0, 2.0, 0.0);	// Position of the sphere
	data->ray_start = vDefine(0.0, 2.0, -4.0);		// Camera position (where our rays start from)	
 	data->sphere_radius = 1.4;						// Radius (size) of the sphere
    data->sphere_center = vDefine(
        atof(av[1]),  // Sphere X position
        atof(av[2]),  // Sphere Y position
        atof(av[3])   // Sphere Z position
    );

    data->sphere_radius = atof(av[4]);  // Sphere radius
    data->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));
}

// ./miniRT 0.0 1.5 5.0 1.5 230 232 98
int	main(int ac, char **av)
{
	if (ac != 8)
		exit(er("error: 4 args needed", NULL));
	(void)ac;
	t_data			data;
	mlx_t			*mlx;
    mlx_image_t		*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(ft_printf(2, "Failed to create image\n") * 0);

	ft_init(&data, av);
	ft_sphere(&data, img);
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}
