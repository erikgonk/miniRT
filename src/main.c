/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 06:16:08 by shurtado         ###   ########.fr       */
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

void	render_one(void *param)
{
	t_data		*data;
	uint32_t	**new_img;

	data = (t_data *)param;
	data->x = data->mlx->width;
	data->y = data->mlx->height;
	data->god = true;
	mlx_resize_image(data->img, data->x, data->y);
	new_img = render(data, 1);
	fill_image(data, (uint32_t *)data->img->pixels, new_img);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	free_image_all(data, new_img);
	data->render_sel = NULL;
	data->last_render = ONE;
}

void	render_fast(void *param)
{
	t_data		*data;
	uint32_t	**new_img;

	data = (t_data *)param;
	data->x = data->mlx->width;
	data->y = data->mlx->height;
	data->god = true;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->x, data->y);
	new_img = console_render(data);
	fill_image(data, (uint32_t *)data->img->pixels, new_img);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	free_image_all(data, new_img);
	run_console(data);
}

void	update_render(void *param)
{
	t_data		*data;
	uint32_t	**new_img;
	uint32_t	**avrg;
	t_ll		time;

	time = current_timestamp();
	data = (t_data *)param;
	data->x = data->mlx->width;
	data->y = data->mlx->height;
	data->god = true;
	mlx_resize_image(data->img, data->x, data->y);
	if (!data->img_last)
		data->img_last = render(data, 0);
	if (!data->img->enabled)
		data->img->enabled = true;
	new_img = render(data, 0);
	avrg = average_samples(data, (uint32_t **)data->img_last, new_img);
	fill_image(data, (uint32_t *)data->img->pixels, avrg);
	free_image_all(data, avrg);
	free_image_all(data, new_img);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	time = current_timestamp() - time;
	data->last_render = UPDATE;
}

void	call_render(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (data->render_sel)
		data->render_sel(param);

}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	srand((unsigned int)mlx_get_time());
	init_data(&data);
	validate_args_and_open(data, ac, av, &fd);
	parse(data, fd);
	close(fd);
	init_all(data);
	data->render_sel = render_fast;
	mlx_resize_hook(data->mlx, &resise_w, data);
	mlx_loop_hook(data->mlx, call_render, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
}
