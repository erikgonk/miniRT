/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slight_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:19:56 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:43:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	adjust_spot_brightness(keys_t key, t_data *data)
{
	if (key == MLX_KEY_UP && data->s_light->br < SLIGHTMAX)
		data->s_light->br = fminf(data->s_light->br + SLIGHTPLUS, SLIGHTMAX);
	else if (key == MLX_KEY_DOWN && data->s_light->br > SLIGHTMIN)
		data->s_light->br = fmaxf(data->s_light->br - SLIGHTPLUS, SLIGHTMIN);
	else if (key == MLX_KEY_RIGHT && data->s_light->br < SLIGHTMAX)
		data->s_light->br = fminf(data->s_light->br + SLIGHTPLUS, SLIGHTMAX);
	else if (key == MLX_KEY_LEFT && data->s_light->br > SLIGHTMIN)
		data->s_light->br = fmaxf(data->s_light->br - SLIGHTPLUS, SLIGHTMIN);
}

void	adjust_spot_position(keys_t key, t_data *data)
{
	if (key == MLX_KEY_UP)
		data->s_light->pos.y += SPOTPLUS;
	else if (key == MLX_KEY_DOWN)
		data->s_light->pos.y -= SPOTPLUS;
	else if (key == MLX_KEY_LEFT)
		data->s_light->pos.x -= SPOTPLUS;
	else if (key == MLX_KEY_RIGHT)
		data->s_light->pos.x += SPOTPLUS;
	else if (key == MLX_KEY_Z)
		data->s_light->pos.z -= SPOTPLUS;
	else if (key == MLX_KEY_X)
		data->s_light->pos.z += SPOTPLUS;
}

void	manage_spot(keys_t key, t_data *data)
{
	static bool	mode;

	if (key == MLX_KEY_SPACE)
		mode = !mode;
	if (!mode)
		adjust_spot_brightness(key, data);
	else
		adjust_spot_position(key, data);
	print_spot_menu(data);
}
