/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_acl_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:02:22 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/11 12:21:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	doubles_acl_parse(char *str, int i)
{
	double	x;
	double	y;
	double	z;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '-')
		exit(er("error: doubles_acl_parse: map parsing:\n", str));
	x = ft_atof(str, i);
	i = skip_double(str, i, 0, 1);
	y = ft_atof(str, i);
	i = random_sum_parse(str, i);
	z = ft_atof(str, i);
	return (vdefine(x, y, z));
}
