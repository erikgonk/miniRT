/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_init_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/16 17:28:43 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_fov(t_data *data)
{
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	btn->name = fov_min;
	btn->x = data->console.icons[2]->instances[6].x;
	btn->y = data->console.icons[2]->instances[6].y;
	btn->h = data->console.icons[2]->height;
	btn->w = data->console.icons[2]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	btn->name = fov_max;
	btn->x = data->console.icons[3]->instances[6].x;
	btn->y = data->console.icons[3]->instances[6].y;
	btn->h = data->console.icons[3]->height;
	btn->w = data->console.icons[3]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}
