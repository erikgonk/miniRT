/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/10 12:22:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
	// init_sides(data);
	// print_objects(data->obj);
	init_light(data);
	init_mlx(data);
	init_materials_render(data);
}

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		exit(er("error: failed to allocate memory", NULL));
	(*data)->aa = -1;
	(*data)->a_light = malloc(sizeof(t_alight));
	(*data)->a_light->br = 0;
	(*data)->a_light->rgb.r = 0;
	(*data)->a_light->rgb.g = 0;
	(*data)->a_light->rgb.b = 0;
	(*data)->trace_flag = false;
	(*data)->x = W_WH;
	(*data)->y = W_HG;
	(*data)->m_trace = malloc(sizeof(pthread_mutex_t));
	(*data)->m_god = malloc(sizeof(pthread_mutex_t));
	(*data)->god = true;
	pthread_mutex_init((*data)->m_trace, NULL);
}
