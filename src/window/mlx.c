/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/21 21:11:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	fill_image(t_data *data, uint32_t *pixels, uint32_t **img_rgb)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	while (y < data->y)
	{
		x = 0;
		while (x < data->x)
		{
			index = y * data->x + x;
			pixels[index] = img_rgb[y][x];
			x++;
		}
		y++;
	}
}

bool	press_keyhook_normi(t_data *data, mlx_key_data_t keydata, bool mode)
{
	if (keydata.key == MLX_KEY_C)
	{
		mode = true;
		if (data->god)
			swap_mgod(data);
		data->render_sel = render_fast;
	}
	else
		set_last(data);
	return (mode);
}

void	press_keyhook(t_data *data, mlx_key_data_t keydata)
{
	static bool	mode;

	if (keydata.key == MLX_KEY_SPACE)
	{
		if (data->last_render != FAST)
			mode = !mode;
		swap_flag_mlx(data);
		if (data->img_last)
			free_image_all(data, data->img_last);
		data->img_last = NULL;
		if (!mode)
		{
			if (data->god)
				swap_mgod(data);
			data->render_sel = render_one;
		}
		else
			data->render_sel = update_render;
	}
	else if (keydata.key == MLX_KEY_C)
		mode = press_keyhook_normi(data, keydata, mode);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(data->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (keydata.action == MLX_PRESS)
		press_keyhook(data, keydata);
}

void	resise_w(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	(void)width;
	(void)height;
	data = param;
	pthread_mutex_lock(data->m_god);
	data->god = false;
	data->img_last = NULL;
	pthread_mutex_unlock(data->m_god);
	if (data->last_render == ONE)
		data->render_sel = render_one;
	else if (data->last_render == FAST)
		data->render_sel = render_fast;
	else if (data->last_render == UPDATE)
		data->render_sel = update_render;
}
