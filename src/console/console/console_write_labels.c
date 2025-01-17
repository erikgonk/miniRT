/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_write_labels.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:05:19 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 20:09:45 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	write_cam_labels(t_data *data, t_img_btn *img_btn)
{
	int		size;
	t_v3	pos;
	t_v3	axis;

	pos = data->cam->pos;
	axis = data->cam->axis;
	size = sizeof(img_btn->posx);
	snprintf(img_btn->posx, size, "x          %.2f", pos.x);
	snprintf(img_btn->posy, size, "y          %.2f", pos.y);
	snprintf(img_btn->posz, size, "z          %.2f", pos.z);
	snprintf(img_btn->axisx, size, "x           %.2f", axis.x);
	snprintf(img_btn->axisy, size, "y           %.2f", axis.y);
	snprintf(img_btn->axisz, size, "z           %.2f", axis.z);
	snprintf(img_btn->fov, size, "              %d", data->cam->fov);
}

void	write_alight_labels(t_data *data, t_img_btn *img_btn)
{
	int		size;
	t_v3	pos;
	t_v3	axis;

	pos = data->cam->pos;
	axis = data->cam->axis;
	size = sizeof(img_btn->posx);
	snprintf(img_btn->posx, size, "br         %.2f", pos.x);
}
