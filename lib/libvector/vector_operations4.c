/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:06:58 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/20 10:08:13 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvct.h"

t_v3	vneg(t_v3 v)
{
	t_v3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

t_v3	vrefl(t_v3 v, t_v3 n)
{
	float	dot_product;
	t_v3	result;

	dot_product = dot(v, n);
	result.x = v.x - 2 * dot_product * n.x;
	result.y = v.y - 2 * dot_product * n.y;
	result.z = v.z - 2 * dot_product * n.z;
	return (result);
}
