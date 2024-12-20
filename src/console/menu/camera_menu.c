/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:18:43 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:19:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	adjust_camera_pos(keys_t key, t_data *data, float *posq)
{
	if (key == MLX_KEY_UP)
		data->cam->pos.y += *posq;
	else if (key == MLX_KEY_DOWN)
		data->cam->pos.y -= *posq;
	else if (key == MLX_KEY_LEFT)
		data->cam->pos.x -= *posq;
	else if (key == MLX_KEY_RIGHT)
		data->cam->pos.x += *posq;
	else if (key == MLX_KEY_Z)
		data->cam->pos.z -= *posq;
	else if (key == MLX_KEY_X)
		data->cam->pos.z += *posq;
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		*posq = fmaxf(1.0f, *posq - 1);
	else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
		*posq = fminf(100, *posq + 1);
}

void	adjust_camera_axis(keys_t key, t_data *data, float *axisq)
{
	if (key == MLX_KEY_UP)
		data->cam->axis.y = fminf(data->cam->axis.y + *axisq, CAMAXISMAX);
	else if (key == MLX_KEY_DOWN)
		data->cam->axis.y = fmaxf(data->cam->axis.y - *axisq, CAMAXISMIN);
	else if (key == MLX_KEY_LEFT)
		data->cam->axis.x = fmaxf(data->cam->axis.x - *axisq, CAMAXISMIN);
	else if (key == MLX_KEY_RIGHT)
		data->cam->axis.x = fminf(data->cam->axis.x + *axisq, CAMAXISMAX);
	else if (key == MLX_KEY_Z)
		data->cam->axis.z = fmaxf(data->cam->axis.z - *axisq, CAMAXISMIN);
	else if (key == MLX_KEY_X)
		data->cam->axis.z = fminf(data->cam->axis.z + *axisq, CAMAXISMAX);
	else if (key == MLX_KEY_MINUS || key == MLX_KEY_KP_SUBTRACT)
		*axisq = fmaxf(0.01f, *axisq - 0.01f);
	else if (key == MLX_KEY_KP_ADD || key == MLX_KEY_EQUAL)
		*axisq = fminf(1.0f, *axisq + 0.01f);
	data->cam->axis = normalize(data->cam->axis);
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
		adjust_camera_pos(key, data, &posq);
	else
		adjust_camera_axis(key, data, &axisq);
	print_cam_menu(data);
	printf("\nincrementos pos= %f\n", posq);
	printf("incrementos axis= %f\n", axisq);
}
