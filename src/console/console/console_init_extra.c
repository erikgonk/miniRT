/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_init_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 17:06:44 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rows_7(t_data *data)
{
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	btn->name = row7l;
	btn->x = data->console.icons[2]->instances[6].x;
	btn->y = data->console.icons[2]->instances[6].y;
	btn->h = data->console.icons[2]->height;
	btn->w = data->console.icons[2]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	btn->name = row7r;
	btn->x = data->console.icons[3]->instances[6].x;
	btn->y = data->console.icons[3]->instances[6].y;
	btn->h = data->console.icons[3]->height;
	btn->w = data->console.icons[3]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	rows_8(t_data *data)
{
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	btn->name = row8l;
	btn->x = data->console.icons[2]->instances[7].x;
	btn->y = data->console.icons[2]->instances[7].y;
	btn->h = data->console.icons[2]->height;
	btn->w = data->console.icons[2]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	btn->name = row8r;
	btn->x = data->console.icons[3]->instances[7].x;
	btn->y = data->console.icons[3]->instances[7].y;
	btn->h = data->console.icons[3]->height;
	btn->w = data->console.icons[3]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}

void	rows_9(t_data *data)
{
	t_btn	*btn;

	btn = calloc(1, sizeof(t_btn));
	btn->name = row9l;
	btn->x = data->console.icons[2]->instances[8].x;
	btn->y = data->console.icons[2]->instances[8].y;
	btn->h = data->console.icons[2]->height;
	btn->w = data->console.icons[2]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
	btn = calloc(1, sizeof(t_btn));
	btn->name = row9r;
	btn->x = data->console.icons[3]->instances[8].x;
	btn->y = data->console.icons[3]->instances[8].y;
	btn->h = data->console.icons[3]->height;
	btn->w = data->console.icons[3]->width;
	ft_lstadd_front(&data->console.click_lst, ft_lstnew(btn));
}
