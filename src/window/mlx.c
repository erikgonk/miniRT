/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/13 11:04:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_to_mlx(t_data *data)
{
	uint32_t	**img_rgb;
	t_ll		time;

	time = current_timestamp();
	img_rgb = render(data);
	if (!img_rgb)
		exit(er(data, "Failed to render data", NULL));
	fill_image(data, (uint32_t *)data->img->pixels, img_rgb);
	if (!data->img->enabled)
		data->img->enabled = true;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	free_image_all(data, img_rgb);
}

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

void	press_keyhook(t_data *data, mlx_key_data_t keydata, bool mode)
{
	run_console(data, keydata.key);
	if (keydata.key == MLX_KEY_K)
	{
		pthread_mutex_lock(data->m_trace);
		data->trace_flag = !data->trace_flag;
		pthread_mutex_unlock(data->m_trace);
		if (data->img_last)
			free_image_all(data, data->img_last);
		data->img_last = NULL;
	}
	if (mode || keydata.key == MLX_KEY_R)
		render_to_mlx(data);
	if (keydata.key == MLX_KEY_R)
		mode = !mode;
	if (keydata.key == MLX_KEY_L)
	{
		pthread_mutex_lock(data->m_god);
		data->god = !data->god;
		pthread_mutex_unlock(data->m_god);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	static bool	mode;
	t_data		*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		last_exit(data);
	}
	else if (keydata.action == MLX_PRESS)
		press_keyhook(data, keydata, mode);
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
}
