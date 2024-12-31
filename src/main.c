/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/31 17:20:37 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	last_exit(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	update_render(void *param)
{
	t_data				*data;
	uint32_t			**new_img;
	uint32_t			**avrg;
	t_ll				time;

	time = current_timestamp();
	data = (t_data *)param;
	if (!data->img_last)
		data->img_last = render(data, W_WH, W_HG);
	if (!data->img->enabled)
		data->img->enabled = true;
	new_img = render(data, W_WH, W_HG);
	avrg = average_samples((uint32_t **)data->img_last, new_img);
	fill_image((uint32_t *)data->img->pixels, avrg);
	free_image_all(avrg);
	mlx_image_to_window(data->mlx, data->img, 0 ,0);
	time = current_timestamp() - time;
	printf("%lld\n", time /= 100);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	srand((unsigned int) current_timestamp());
	init_data(&data);
	validate_args_and_open(ac, av, &fd);
	parse(data, fd);
	close(fd);
	init_all(data);
	data->img_last = NULL;
	// render_to_mlx(data);
	mlx_loop_hook(data->mlx, update_render, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
}
