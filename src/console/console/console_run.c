/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 15:01:51 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_obj_labels(t_data *data, t_img_btn *img_btn, int top)
{
	t_obj		*obj;

	obj = data->console.last_item;
	write_obj_labels(data, img_btn);
	if (obj->type == PL)
		plane_set_labels(data, img_btn, top);
	else if (obj->type == SP)
		sphere_set_labels(data, img_btn, top);
	else if (obj->type == CY)
		cylinder_set_labels(data, img_btn, top);
	else if (obj->type == CO)
		cone_set_labels(data, img_btn, top);
	else if (obj->type == CU)
		cube_set_labels(data, img_btn, top);
}

void	set_labels(t_data *data, t_img_btn *img_btn, int top)
{
	if (data->console.last_type == CAM)
		set_cam_labels(data, img_btn, top);
	else if (data->console.last_type == ALIGHT)
		set_alight_labels(data, img_btn, top);
	else if (data->console.last_type == SLIGHT)
		set_slight_labels(data, img_btn, top);
	else if (data->console.last_type == OBJ)
		set_obj_labels(data, img_btn, top);
}

void	set_all_buttons(t_data *data)
{
	t_img_btn	*img_btn;
	int			top;

	top = 25;
	img_btn = calloc(1, sizeof(t_img_btn));
	set_resize_buton_images(data, img_btn);
	put_imgarrows(data, top);
	set_labels(data, img_btn, top);
	fill_image_list(data, img_btn);
}

void	run_console(t_data *data)
{
	if (!g_mlx)
		g_mlx = data->mlx;
	if (data->console.btn_list)
	{
		ft_lstclear(&data->console.btn_list, del_image);
		data->console.btn_list = NULL;
	}
	set_background(data);
	set_all_buttons(data);
	init_console(data);
	data->last_render = FAST;
}