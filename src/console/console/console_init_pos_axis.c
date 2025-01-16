/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_init_pos_axis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/16 17:21:32 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	make_arrows(t_data *data)
{
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	btn->name = left;
	btn->x = data->console.icons[0]->instances[0].x;
	btn->y = data->console.icons[0]->instances[0].y;
	btn->h = data->console.icons[0]->height;
	btn->w = data->console.icons[0]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	btn->name = right;
	btn->x = data->console.icons[1]->instances[0].x;
	btn->y = data->console.icons[1]->instances[0].y;
	btn->h = data->console.icons[1]->height;
	btn->w = data->console.icons[1]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	pos_buttons_min(t_data *data)
{
	t_btn	tmp;
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_xmin;
	tmp.x = data->console.icons[2]->instances[0].x;
	tmp.y = data->console.icons[2]->instances[0].y;
	tmp.h = data->console.icons[2]->height;
	tmp.w = data->console.icons[2]->width;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_ymin;
	tmp.x = data->console.icons[2]->instances[1].x;
	tmp.y = data->console.icons[2]->instances[1].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_zmin;
	tmp.x = data->console.icons[2]->instances[2].x;
	tmp.y = data->console.icons[2]->instances[2].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	pos_buttons_max(t_data *data)
{
	t_btn	tmp;
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_xmax;
	tmp.x = data->console.icons[3]->instances[0].x;
	tmp.y = data->console.icons[3]->instances[0].y;
	tmp.h = data->console.icons[3]->height;
	tmp.w = data->console.icons[3]->width;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_ymax;
	tmp.x = data->console.icons[3]->instances[1].x;
	tmp.y = data->console.icons[3]->instances[1].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = pos_zmax;
	tmp.x = data->console.icons[3]->instances[2].x;
	tmp.y = data->console.icons[3]->instances[2].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	axis_buttons_min(t_data *data)
{
	t_btn	tmp;
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_xmin;
	tmp.x = data->console.icons[2]->instances[3].x;
	tmp.y = data->console.icons[2]->instances[3].y;
	tmp.h = data->console.icons[2]->height;
	tmp.w = data->console.icons[2]->width;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_ymin;
	tmp.x = data->console.icons[2]->instances[4].x;
	tmp.y = data->console.icons[2]->instances[4].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_zmin;
	tmp.x = data->console.icons[2]->instances[5].x;
	tmp.y = data->console.icons[2]->instances[5].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	axis_buttons_max(t_data *data)
{
	t_btn	tmp;
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_xmax;
	tmp.x = data->console.icons[3]->instances[3].x;
	tmp.y = data->console.icons[3]->instances[3].y;
	tmp.h = data->console.icons[3]->height;
	tmp.w = data->console.icons[3]->width;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_ymax;
	tmp.x = data->console.icons[3]->instances[4].x;
	tmp.y = data->console.icons[3]->instances[4].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	tmp.name = axis_zmax;
	tmp.x = data->console.icons[3]->instances[5].x;
	tmp.y = data->console.icons[3]->instances[5].y;
	*btn = tmp;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}
