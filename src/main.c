/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/02 10:57:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	t_data			*data;
	mlx_t			*mlx;
    mlx_image_t		*img;
	int				fd;
	t_rgb			**img_rgb;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
	parse(data, av, fd);
	data->obj->pos.z = 0;
	print_t_data(data);
	data->obj->sphere_radius = data->obj->size / 2; // size
	data->obj->sphere_center = data->obj->pos;
	// exit(1);

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit (er("Failed to initialize MLX42", NULL));
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(er("Failed to create image\n", NULL));
	img_rgb = render(data, 0, 0);
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_HEIGHT ; j++)
		{
			int	a = get_acolour(0, img_rgb[i][j].r, img_rgb[i][j].g, img_rgb[i][j].b);
			mlx_put_pixel(img, i, j, a);
		}
	}
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
	exit(0);
}
