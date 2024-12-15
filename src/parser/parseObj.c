/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseObj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 17:02:22 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*create_obj(t_data *data, char *str, int type)
{
	char	*tmp;
	char	*tmp2;
	t_obj	*obj;

	tmp2 = NULL;
	obj = new_obj(obj);
	obj->type = type;
	tmp = floats_parse(obj, str, 2, 0);
	if (obj->type != 0)
		tmp2 = floats_parse(obj, tmp, 0, 1);
	if (obj->type == 0)
	{
		obj->size = ft_atof(tmp, 0);
		tmp2 = ft_substr(tmp, sum_parse(tmp, 0, 2, 0), ft_strlen(tmp));
	}
	else if (obj->type == 2)
	{
		obj->size = ft_atof(tmp2, 0);
		obj->i = sum_parse(tmp2, 0, 2, 0);
		obj->height = ft_atof(tmp2, obj->i);
		obj->i = sum_parse(tmp2, obj->i, 2, 0);
		free(tmp);
		tmp = ft_substr(tmp2, obj->i, ft_strlen(tmp2));
	}
	if (obj->type != 2)
	{
		check_end(obj, tmp2);
		obj->rgb = colors_parse(tmp2);
	}
	else
	{
		check_end(obj, tmp);
		obj->rgb = colors_parse(tmp);
	}
	free(tmp);
	if (tmp2)
		free(tmp2);
	return (obj);
}
