/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submenu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:57:09 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/09 18:57:36 by shurtado         ###   ########.fr       */
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
	//meter aqui funcion de re-reenderizar
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
			data->cam->pos.y = fminf(data->cam->pos.y + CAMAXISP, CAMAXISMAX);
		else if (key == MLX_KEY_DOWN)
			data->cam->pos.y = fmaxf(data->cam->pos.y - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_LEFT)
			data->cam->pos.x = fmaxf(data->cam->pos.x - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_RIGHT)
			data->cam->pos.x = fminf(data->cam->pos.x + CAMAXISP, CAMAXISMAX);
		else if (key == MLX_KEY_Z)
			data->cam->pos.z = fmaxf(data->cam->pos.z - CAMAXISP, CAMAXISMIN);
		else if (key == MLX_KEY_X)
			data->cam->pos.z = fminf(data->cam->pos.z + CAMAXISP, CAMAXISMAX);
	}
	//meter aqui funcion de re-reenderizar
	print_cam_menu(data);
}

void	manage_spot(keys_t key, t_data *data)
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
	//meter aqui funcion de re-reenderizar
}

void	manage_obj(keys_t key, t_data *data)
{
	if (key == MLX_KEY_UP)
		data->obj->pos.y += OBJPLUS;
	else if (key == MLX_KEY_DOWN)
		data->obj->pos.y -= OBJPLUS;
	else if (key == MLX_KEY_LEFT)
		data->obj->pos.x -= OBJPLUS;
	else if (key == MLX_KEY_RIGHT)
		data->obj->pos.x += OBJPLUS;
	else if (key == MLX_KEY_Z)
		data->obj->pos.z -= OBJPLUS;
	else if (key == MLX_KEY_X)
		data->obj->pos.z += OBJPLUS;
	//meter aqui funcion de re-reenderizar
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
}
