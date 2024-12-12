/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseObj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/12 17:30:43 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*createObj(t_data *data, char *str, int type)
{
	char	*tmp;
	char	*tmp2;
	t_obj	*obj;

	tmp2 = NULL;
	obj = newObj(obj);
	obj->type = type;
	tmp = floatsParse(obj, str, 2, 0);
	if (obj->type != 0) // pl & cy
		tmp2 = floatsParse(obj, tmp, 0, 1);
	if (obj->type == 0) // sp
	{
		obj->size = ft_atof(tmp, 0);
		tmp2 = ft_substr(tmp, sumParse(tmp, 0, 2, 0), ft_strlen(tmp));
	}
	else if (obj->type == 2) // cy
	{
		obj->size = ft_atof(tmp2, 0);
		obj->i = sumParse(tmp2, 0, 2, 0);
		obj->height = ft_atof(tmp2, obj->i);
		obj->i = sumParse(tmp2, obj->i, 2, 0);
		free(tmp);
		tmp = ft_substr(tmp2, obj->i, ft_strlen(tmp2));
	}
	if (obj->type != 2) // sp & pl
	{
		check_end(obj, tmp2);
		obj->rgb = colorsParse(tmp2);
	}
	else // cy
	{
		check_end(obj, tmp);
		obj->rgb = colorsParse(tmp);
	}
	free(tmp);
	if (tmp2)
		free(tmp2);
	return (obj);
}
