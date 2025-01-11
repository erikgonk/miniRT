/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:27:29 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 10:07:12 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void calculate_sphere_tangent_bitangent(t_v3 normal, t_v3 *tangent, t_v3 *bitangent)
{
	// Suponiendo normal ya normalizada
	t_v3 up;

	// Usa un vector arbitrario para "up" que no sea paralelo a la normal
	up = (fabs(normal.y) < 0.99) ? vdefine(0, 1, 0) : vdefine(1, 0, 0);

	// Calcula el tangente (perpendicular a normal y up)
	*tangent = cross(up, normal);
	*tangent = normalize(*tangent);

	// Calcula el bitangente (perpendicular a tangente y normal)
	*bitangent = cross(normal, *tangent);
	*bitangent = normalize(*bitangent);
}

t_v3 transform_to_world_space(t_v3 tangent, t_v3 bitangent, t_v3 normal, t_v3 map_normal)
{
	t_v3 world_normal;

	world_normal.x = map_normal.x * tangent.x + map_normal.y * bitangent.x + map_normal.z * normal.x;
	world_normal.y = map_normal.x * tangent.y + map_normal.y * bitangent.y + map_normal.z * normal.y;
	world_normal.z = map_normal.x * tangent.z + map_normal.y * bitangent.z + map_normal.z * normal.z;
	return (normalize(world_normal));
}

t_v3	get_normal_from_map(t_obj *sphere, t_ray *ray)
{
	int x, y;
	int index;
	uint8_t r, g, b;
	t_v3 normal;
	float	u;
	float	v;
	double	tiles;

	u = 0.5 + atan2(ray->normal.z, ray->normal.x) / (2 * M_PI);
	v = 0.5 - asin(ray->normal.y) / M_PI;
	u = fmod((u * tiles), 1.0f);
	if (u < 0) u += 1.0f;
	v = fmod((v * tiles), 1.0f);
	if (v < 0) v += 1.0f;

	x = (int)(u * sphere->material.texture->width * sphere->material.bm_size) % sphere->material.texture->width;
	y = (int)(v * sphere->material.texture->height * sphere->material.bm_size) % sphere->material.texture->height;
	index = (y * sphere->material.texture->width + x) * sphere->material.texture->bytes_per_pixel;
	r = sphere->material.texture->pixels[index];
	g = sphere->material.texture->pixels[index + 1];
	b = sphere->material.texture->pixels[index + 2];
	normal.x = (r / 255.0f) * 2.0f - 1.0f;
	normal.y = (g / 255.0f) * 2.0f - 1.0f;
	normal.z = (b / 255.0f) * 2.0f - 1.0f;
	return (normalize(normal));
}

void	get_sphere_normal(t_obj *sphere, t_v3 hit_point, t_ray *ray)
{
	t_v3		map_normal;
	t_v3		tangent;
	t_v3		bitangent;

	if (sphere->material.texture)
	{
		map_normal = get_normal_from_map(sphere, ray);
		calculate_sphere_tangent_bitangent(ray->normal, &tangent, &bitangent);
		ray->normal = transform_to_world_space(tangent, bitangent, ray->normal, map_normal);
	}
}
