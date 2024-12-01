/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/01 15:34:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	t_data			*data;
	mlx_t			*mlx;
    mlx_image_t		*img;
	int				fd;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
	parse(data, av, fd);
	printf("%f, %f, %f %f, %f, %f %f, %f %hhu, %hhu, %hhu\n", data->obj->pos.x, data->obj->pos.y, data->obj->pos.z, data->obj->axis.x, data->obj->axis.y, data->obj->axis.z, data->obj->size, data->obj->height, data->obj->rgb.r, data->obj->rgb.g, data->obj->rgb.b);
	printf("%f %hhu, %hhu, %hhu\n", data->aLight->br, data->aLight->rgb.r, data->aLight->rgb.g, data->aLight->rgb.b);
	printf("%f %f %f %f %f %f %d\n", data->cam->pos.x, data->cam->pos.y, data->cam->pos.z, data->cam->axis.x, data->cam->axis.y, data->cam->axis.z, data->cam->fov);
	printf("%f %f %f %f %hhu, %hhu, %hhu\n", data->sLight->pos.x, data->sLight->pos.y, data->sLight->pos.z, data->sLight->br, data->sLight->rgb.r, data->sLight->rgb.g, data->sLight->rgb.b);
	exit (er("salio bien\n", NULL));
	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit (er("Failed to initialize MLX42", NULL));

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(er("Failed to create image\n", NULL));
	// ft_init(&data, av);
	// obj = data->obj;
	// while (obj)
	// {
	// 	// organizator(obj);
	// 	ft_sphere(data->obj, data->sLight, img);
	// 	obj = obj->next;
	// }
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
	exit(0);
}
