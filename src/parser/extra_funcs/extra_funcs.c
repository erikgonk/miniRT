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
    obj->material.reflectivity = -1;
    obj->material.transmittance = -1;
    obj->material.roughness = -1;
    obj->material.absorption = -1;
    obj->material.specularity = -1;
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
	static char		*bts[] = {"sl", "mt", "gl", "mr", "cb", "bl", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (-1);
}

void	parse_cb(t_obj *obj, char *str)
{
	int		i;

	i = 2;
    obj->material.board_scale = ft_atof(str, i);
	obj->material.board_scale = 1 - obj->material.board_scale;
    if (obj->material.board_scale > 0.991 || obj->material.board_scale < 0.001)
        exit(er("error: parse_cb: board size has to be 0.991-0.001", NULL));
    i = skip_float(str, i, 0, 0);
	obj->material.rgb_checker = colors_parse(str, i);
	check_end(str, i);
}

void	extra_functionalities(t_obj *obj, char *tmp)
{
	char	*str;
	int		type;

    init_materials(obj);
	skip_colors(tmp, &str);
	if (str && (!str[0] || str[0] == '\n'))
		return (free(str));
	type = type_extra_func(str);
	if (type == -1 || !str[1] || (type != CB && str[2] && str[3]))
		exit(er("error: extra functs: invalid char after color", str));
	if (type == CB)
		parse_cb(obj, str);
    // else if (type == MT)
    // else if (type == GL)
    // else if (type == MR)
	free(str);
}
