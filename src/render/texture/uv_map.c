/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:55:14 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/13 15:32:14 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v2	sphere_uv(t_v3 point, t_obj *sphere)
{
	t_v3	dir;
	t_v2	uv;

	dir = normalize(vsub(point, sphere->pos));
	uv.u = 0.5 + atan2(dir.z, dir.x) / (2 * M_PI);
	uv.v = 0.5 - asin(dir.y) / M_PI;
	return (uv);
}

t_v2	side_uv(t_v3 point, t_obj *plane)
{
	t_v3	local_pos;
	t_v3	tangent;
	t_v3	bitangent;
	t_v2	uv;

	local_pos = vsub(point, plane->pos);
	if (fabs(plane->axis.y) < fabs(plane->axis.x))
		tangent = vdefine(0, 1, 0);
	else
		tangent = vdefine(1, 0, 0);
	bitangent = cross(plane->axis, tangent);
	uv.u = dot(local_pos, tangent) / plane->size;
	uv.v = dot(local_pos, bitangent) / plane->height;
	if (uv.u < 0 || uv.u > 1 || uv.v < 0 || uv.v > 1)
	{
		uv.u = -1;
		uv.v = -1;
	}
	return (uv);
}

t_v2	plane_uv(t_v3 point, t_obj *plane)
{
	t_v3	local_pos;
	t_v3	tangent;
	t_v3	bitangent;
	t_v2	uv;

	local_pos = vsub(point, plane->pos);
	if (fabs(plane->axis.y) < fabs(plane->axis.x))
		tangent = vdefine(1, 0, 0);
	else
		tangent = vdefine(0, 1, 0);
	bitangent = cross(plane->axis, tangent);
	uv.u = dot(local_pos, tangent) / plane->size;
	uv.v = dot(local_pos, bitangent) / plane->height;
	if (uv.u < 0 || uv.u > 1 || uv.v < 0 || uv.v > 1)
	{
		uv.u = -1;
		uv.v = -1;
	}
	return (uv);
}

t_v2	cylinder_uv(t_v3 point, t_obj *cyl)
{
	t_v3	dir;
	t_v2	uv;

	dir = vsub(point, cyl->pos);
	uv.u = 0.5 + atan2(dir.z, dir.x) / (2 * M_PI);
	uv.v = dir.y / cyl->height;
	return (uv);
}

t_v2	cone_uv(t_v3 point, t_obj *cone)
{
	t_v3	local_pos;
	t_v2	uv;
	double	theta;
	double	height;

	local_pos = vsub(point, cone->pos);
	height = dot(local_pos, cone->axis);
	uv.v = height / cone->height;
	local_pos = vsub(local_pos, vmul(height, cone->axis));
	theta = atan2(local_pos.z, local_pos.x);
	if (theta < 0)
		theta += 2 * M_PI;
	uv.u = theta / (2 * M_PI);

	return (uv);
}

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

	x = (int)(uv.u * obj->texture->width) % obj->texture->width;
	y = (int)(uv.v * obj->texture->height) % obj->texture->height;
	index = (y * obj->texture->width + x) * 4;
	return (rgbdefine(obj->texture->pixels[index + 2], \
			obj->texture->pixels[index + 1], \
			obj->texture->pixels[index]));
}
