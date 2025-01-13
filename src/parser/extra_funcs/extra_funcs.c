/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/11 12:14:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_em(t_obj *obj, char **args)
{
	if (!args[1])
		exit(er("error: parse_em: lacks arg", NULL));
	if (!ft_isdigit(args[1][0]))
		exit(er("error: parse_em: arg not num", args[1]));
	obj->material.emision = ft_atof(args[1], 0);
	if (obj->material.emision > 1 || obj->material.emision < 0)
		exit(er("error: parse_em: emision 0-1", args[1]));
	if (args[2] && args[2][0] != '\n')
		exit(er("error: parse_em: arg not valid", args[2]));
	obj->material.self_emision = obj->material.emision * 2.5;
}

void	parse_bm(t_obj *obj, char **args)
{
	char	*tmp;

	if (!args[1] || !args[2])
		exit(er("error: parse_bm: lacks arg", NULL));
	obj->material.bm_size = ft_atoi_parse(args[1], 0, 0);
	if (obj->material.m_type != -1 && (!args[1] || !args[2]))
		exit(er("error: parse_bm: arg not valid", NULL));
	tmp = ft_strtrim(args[2], " \n\t");
	obj->material.texture = mlx_load_png(tmp);
	free(tmp);
	if (!obj->material.texture)
		exit(er("error: parse_bm: texture not valid", NULL));
	if (args[3])
		obj->material.m_type = type_extra_func(args[3]);
	if (obj->material.m_type == -1 && args[3][0] != '\n')
		exit(er("error: parse_bm: arg not valid after bm", NULL));
	if (args[3] && args[4])
		exit(er("error: parse_bm: arg not valid after bm", NULL));
}

void	parse_cb(t_obj *obj, char **args)
{
	if (!args[1] || !args[2])
		exit(er("error: parse_cb: lacks arg", NULL));
	if (obj->type != PL)
		exit(er("error: parse_cb: checkerboard just in pl", args[1]));
	obj->material.board_scale = 1 - ft_atof(args[1], 0);
	if (obj->material.board_scale > 0.991 || \
			obj->material.board_scale < 0.001)
		exit(er("error: parse_cb: board size 0.991-0.001", NULL));
	obj->material.rgb_checker = colors_parse(args[2], 0);
	if (args[3])
		obj->material.m_type = type_extra_func(args[3]);
	if (obj->material.m_type == -1 && args[3][0] != '\n')
		exit(er("error: parse_cb: arg not valid after cb", NULL));
	if (args[3] && args[4])
		exit(er("error: parse_cb: arg not valid after cb", NULL));
}

void	extra_functionalities(t_obj *obj, char *tmp)
{
	char	**args;
	char	*str;

	init_materials(obj);
	skip_colors(tmp, &str);
	args = ft_split(str, ' ');
	if (str && (!str[0] || str[0] == '\n'))
		return (free(str));
	obj->material.m_type = type_extra_func(args[0]);
	if (obj->material.m_type == -1 || !str[1] || \
			(obj->material.m_type < CB && str[2] && str[3]))
		exit(er("error: extra_functs: invalid char after color", str));
	else if (obj->material.m_type == EM)
		parse_em(obj, args);
	else if (obj->material.m_type == CB)
		parse_cb(obj, args);
	else if (obj->material.m_type == BM)
		parse_bm(obj, args);
	ft_free_willy(args);
	free(str);
}
