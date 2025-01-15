/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 16:24:42 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
	init_light(data);
	init_mlx(data);
	init_materials_render(data);
	data->img_last = NULL;
	data->console.btn_list = NULL;
}

void	init_data(t_data **data)
{
	*data = calloc(1, sizeof(t_data));
	if (!(*data))
		exit(er(NULL, "error: failed to allocate memory", NULL));
	(*data)->obj = NULL;
	(*data)->s_light = NULL;
	(*data)->a_light = NULL;
	(*data)->cam = NULL;
	(*data)->aa = -1;
	(*data)->a_light = calloc(1, sizeof(t_alight));
	(*data)->a_light->br = 0;
	(*data)->a_light->rgb.r = 0;
	(*data)->a_light->rgb.g = 0;
	(*data)->a_light->rgb.b = 0;
	(*data)->trace_flag = false;
	(*data)->x = W_WH;
	(*data)->y = W_HG;
	(*data)->m_trace = calloc(1, sizeof(pthread_mutex_t));
	(*data)->m_god = calloc(1, sizeof(pthread_mutex_t));
	(*data)->god = true;
	(*data)->render_sel = NULL;
	(*data)->last_render = ONE;
	pthread_mutex_init((*data)->m_trace, NULL);
}
