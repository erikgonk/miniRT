/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/20 16:20:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
	init_light(data);
	init_mlx(data);
}

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		exit(er("error: failed to allocate memory", NULL));
	(*data)->aa = 0;
}

void	free_data(t_data *data)
{
	t_obj		*obj;
	t_slight	*slight;

	obj = data->obj;
	slight = data->s_light;
	free(data->cam);
	free(data->a_light);
	while (data->s_light)
	{
		data->s_light = data->s_light->next;
		free(slight);
		slight = data->s_light;
	}
	free(data->s_light);
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
	if (data)
		free(data);
}
