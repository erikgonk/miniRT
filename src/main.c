/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/19 12:45:02 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	(void)ac;
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	t_data			data;
	mlx_t			*mlx;
    mlx_image_t		*img;

	correct_file(av[1]);
	parse(&data, av);
	data.sp = malloc(sizeof(t_sphere));
	data.light = malloc(sizeof(t_light));
	data.pl = malloc(sizeof(t_plane));
	if (!data.sp || !data.light || !data.pl)
		exit(er("error: malloc", NULL));

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(ft_printf(2, "Failed to create image\n") * 0);

	ft_init(&data, av);
	ft_sphere(data.sp, data.light, img);
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}
