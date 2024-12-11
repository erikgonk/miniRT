/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submenu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:57:09 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/11 10:22:38 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	manage_alight(keys_t key, t_data *data)
{
	if (key == MLX_KEY_UP && data->aLight->br < ALIGHTMAX)
		data->aLight->br = fminf(data->aLight->br + ALIGHTPLUS, ALIGHTMAX);
	else if (key == MLX_KEY_DOWN && data->aLight->br > ALIGHTMIN)
		data->aLight->br = fmaxf(data->aLight->br - ALIGHTPLUS, ALIGHTMIN);
	print_alight_menu(data);
}

void	manage_cam(keys_t key, t_data *data)
{
	static bool	mode;

	if (key == MLX_KEY_SPACE)
		mode = !mode;
	if (!mode)
	{
		if (key == MLX_KEY_UP)
			data->cam->pos.y += CAMPLUS;
		else if (key == MLX_KEY_DOWN)
			data->cam->pos.y -= CAMPLUS;
		else if (key == MLX_KEY_LEFT)
			data->cam->pos.x -= CAMPLUS;
		else if (key == MLX_KEY_RIGHT)
			data->cam->pos.x += CAMPLUS;
		else if (key == MLX_KEY_Z)
			data->cam->pos.z -= CAMPLUS;
		else if (key == MLX_KEY_X)
			data->cam->pos.z += CAMPLUS;
	}
	else
	{
		if (key == MLX_KEY_UP)
			data->cam->axis.y = fminf(data->cam->axis.y + CAMAXISP, CAMAXISMAX);
		else if (key == MLX_KEY_DOWN)
			data->cam->axis.y = fmaxf(data->cam->axis.y - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_LEFT)
			data->cam->axis.x = fmaxf(data->cam->axis.x - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_RIGHT)
			data->cam->axis.x = fminf(data->cam->axis.x + CAMAXISP, CAMAXISMAX);
		else if (key == MLX_KEY_Z)
			data->cam->axis.z = fmaxf(data->cam->axis.z - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_X)
			data->cam->axis.z = fminf(data->cam->axis.z + CAMAXISP, CAMAXISMAX);
	}
	print_cam_menu(data);
}

void	manage_spot(keys_t key, t_data *data)
{
	static bool	mode;

	if (key == MLX_KEY_SPACE)
		mode = !mode;
	if (!mode)
	{
		if (key == MLX_KEY_UP && data->sLight->br < SLIGHTMAX)
			data->sLight->br = fminf(data->sLight->br + SLIGHTPLUS, SLIGHTMAX);
		else if (key == MLX_KEY_DOWN && data->sLight->br > SLIGHTMIN)
			data->sLight->br = fmaxf(data->sLight->br - SLIGHTPLUS, SLIGHTMIN);
		else if (key == MLX_KEY_RIGHT && data->sLight->br < SLIGHTMAX)
			data->sLight->br = fminf(data->sLight->br + SLIGHTPLUS, SLIGHTMAX);
		else if (key == MLX_KEY_LEFT && data->sLight->br > SLIGHTMIN)
			data->sLight->br = fmaxf(data->sLight->br - SLIGHTPLUS, SLIGHTMIN);
	}
	else
	{
		if (key == MLX_KEY_UP)
			data->sLight->pos.y += SPOTPLUS;
		else if (key == MLX_KEY_DOWN)
			data->sLight->pos.y -= SPOTPLUS;
		else if (key == MLX_KEY_LEFT)
			data->sLight->pos.x -= SPOTPLUS;
		else if (key == MLX_KEY_RIGHT)
			data->sLight->pos.x += SPOTPLUS;
		else if (key == MLX_KEY_Z)
			data->sLight->pos.z -= SPOTPLUS;
		else if (key == MLX_KEY_X)
			data->sLight->pos.z += SPOTPLUS;
	}
	print_spot_menu(data);
}

void	manage_obj(keys_t key, t_data *data)
{
	static bool			mode;
	static t_obj		*obj;

	if (!obj)
		obj = data->obj;
	if (key == MLX_KEY_N)
	{
		if (obj->next)
			obj = obj->next;
		else
			obj = data->obj;
	}
	if (key == MLX_KEY_SPACE)
		mode = !mode;
	if (!mode)
	{
		if (key == MLX_KEY_UP)
			obj->pos.y += OBJPLUS;
		else if (key == MLX_KEY_DOWN)
			obj->pos.y -= OBJPLUS;
		else if (key == MLX_KEY_LEFT)
			obj->pos.x -= OBJPLUS;
		else if (key == MLX_KEY_RIGHT)
			obj->pos.x += OBJPLUS;
		else if (key == MLX_KEY_Z)
			obj->pos.z -= OBJPLUS;
		else if (key == MLX_KEY_X)
			obj->pos.z += OBJPLUS;
	}
	else
	{
		if (key == MLX_KEY_UP)
			obj->axis.y = fminf(obj->axis.y + OBJAXISP, OBJAXISMAX);
		else if (key == MLX_KEY_DOWN)
			obj->axis.y = fmaxf(obj->axis.y - OBJAXISP, OBJAXISMIN);
		else if (key == MLX_KEY_LEFT)
			obj->axis.x = fmaxf(obj->axis.x - OBJAXISP, OBJAXISMIN);
		else if (key == MLX_KEY_RIGHT)
			obj->axis.x = fminf(obj->axis.x + OBJAXISP, OBJAXISMAX);
		else if (key == MLX_KEY_Z)
			obj->axis.z = fmaxf(obj->axis.z - OBJAXISP, OBJAXISMIN);
		else if (key == MLX_KEY_X)
			obj->axis.z = fminf(obj->axis.z + OBJAXISP, OBJAXISMAX);
	}
	print_obj_menu(data);
}

void	manage_submenu(keys_t key, int option, t_data *data)
{
	if (option == 0)
		manage_alight(key, data);
	else if (option == 1)
		manage_cam(key, data);
	else if (option == 2)
		manage_spot(key, data);
	else if (option == 3)
		manage_obj(key, data);
	render_to_mlx(data);
}
