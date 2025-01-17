/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 11:42:49 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_btn_name	get_clicked_btn(t_data *data, int x, int y)
{
	t_list	*click;
	t_btn	*btn;

	click = data->console.click_lst;

	while (click)
	{
		btn = click->content;
		if (x > btn->x && x <  btn->x + btn->w)
			if (y > btn->y && y <  btn->y + btn->h)
				return (btn->name);
		click = click->next;
	}
	return (none);
}


int	ft_objremove(t_obj **lst, t_obj *node)
{
	t_obj	*temp;
	t_obj	*lstp;

	if (!lst || !(*lst) || !node)
		return (0);
	if (*lst == node)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
		temp = NULL;
		return (1);
	}
	lstp = *lst;
	while (lstp && lstp->next != node)
		lstp = lstp->next;
	if (lstp->next == node)
	{
		temp = lstp->next;
		lstp->next = temp->next;
		free(temp);
		temp = NULL;
		return (1);
	}
	return (0);
}

void	free_after_click(t_data *data)
{
	t_obj		*obj;
	t_obj		*next;

	obj = data->obj;
	while(obj)
	{
		next = obj->next;
		if (obj && obj->type == SIDE || obj->type == CAP)
		{
			ft_objremove(&data->obj, obj);
		}
		obj = next;
	}
}

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

void	print_cam_console(t_data *data, t_btn_name clicked)
{
		if (clicked == left)
			return ;
		else if (clicked == right)
			return ;
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

void	print_alight_console(t_data *data, t_btn_name clicked)
{
	return ;
}
void	print_slight_console(t_data *data, t_btn_name clicked)
{
	return ;
}
void	print_obj_console(t_data *data, t_btn_name clicked)
{
	return ;
}

void		console_click(t_data *data, int x, int y)
{
	t_btn_name	clicked;

	if (!data->console.last_item)
	{
		data->console.last_item = data->cam;
		data->console.last_type = CAM;
	}
	clicked = get_clicked_btn(data, x, y);
	if (!clicked)
		return ;
	if (data->console.last_type == CAM)
		print_cam_console(data, clicked);
	else if (data->console.last_type == ALIGHT)
		print_alight_console(data, clicked);
	else if (data->console.last_type == SLIGHT)
		print_slight_console(data, clicked);
	else if (data->console.last_type == OBJ)
		print_obj_console(data, clicked);
	return ;
}
