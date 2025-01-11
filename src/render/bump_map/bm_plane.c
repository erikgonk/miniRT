/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:27:29 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 11:43:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void calculate_plane_tangent_bitangent(t_v3 normal, t_v3 *tangent, t_v3 *bitangent)
{
	t_v3 up;

	up = (fabs(normal.y) < 0.99) ? vdefine(0, 1, 0) : vdefine(1, 0, 0);
	*tangent = cross(up, normal);
	*tangent = normalize(*tangent);
	*bitangent = cross(normal, *tangent);
	*bitangent = normalize(*bitangent);
}

static t_v3 transform_to_world_space(t_v3 tangent, t_v3 bitangent, t_v3 normal, t_v3 map_normal)
{
	t_v3 world_normal;

	world_normal.x = map_normal.x * tangent.x + map_normal.y * bitangent.x + map_normal.z * normal.x;
	world_normal.y = map_normal.x * tangent.y + map_normal.y * bitangent.y + map_normal.z * normal.y;
	world_normal.z = map_normal.x * tangent.z + map_normal.y * bitangent.z + map_normal.z * normal.z;
	return (normalize(world_normal));
}

t_v3 get_normal_from_map_plane(t_obj *plane, t_v3 hit_point)
{
	int x, y, index;
	uint8_t r, g, b;
	t_v3 normal;
	float u, v;

	u = fmod(hit_point.x, 1.0f);
	if (u < 0)
		u += 1.0f;
	v = fmod(hit_point.z, 1.0f);
	if (v < 0)
		v += 1.0f;

	x = (int)(u * plane->material.texture->width * plane->material.bm_size) % plane->material.texture->width;
	y = (int)(v * plane->material.texture->height * plane->material.bm_size) % plane->material.texture->height;
	index = (y * plane->material.texture->width + x) * plane->material.texture->bytes_per_pixel;

	r = plane->material.texture->pixels[index];
	g = plane->material.texture->pixels[index + 1];
	b = plane->material.texture->pixels[index + 2];

	normal.x = (r / 255.0f) * 2.0f - 1.0f;
	normal.y = (g / 255.0f) * 2.0f - 1.0f;
	normal.z = (b / 255.0f) * 2.0f - 1.0f;
	return (normalize(normal));
}

void get_plane_normal(t_obj *plane, t_v3 hit_point, t_ray *ray)
{
	t_v3 map_normal;
	t_v3 tangent;
	t_v3 bitangent;

	if (plane->material.texture)
	{
		map_normal = get_normal_from_map_plane(plane, hit_point);
		calculate_plane_tangent_bitangent(plane->axis, &tangent, &bitangent);
		ray->normal = transform_to_world_space(tangent, bitangent, plane->axis, map_normal);
	}
}
