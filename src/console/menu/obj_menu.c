/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:41 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 12:41:36 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	adjust_obj_position(keys_t key, t_obj *obj, double *posq)
{
	if (key == MLX_KEY_UP)
		obj->pos.y += *posq;
	else if (key == MLX_KEY_DOWN)
		obj->pos.y -= *posq;
	else if (key == MLX_KEY_LEFT)
		obj->pos.x -= *posq;
	else if (key == MLX_KEY_RIGHT)
		obj->pos.x += *posq;
	else if (key == MLX_KEY_Z)
		obj->pos.z -= *posq;
	else if (key == MLX_KEY_X)
		obj->pos.z += *posq;
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		*posq = fmax(1.0f, *posq - 1);
	else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
		*posq = fmin(100, *posq + 1);
}

void	adjust_obj_axis(keys_t key, t_obj *obj, double *axisq)
{
	if (key == MLX_KEY_UP)
		obj->axis.y = fmin(obj->axis.y + *axisq, OBJAXISMAX);
	else if (key == MLX_KEY_DOWN)
		obj->axis.y = fmax(obj->axis.y - *axisq, OBJAXISMIN);
	else if (key == MLX_KEY_LEFT)
		obj->axis.x = fmax(obj->axis.x - *axisq, OBJAXISMIN);
	else if (key == MLX_KEY_RIGHT)
		obj->axis.x = fmin(obj->axis.x + *axisq, OBJAXISMAX);
	else if (key == MLX_KEY_Z)
		obj->axis.z = fmax(obj->axis.z - *axisq, OBJAXISMIN);
	else if (key == MLX_KEY_X)
		obj->axis.z = fmin(obj->axis.z + *axisq, OBJAXISMAX);
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		*axisq = fmax(0.01f, *axisq - 0.01f);
	else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
		*axisq = fmin(1.0f, *axisq + 0.01f);
	obj->axis = normalize(obj->axis);
}

void	manage_obj(keys_t key, t_data *data)
{
	static bool			mode;
	static t_obj		*obj;
	static double		posq;
	static double		axisq;

	posq = fmax(posq, 1.0f);
	axisq = fmax(axisq, 0.001f);
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
		adjust_obj_position(key, obj, &posq);
	else
		adjust_obj_axis(key, obj, &axisq);
	print_obj_menu(data);
	printf("\nincrementos pos= %f\n", posq);
	printf("incrementos axis= %f\n", axisq);
}
