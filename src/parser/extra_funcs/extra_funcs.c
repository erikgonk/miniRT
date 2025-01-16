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
		exit(er(obj->data, "error: parse_em: lacks arg", NULL));
	if (!ft_isdigit(args[1][0]))
		exit(er(obj->data, "error: parse_em: arg not num", args[1]));
	obj->material.emision = ft_atof(obj->data, args[1], 0);
	if (obj->material.emision > 1 || obj->material.emision < 0)
		exit(er(obj->data, "error: parse_em: emision 0-1", args[1]));
	if (args[2] && args[2][0] != '\n')
		exit(er(obj->data, "error: parse_em: arg not valid", args[2]));
	obj->material.self_emision = obj->material.emision * 2.5;
}

void	parse_cb(t_obj *obj, char **args)
{
	if (!args[1] || !args[2])
		exit(er(obj->data, "error: parse_cb: lacks arg", NULL));
	if (obj->type != PL)
		exit(er(obj->data, "error: parse_cb: just in pl", args[1]));
	obj->material.board_scale = 1 - ft_atof(obj->data, args[1], 0);
	if (obj->material.board_scale > 0.991 || \
			obj->material.board_scale < 0.001)
		exit(er(obj->data, "error: parse_cb: board size 0.991-0.001", NULL));
	obj->material.rgb_checker = colors_parse(obj->data, args[2], 0);
	if (args[3])
		obj->material.m_type = type_extra_func(args[3]);
	if (obj->material.m_type == -1 && args[3][0] != '\n')
		exit(er(obj->data, "error: parse_cb: arg not valid after cb", NULL));
	if (args[3] && args[4])
		exit(er(obj->data, "error: parse_cb: arg not valid after cb", NULL));
}

void	parse_bm(t_obj *obj, char **args, int i)
{
	char	*tmp;

	if (!args[i] || !args[i + 1])
		exit(er(obj->data, "error: parse_bm: lacks arg", NULL));
	obj->material.bm_size = ft_atoi_parse(obj->data, args[i], 0, 0);
	if (obj->material.m_type != -1 && (!args[i] || !args[i + 1]))
		exit(er(obj->data, "error: parse_bm: arg not valid", NULL));
	tmp = ft_strtrim(args[i + 1], " \n\t");
	obj->material.bm_texture = mlx_load_png(tmp);
	free(tmp);
	if (!obj->material.bm_texture)
		exit(er(obj->data, "error: parse_bm: texture not valid", NULL));
	if (args[i + 2])
		obj->material.m_type = type_extra_func(args[i + 2]);
	if (obj->material.m_type == -1 && args[i + 2][0] != '\n')
		exit(er(obj->data, "error: parse_bm: arg not valid after bm", NULL));
	if (args[i + 2] && args[i + 3])
		exit(er(obj->data, "error: parse_bm: arg not valid after bm", NULL));
}

void	parse_tx(t_obj *obj, char **args, int i)
{
	char	*tmp;

	if (!args[i] || !args[i + 1])
		exit(er(obj->data, "error: parse_tx: lacks arg", NULL));
	obj->material.bm_size = ft_atoi_parse(obj->data, args[i], 0, 0);
	if (obj->material.m_type != -1 && (!args[i] || !args[i + 1]))
		exit(er(obj->data, "error: parse_tx: arg not valid", NULL));
	tmp = ft_strtrim(args[i + 1], " \n\t");
	obj->material.texture = mlx_load_png(tmp);
	free(tmp);
	if (!obj->material.texture)
		exit(er(obj->data, "error: parse_tx: texture not valid", NULL));
	if (args[i + 2])
		obj->material.m_type = type_extra_func(args[i + 2]);
	if (obj->material.m_type == -1 && args[3][0] != '\n')
		exit(er(obj->data, "error: parse_tx: arg not valid after bm", NULL));
	if (args[i + 2] && args[i + 3])
		exit(er(obj->data, "error: parse_tx: arg not valid after bm", NULL));
}

void	extra_functionalities(t_obj *obj, char *tmp)
{
	char	**args;
	char	*str;

	init_materials(obj);
	skip_colors(obj->data, tmp, &str);
	args = ft_split(str, ' ');
	if (str && (!str[0] || str[0] == '\n'))
		return (free(str));
	obj->material.m_type = type_extra_func(args[0]);
	if (obj->material.m_type == -1 || !str[1] || \
			(obj->material.m_type < CB && str[2] && str[3]))
		exit(er(obj->data, "error: extra_functs: char after color", str));
	else if (obj->material.m_type == EM)
		parse_em(obj, args);
	else if (obj->material.m_type == CB)
		parse_cb(obj, args);
	else if (obj->material.m_type == BM)
		parse_bm(obj, args, 1);
	else if (obj->material.m_type == TX)
		parse_tx(obj, args, 1);
	ft_free_willy(args);
	free(str);
}
