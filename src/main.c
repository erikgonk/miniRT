/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/17 11:30:59 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_to_mlx(t_data *data)
{
	uint32_t		**img_rgb;

	img_rgb = render(data, 0, 0);
	if (!img_rgb)
		exit(er("Failed to render scene", NULL));
	fill_image((uint32_t *)data->img->pixels, img_rgb);
	if (!data->img->enabled)
		data->img->enabled = true;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		exit(er("error: failed to allocate memory", NULL));
}

void	validate_args_and_open(int ac, char **av, int *fd)
{
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
		exit(er("error: fd failed", NULL));
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!data->mlx)
		exit(er("Failed to initialize MLX42", NULL));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		exit(er("Failed to create image\n", NULL));
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	init_data(&data);
	validate_args_and_open(ac, av, &fd);
	parse(data, av, fd);
	init_mlx(data);
	render_to_mlx(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}
