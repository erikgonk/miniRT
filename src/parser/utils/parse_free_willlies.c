/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_willlies.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/16 10:59:03 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**ft_free_willy(char **cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	cmd = NULL;
	return (NULL);
}

void	free_willy_lst(t_data *data)
{
	t_obj		*obj;
	t_slight	*s_light;

	obj = data->obj;
	s_light = data->s_light;
	if (!data)
		return ;
	if (data->a_light)
		free(data->a_light);
	if (data->cam)
		free(data->cam);
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
	while (data->s_light)
	{
		data->s_light = data->s_light->next;
		free(s_light);
		s_light = data->s_light;
	}
}
