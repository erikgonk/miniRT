/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click_cam.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:59:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 11:36:16 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	console_click_axis(t_data *data, t_btn_name clicked)
{
	if (clicked == axis_xmin)
		data->cam->axis.x -= CAMAXISP;
	else if (clicked == axis_xmax)
		data->cam->axis.x += CAMAXISP;
	else if (clicked == axis_ymin)
		data->cam->axis.y -= CAMAXISP;
	else if (clicked == axis_ymax)
		data->cam->axis.y += CAMAXISP;
	else if (clicked == axis_zmin)
		data->cam->axis.z -= CAMAXISP;
	else if (clicked == axis_zmax)
		data->cam->axis.z += CAMAXISP;
}

void	console_click_pos(t_data *data, t_btn_name clicked)
{
	if (clicked == pos_xmin)
		data->cam->pos.x -= CAMPLUS;
	else if (clicked == pos_xmax)
		data->cam->pos.x += CAMPLUS;
	else if (clicked == pos_ymin)
		data->cam->pos.y -= CAMPLUS;
	else if (clicked == pos_ymax)
		data->cam->pos.y += CAMPLUS;
	else if (clicked == pos_zmin)
		data->cam->pos.z -= CAMPLUS;
	else if (clicked == pos_zmax)
		data->cam->pos.z += CAMPLUS;
}

void	click_cam_console(t_data *data, t_btn_name clicked)
{
	if (clicked == left)
		return ;
	else if (clicked == right)
	{
		if (data->a_light->exist == 1)
			data->console.last_type = ALIGHT;
		else if (data->s_light)
		{
			data->console.last_type = SLIGHT;
			data->console.last_item = data->s_light;
		}
		run_console(data);
		return ;
	}
	console_click_pos(data, clicked);
	console_click_axis(data, clicked);
	if (clicked == fov_min)
		data->cam->fov = fmax(data->cam->fov - CAMPLUS, 0);
	else if (clicked == fov_max)
		data->cam->fov += CAMPLUS;
	free_after_click(data);
	init_all(data);
	data->render_sel = render_fast;
}
