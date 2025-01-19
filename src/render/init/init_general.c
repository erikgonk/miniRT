/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/19 18:26:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
	init_set_prev(data);
	init_light(data);
	init_materials_render(data);
	data->img_last = NULL;
}

void	init_data(t_data **data)
{
	*data = calloc(1, sizeof(t_data));
	if (!(*data))
		exit(er(NULL, "error: failed to allocate memory", NULL));
	(*data)->aa = -1;
	(*data)->trace_flag = false;
	(*data)->x = W_WH;
	(*data)->y = W_HG;
	(*data)->m_trace = calloc(1, sizeof(pthread_mutex_t));
	(*data)->m_god = calloc(1, sizeof(pthread_mutex_t));
	(*data)->god = true;
	(*data)->render_sel = NULL;
	(*data)->last_render = ONE;
	(*data)->console = calloc(1, sizeof(t_console));
	(*data)->console->btn_list = NULL;
	(*data)->console->click_lst = NULL;
	(*data)->console->last_item = NULL;
	(*data)->console->last_type = CAM;
	pthread_mutex_init((*data)->m_trace, NULL);
}
