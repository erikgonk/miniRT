/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/30 16:00:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
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
	(*data)->trace_flag = true;
}
