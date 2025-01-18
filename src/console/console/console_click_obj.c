/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:37 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 14:59:43 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	obj_click_move(t_data *data, t_obj *obj, t_btn_name clicked)
{
	t_slight	*slight;

	slight = data->s_light;
	while (slight->next)
		slight = slight->next;
	if (clicked == left)
	{
		if (obj->prev)
			data->console.last_item = obj->prev;
		else
		{
			if (slight)
			{
				data->console.last_type = SLIGHT;
				data->console.last_item = slight;
			}
			else
				data->console.last_type = ALIGHT;
		}
		return (true);
	}
	else if (clicked == right)
	{
		if (obj->next && obj->next->type == SIDE || obj->next->type == CAP)
			return (false);
		else if (obj->next)
		{
			data->console.last_item = obj->next;
			return (true);
		}
	}
	return (false);
}

void	click_sphere(t_data *data, t_obj *obj, t_btn_name clicked)
{
	if (clicked == row4r)
		obj->size += OBJPLUS;
	else if (clicked == row4l)
		obj->size -= OBJPLUS;
}

void	click_cy_co(t_data *data, t_obj *obj, t_btn_name clicked)
{
	if (clicked == row7r)
		obj->size += OBJPLUS;
	else if (clicked == row7l)
		obj->size = fmax(0.1, obj->size - OBJPLUS);
	else if (clicked == row8r)
		obj->height += OBJPLUS;
	else if (clicked == row8l)
		obj->height = fmax(1, obj->height - OBJPLUS);
}

void	click_cube(t_data *data, t_obj *obj, t_btn_name clicked)
{
	if (clicked == row7r)
		obj->cube_size.x += OBJPLUS;
	else if (clicked == row7l)
		obj->cube_size.x -= OBJPLUS;
	else if (clicked == row8r)
		obj->cube_size.y += OBJPLUS;
	else if (clicked == row8l)
		obj->cube_size.y -= OBJPLUS;
	else if (clicked == row9r)
		obj->cube_size.z += OBJPLUS;
	else if (clicked == row9l)
		obj->cube_size.z -= OBJPLUS;
}

void	click_type(t_data *data, t_obj *obj, t_btn_name clicked, int type)
{
	if (type == SP)
	{
		click_sphere(data, obj, clicked);
		return ;
	}
	if (clicked == axis_xmin)
		obj->axis.x -= OBJAXISP;
	else if (clicked == axis_xmax)
		obj->axis.x += OBJAXISP;
	else if (clicked == axis_ymin)
		obj->axis.y -= OBJAXISP;
	else if (clicked == axis_ymax)
		obj->axis.y += OBJAXISP;
	else if (clicked == axis_zmin)
		obj->axis.z -= OBJAXISP;
	else if (clicked == axis_zmax)
		obj->axis.z += OBJAXISP;
	if (type == CY || type == CO)
		click_cy_co(data, obj, clicked);
	else if (type == CU)
		click_cube(data, obj, clicked);
}
