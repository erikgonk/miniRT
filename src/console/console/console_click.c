/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 13:54:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	console_click(t_data *data, int x, int y)
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
