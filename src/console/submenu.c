/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submenu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:57:09 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 00:44:56 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	manage_alight(keys_t key, t_data *data)
{
	static float quantity;
	
	if (quantity < 0.01f)
		quantity = ALIGHTPLUS;
	if (key == MLX_KEY_UP && data->aLight->br < ALIGHTMAX)
		data->aLight->br = fminf(data->aLight->br + quantity, ALIGHTMAX);
	else if (key == MLX_KEY_DOWN && data->aLight->br > ALIGHTMIN)
		data->aLight->br = fmaxf(data->aLight->br - quantity, ALIGHTMIN);
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		quantity = fmaxf(quantity - 0.01f, 0.01);
	else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
		quantity += 0.01f;
	print_alight_menu(data);
	printf("\nincrementos = %f\n", quantity);
}

void	manage_cam(keys_t key, t_data *data)
{
	static bool		mode;
	static float	posq;
	static float	axisq;

	if (posq < 1.0f)
		posq = CAMPLUS;
	if (axisq < 0.01f)
		axisq = CAMAXISP;
	if (key == MLX_KEY_SPACE)
		mode = !mode;
	if (!mode)
	{
		if (key == MLX_KEY_UP)
			data->cam->pos.y += posq;
		else if (key == MLX_KEY_DOWN)
			data->cam->pos.y -= posq;
		else if (key == MLX_KEY_LEFT)
			data->cam->pos.x -= posq;
		else if (key == MLX_KEY_RIGHT)
			data->cam->pos.x += posq;
		else if (key == MLX_KEY_Z)
			data->cam->pos.z -= posq;
		else if (key == MLX_KEY_X)
			data->cam->pos.z += posq;
		else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
			posq = fmaxf(1.0f, posq -1);
		else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
			posq = fminf(100, posq + 1);

	}
	else
	{
		if (key == MLX_KEY_UP)
			data->cam->axis.y = fminf(data->cam->axis.y + axisq, CAMAXISMAX);
		else if (key == MLX_KEY_DOWN)
			data->cam->axis.y = fmaxf(data->cam->axis.y - axisq, CAMAXISMIN);
		else if (key == MLX_KEY_LEFT)
			data->cam->axis.x = fmaxf(data->cam->axis.x - axisq, CAMAXISMIN);
		else if (key == MLX_KEY_RIGHT)
			data->cam->axis.x = fminf(data->cam->axis.x + axisq, CAMAXISMAX);
		else if (key == MLX_KEY_Z)
			data->cam->axis.z = fmaxf(data->cam->axis.z - axisq, CAMAXISMIN);
		else if (key == MLX_KEY_X)
			data->cam->axis.z = fminf(data->cam->axis.z + axisq, CAMAXISMAX);
		else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
			axisq = fmaxf(0.01f, axisq -0.01f);
		else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
			axisq = fminf(1.0f, axisq + 0.01f);
	}
	print_cam_menu(data);
	printf("\nincrementos pos= %f\n", posq);
	printf("incrementos axis= %f\n", axisq);
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
	static float		posq;
	static float		axisq;

	if (posq < 1.0f)
		posq = OBJPLUS;
	if (axisq < 0.001f)
		axisq = OBJAXISP;
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
			obj->pos.y += posq;
		else if (key == MLX_KEY_DOWN)
			obj->pos.y -= posq;
		else if (key == MLX_KEY_LEFT)
			obj->pos.x -= posq;
		else if (key == MLX_KEY_RIGHT)
			obj->pos.x += posq;
		else if (key == MLX_KEY_Z)
			obj->pos.z -= posq;
		else if (key == MLX_KEY_X)
			obj->pos.z += posq;
		else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
			posq = fmaxf(1.0f, posq -1);
		else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
			posq = fminf(100, posq + 1);
	}
	else
	{
		if (key == MLX_KEY_UP)
			obj->axis.y = fminf(obj->axis.y + axisq, OBJAXISMAX);
		else if (key == MLX_KEY_DOWN)
			obj->axis.y = fmaxf(obj->axis.y - axisq, OBJAXISMIN);
		else if (key == MLX_KEY_LEFT)
			obj->axis.x = fmaxf(obj->axis.x - axisq, OBJAXISMIN);
		else if (key == MLX_KEY_RIGHT)
			obj->axis.x = fminf(obj->axis.x + axisq, OBJAXISMAX);
		else if (key == MLX_KEY_Z)
			obj->axis.z = fmaxf(obj->axis.z - axisq, OBJAXISMIN);
		else if (key == MLX_KEY_X)
			obj->axis.z = fminf(obj->axis.z + axisq, OBJAXISMAX);
		else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
			axisq = fmaxf(0.01f, axisq -0.01f);
		else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
			axisq = fminf(1.0f, axisq + 0.01f);
		obj->axis = normalize(obj->axis);
	}
	print_obj_menu(data);
	printf("\nincrementos pos= %f\n", posq);
	printf("incrementos axis= %f\n", axisq);
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
