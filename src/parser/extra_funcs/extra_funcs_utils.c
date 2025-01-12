/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funcs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/12 10:20:07 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_materials(t_obj *obj)
{
	obj->material.m_type = -1;
	obj->material.reflectivity = 0;
	obj->material.transmittance = 0;
	obj->material.roughness = 1;
	obj->material.absorption = 1;
	obj->material.specularity = 0.1;
	obj->material.board_scale = -1;
}

void	skip_colors(char *str, char **res)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	i = skip_color(str, i, 0);
	i = skip_color(str, i, 0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	*res = ft_substr(str, i, ft_strlen(str));
}

int	type_extra_func(char *str)
{
	static char		*bts[] = {"mt", "gl", "mr", "cb", "em", "bm", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (-1);
}