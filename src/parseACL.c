/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/24 14:28:57 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

char	*floatsACLParse(t_obj *obj, char *str, int i, int flag)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;
	
	i = sumParse(str, i, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1);
	y = ft_atof(str, i);
	i = sumParse(str, i, 1);
	z = ft_atof(str, i);
	i = sumParse(str, i, 2);
	if (flag == 0)
		obj->pos = vDefine(x, y, z);
	else if (flag == 1)
		obj->axis = vDefine(x, y, z);
	tmp = ft_substr(str, i, ft_strlen(str));
	return (tmp);
}

void	createACL(t_data *data, char *str, int type)
{
	if (type == 3)
		data->cam = malloc(sizeof(t_sLight));
	else if (type == 4)
		data->sLight = malloc(sizeof(t_aLight));
	else if (type == 5)
		data->aLight = malloc(sizeof(t_cam));
}
