/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/23 12:29:13 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include "render.h"

void	print_t_rgb(const char *label, t_rgb rgb)
{
	ft_printf(1, "%s -> r: %u, g: %u, b: %u\n", label, rgb.r, rgb.g, rgb.b);
}

void	print_t_v3(const char *label, t_v3 vec)
{
	ft_printf(1, "%s -> x: %.2f, y: %.2f, z: %.2f\n", label, vec.x, \
														vec.y, vec.z);
}

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	print_objects(t_obj *obj)
{
	if (obj)
	{
		ft_printf(1, "Objects:\n");
		while (obj)
		{
			ft_printf(1, "\tType: %d\n", obj->type);
			ft_printf(1, "\tIndex: %d\n", obj->i);
			print_t_v3("\tPosition", obj->pos);
			print_t_v3("\tAxis (Orientation)", obj->axis);
			print_t_rgb("\tColor", obj->rgb);
			ft_printf(1, "\tSize: %.2f\n", obj->size);
			ft_printf(1, "\tHeight: %.2f\n", obj->height);
			ft_printf(1, "\n");
			obj = obj->next;
		}
	}
	else
		ft_printf(1, "Objects: NULL\n");
}
