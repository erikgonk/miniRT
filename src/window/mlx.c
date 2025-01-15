/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/15 04:28:03 by shurtado         ###   ########.fr       */
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

void	swap_mgod(t_data *data)
{
	pthread_mutex_lock(data->m_god);
	data->god = !data->god;
	pthread_mutex_unlock(data->m_god);
}

void	press_keyhook(t_data *data, mlx_key_data_t keydata)
{
	static bool	mode;

	data->last_key = keydata.key;
	if (keydata.key == MLX_KEY_SPACE)
	{
		pthread_mutex_lock(data->m_trace);
		data->trace_flag = !data->trace_flag;
		pthread_mutex_unlock(data->m_trace);
		if (data->img_last)
			free_image_all(data, data->img_last);
		data->img_last = NULL;
		if (mode)
		{
			if (data->god)
				swap_mgod(data);
			data->render_sel = render_one;
			mode = !mode;
		}
		else
		{
			data->render_sel = update_render;
			mode = !mode;
		}
	}
	else if (keydata.key == MLX_KEY_C)
	{
		mode = true;
		if (data->god)
			swap_mgod(data);
		data->render_sel = render_fast;
	}
	else
	{
		if (data->last_render == ONE)
			data->render_sel = render_one;
		else if (data->last_render == FAST)
			data->render_sel = render_fast;
		else if (data->last_render == UPDATE)
			data->render_sel = update_render;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		last_exit(data);
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
