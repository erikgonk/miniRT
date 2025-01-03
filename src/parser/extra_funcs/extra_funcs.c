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

void    init_materials(t_obj *obj)
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
	static char		*bts[] = {"mt", "gl", "mr", "cb", "tr", "em", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (-1);
}

void	parse_cb_em(t_obj *obj, char *str)
{
	int		i;

	i = 2;
	if (obj->material.m_type == CB)
	{
		if (obj->type != PL)
			exit(er("error: parse_cb_em: just plane can be a checkerboard", str));
		obj->material.board_scale = ft_atof(str, i);
		obj->material.board_scale = 1 - obj->material.board_scale;
		if (obj->material.board_scale > 0.991 || obj->material.board_scale < 0.001)
			exit(er("error: parse_cb_em: board size has to be 0.991-0.001", NULL));
		i = skip_float(str, i, 0, 0);
		obj->material.rgb_checker = colors_parse(str, i);
		check_end(str, i);
	}
	else if (obj->material.m_type == EM)
	{
		obj->material.emision = ft_atof(str, i);
		i = skip_float(str, i, 0, 0);
		while (str[i] && str[i] != '\n')
			if (!ft_isspace(str[i++]))
				exit(er("error: parse_cb_em: char after last num", str));
		if (obj->material.emision > 1 || obj->material.emision < 0)
			exit(er("error: parse_cb_em: emision 0-1", str));
	}
}

void	extra_functionalities(t_obj *obj, char *tmp)
{
	char	*str;

    init_materials(obj);
	skip_colors(tmp, &str);
	if (str && (!str[0] || str[0] == '\n'))
		return (free(str));
	obj->material.m_type = type_extra_func(str);
	if (obj->material.m_type == -1 || !str[1] || (obj->material.m_type < CB && str[2] && str[3]))
		exit(er("error: extra_functs: invalid char after color", str));
	else if (obj->material.m_type >= CB)
		parse_cb_em(obj, str);
	free(str);
}
