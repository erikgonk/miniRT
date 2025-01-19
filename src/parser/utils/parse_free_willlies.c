/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_willlies.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/19 19:32:07 by shurtado         ###   ########.fr       */
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
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
	return (NULL);
}

void	free_willy_obj(t_data *data)
{
	t_obj		*obj;

	obj = data->obj;
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
}

void	free_willy_lst(t_data *data)
{
	t_slight	*s_light;

	if (data->args)
		ft_free_willy(data->args);
	s_light = data->s_light;
	if (!data)
		return ;
	if (data->a_light)
	{
		free(data->a_light);
		data->a_light = NULL;
	}
	if (data->cam)
		free(data->cam);
	free_willy_obj(data);
	while (data->s_light)
	{
		data->s_light = data->s_light->next;
		free(s_light);
		s_light = data->s_light;
	}
}
