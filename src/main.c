/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/09 19:51:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	t_data			*data;
	int				fd;
	uint32_t		**img_rgb;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
	parse(data, av, fd);

	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!data->mlx)
		exit (er("Failed to initialize MLX42", NULL));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		exit(er("Failed to create image\n", NULL));
	}
	img_rgb = render(data, 0, 0);
	if (!img_rgb)
		exit(er("Failed to render scene", NULL));
	fill_image((uint32_t *)data->img->pixels, img_rgb);
	data->img->enabled = true;
	run_console(data, MLX_KEY_0);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}
