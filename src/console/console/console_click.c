/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 17:56:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	console_click(t_data *data, int x, int y)
{
	t_btn_name	clicked;
	t_slight	*slight;

	clicked = get_clicked_btn(data, x, y);
	slight = data->console.last_item;
	if (!clicked)
		return ;
	if (data->console.last_type == CAM)
		click_cam_console(data, clicked);
	else if (data->console.last_type == ALIGHT)
		click_alight_console(data, clicked);
	else if (data->console.last_type == SLIGHT)
		click_slight_console(data, slight, clicked);
	else if (data->console.last_type == OBJ)
		click_obj_console(data, clicked);
	return ;
}
