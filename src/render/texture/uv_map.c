/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:55:14 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 17:24:46 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v2	calculate_uv(t_v3 point, t_obj *obj)
{
	t_v2	result;

	result.u = -1;
	result.v = -1;
	if (obj->type == SIDE)
		return (side_uv(point, obj));
	else if (obj->type == CY)
		return (cylinder_uv(point, obj));
	else if (obj->type == SP)
		return (sphere_uv(point, obj));
	else if (obj->type == PL)
		return (plane_uv(point, obj));
	else if (obj->type == CO)
		return (cone_uv(point, obj));
	else
		return (result);
}

t_rgb	texture_color(t_obj *obj, t_v2 uv)
{
	int	x;
	int	y;
	int	index;

	x = (int)(uv.u * obj->material.texture->width) % \
							obj->material.texture->width;
	y = (int)(uv.v * obj->material.texture->height) % \
							obj->material.texture->height;
	index = (y * obj->material.texture->width + x) * 4;
	return (rgbdefine(obj->material.texture->pixels[index + 2], \
			obj->material.texture->pixels[index + 1], \
			obj->material.texture->pixels[index]));
}
