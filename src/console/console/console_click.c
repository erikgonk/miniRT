/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:13 by shurtado         ###   ########.fr       */
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

void		console_click(t_data *data, int x, int y)
{
	t_btn_name	clicked;

	clicked = get_clicked_btn(data, x, y);
	// if (!clicked)
	// 	return ;
	// if (clicked == left)
	// 	(void)
	// else if (clicked == right)
	// 	(void)
	// else
	// 	return ;
	printf("Se ha clickado en: %d\n", clicked);
	return ;
}
