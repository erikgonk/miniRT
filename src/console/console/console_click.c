/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 22:10:15 by shurtado         ###   ########.fr       */
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
		data->console.last_type = ALIGHT;
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

void	click_alight_console(t_data *data, t_btn_name clicked)
{
	if (clicked == right)
		return ;
	else if (clicked == left)
	{
		data->console.last_type = CAM;
		run_console(data);
		return ;
	}
	if (clicked == br_min)
		data->a_light->br = fmax(data->a_light->br - ALIGHTPLUS, ALIGHTMIN);
	else if (clicked == br_max)
		data->a_light->br = fmin(data->a_light->br + ALIGHTPLUS, ALIGHTMAX);
	free_after_click(data);
	init_all(data);
	data->render_sel = render_fast;
}
void	click_slight_console(t_data *data, t_btn_name clicked)
{
	return ;
}
void	click_obj_console(t_data *data, t_btn_name clicked)
{
	return ;
}

void		console_click(t_data *data, int x, int y)
{
	t_btn_name	clicked;

	clicked = get_clicked_btn(data, x, y);
	if (!clicked)
		return ;
	if (data->console.last_type == CAM)
		click_cam_console(data, clicked);
	else if (data->console.last_type == ALIGHT)
		click_alight_console(data, clicked);
	else if (data->console.last_type == SLIGHT)
		click_slight_console(data, clicked);
	else if (data->console.last_type == OBJ)
		click_obj_console(data, clicked);
	return ;
}
