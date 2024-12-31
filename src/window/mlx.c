/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/31 17:18:05 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_to_mlx(t_data *data)
{
	uint32_t		**img_rgb;
	t_ll			time;

	time = current_timestamp();
	img_rgb = render(data, 0, 0);
	if (!img_rgb)
		exit(er("Failed to render data", NULL));
	fill_image((uint32_t *)data->img->pixels, img_rgb);
	if (!data->img->enabled)
		data->img->enabled = true;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	free_image_all(img_rgb);
	// time = current_timestamp() - time;
	// time /= 100;
}
// printf("Ha tardado en reenderizar: %lld\n", time);

void	fill_image(uint32_t *pixels, uint32_t **img_rgb)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	while (y < W_HG)
	{
		x = 0;
		while (x < W_WH)
		{
			index = y * W_WH+ x;
			pixels[index] = img_rgb[y][x];
			x++;
		}
		y++;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	static bool	mode;
	t_data		*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		last_exit(data);
	else if (keydata.action == MLX_PRESS)
	{
		run_console(data, keydata.key);
		if (keydata.key == MLX_KEY_K)
		{
			pthread_mutex_lock(data->m_trace);
			data->trace_flag = !data->trace_flag;
			pthread_mutex_unlock(data->m_trace);
			if (data->img_last)
				free_image_all(data->img_last);
			data->img_last = NULL;

		}
		if (mode || keydata.key == MLX_KEY_R)
			render_to_mlx(data);
		if (keydata.key == MLX_KEY_R)
			mode = !mode;
	}
}
