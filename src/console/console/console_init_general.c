/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_init_general.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/19 15:32:36 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	click_obj_console(t_data *data, t_btn_name clicked)
{
	t_obj	*obj;

	obj = data->console.last_item;
	if (obj_click_move(data, obj, clicked))
	{
		run_console(data);
		return ;
	}
	if (clicked == pos_xmin)
		obj->pos.x -= OBJPLUS;
	else if (clicked == pos_xmax)
		obj->pos.x += OBJPLUS;
	else if (clicked == pos_ymin)
		obj->pos.y -= OBJPLUS;
	else if (clicked == pos_ymax)
		obj->pos.y += OBJPLUS;
	else if (clicked == pos_zmin)
		obj->pos.z -= OBJPLUS;
	else if (clicked == pos_zmax)
		obj->pos.z += OBJPLUS;
	else
		click_type(data, obj, clicked, obj->type);
	free_after_click(data);
	init_all(data);
	data->render_sel = render_fast;
}

void	init_console(t_data *data)
{
	make_arrows(data);
	rows_1to3_left(data);
	rows_1to3_right(data);
	rows_4to6_left(data);
	rows_4to6_right(data);
	rows_7(data);
	rows_8(data);
	rows_9(data);
	row_material(data, btn_df);
}
