/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 16:59:40 by shurtado         ###   ########.fr       */
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
		exit(er("Failed to render scene", NULL));
	fill_image((uint32_t *)data->img->pixels, img_rgb);
	if (!data->img->enabled)
		data->img->enabled = true;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	free_image_all(img_rgb);
	time = current_timestamp() - time;
	time /= 100;
	printf("Ha tardado en reenderizar: %lld\n", time);
}

void	fill_image(uint32_t *pixels, uint32_t **img_rgb)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			index = y * WINDOW_WIDTH + x;
			pixels[index] = img_rgb[y][x];
			x++;
		}
		y++;
	}
}

void	free_data(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	free(data->cam);
	free(data->s_light);
	free(data->a_light);
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
	if (data)
		free(data);
}

void	last_exit(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	static bool	mode;

	if (keydata.key == MLX_KEY_ESCAPE)
		last_exit(param);
	else if (keydata.action == MLX_PRESS)
	{
		run_console((t_data *) param, keydata.key);
		if (mode || keydata.key == MLX_KEY_R)
			render_to_mlx((t_data *) param);
		if (keydata.key == MLX_KEY_R)
			mode = !mode;
	}
}
