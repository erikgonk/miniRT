/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:36 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/09 18:11:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_params(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	if (obj)
		check_obj(obj);
		// exit(er("erro: check_params: no obj detected", NULL));
	check_params_acl(data->a_light, data->s_light, data->cam);
}
