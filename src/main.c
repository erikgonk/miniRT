/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 18:13:55 by erigonza         ###   ########.fr       */
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

void	call_render(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (data->render_sel)
		data->render_sel(param);
}

void	mouse_click(mouse_key_t button, action_t action, \
						modifier_key_t mods, void *param)
{
	t_data		*data;
	int			x;
	int			y;

	(void)button;
	(void)mods;
	data = param;
	if (action == 1)
	{
		if (data->last_render != FAST)
			data->render_sel = render_fast;
		mlx_get_mouse_pos(data->mlx, &x, &y);
		console_click(data, x, y);
	}
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
	init_mlx(data);
	init_all(data);
	data->render_sel = render_fast;
	mlx_resize_hook(data->mlx, &resise_w, data);
	mlx_loop_hook(data->mlx, call_render, data);
	mlx_mouse_hook(data->mlx, mouse_click, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
}
