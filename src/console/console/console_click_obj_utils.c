/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_click_obj_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:37 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 17:58:08 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	obj_click_move_normi(t_data *data, t_obj *obj, t_slight *slight)
{
	if (obj->prev)
		data->console.last_item = obj->prev;
	else
	{
		if (slight)
		{
			data->console.last_type = SLIGHT;
			data->console.last_item = slight;
		}
		else
			data->console.last_type = ALIGHT;
	}
	return (true);
}
