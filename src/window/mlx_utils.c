/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:58:38 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/18 17:37:57 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	swap_mgod(t_data *data)
{
	pthread_mutex_lock(data->m_god);
	data->god = !data->god;
	pthread_mutex_unlock(data->m_god);
}

void	set_last(t_data *data)
{
	if (data->last_render == ONE)
		data->render_sel = render_one;
	else if (data->last_render == FAST)
		data->render_sel = render_fast;
	else if (data->last_render == UPDATE)
		data->render_sel = update_render;
}

void	swap_flag_mlx(t_data *data)
{
	pthread_mutex_lock(data->m_trace);
	data->trace_flag = !data->trace_flag;
	pthread_mutex_unlock(data->m_trace);
}
