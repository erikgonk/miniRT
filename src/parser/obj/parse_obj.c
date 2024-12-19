/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 16:05:03 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	create_obj_normi(t_obj *obj, char **tmp, char **tmp2)
{
	if (obj->type == SP)
	{
		obj->size = ft_atof(*tmp, 0);
		*tmp2 = ft_substr(*tmp, sum_parse(*tmp, 0, 0), ft_strlen(*tmp));
	}
	else if (obj->type == CY)
	{
		obj->size = ft_atof(*tmp2, 0);
		obj->i = sum_parse(*tmp2, 0, 0);
		obj->height = ft_atof(*tmp2, obj->i);
		obj->i = sum_parse(*tmp2, obj->i, 0);
		free(*tmp);
		*tmp = ft_substr(*tmp2, obj->i, ft_strlen(*tmp2));
	}
}

t_obj	*create_obj(char *str, int type)
{
	char	*tmp;
	char	*tmp2;
	t_obj	*obj;

	tmp2 = NULL;
	obj = NULL;
	obj = new_obj();
	obj->type = type;
	tmp = floats_parse(obj, str, 2, 0);
	if (obj->type != SP)
		tmp2 = floats_parse(obj, tmp, 0, 1);
	create_obj_normi(obj, &tmp, &tmp2);
	if (obj->type != CY)
	{
		check_end(tmp2);
		obj->rgb = colors_parse(tmp2);
	}
	else
	{
		check_end(tmp);
		obj->rgb = colors_parse(tmp);
	}
	if (tmp2)
		free(tmp2);
	return (free(tmp), obj);
}
