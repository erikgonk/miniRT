/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:36 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/18 11:43:00 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_params(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	if (obj)
		check_obj(obj);
	else
		exit(er(data, "error: check_params: obj not exist", NULL));
	check_params_acl(data, data->a_light, data->s_light, data->cam);
}
