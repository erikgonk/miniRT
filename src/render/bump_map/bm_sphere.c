/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:27:29 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 13:36:15 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calc_sp_tb(t_v3 normal, t_v3 *tangent, t_v3 *bitangent)
{
	t_v3	up;

	if (fabs(normal.y) < 0.99)
		up = vdefine(0, 1, 0);
	else
		up = vdefine(1, 0, 0);
	*tangent = cross(up, normal);
	*tangent = normalize(*tangent);
	*bitangent = cross(normal, *tangent);
	*bitangent = normalize(*bitangent);
}

static t_v3	transform_tws(t_v3 tang, t_v3 bitang, t_v3 normal, t_v3 mp_nrmal)
{
	t_v3	w_normal;

	w_normal.x = mp_nrmal.x * tang.x + mp_nrmal.y * \
				bitang.x + mp_nrmal.z * normal.x;
	w_normal.y = mp_nrmal.x * tang.y + mp_nrmal.y * \
				bitang.y + mp_nrmal.z * normal.y;
	w_normal.z = mp_nrmal.x * tang.z + mp_nrmal.y * \
				bitang.z + mp_nrmal.z * normal.z;
	return (normalize(w_normal));
}

t_v3	get_normal_from_map(t_obj *sphere, t_ray *ray, int x, int y)
{
	int		index;
	t_rgb	rgb;
	t_v3	normal;
	float	uv[2];

	uv[0] = 0.5 + atan2(ray->normal.z, ray->normal.x) / (2 * M_PI);
	uv[1] = 0.5 - asin(ray->normal.y) / M_PI;
	uv[0] = fmod(uv[0], 1.0f);
	uv[1] = fmod(uv[1], 1.0f);
	x = (int)(uv[0] * sphere->material.texture->width * \
				sphere->material.bm_size) % sphere->material.texture->width;
	y = (int)(uv[1] * sphere->material.texture->height * \
				sphere->material.bm_size) % sphere->material.texture->height;
	index = (y * sphere->material.texture->width + x) * \
				sphere->material.texture->bytes_per_pixel;
	rgb.r = sphere->material.texture->pixels[index];
	rgb.g = sphere->material.texture->pixels[index + 1];
	rgb.b = sphere->material.texture->pixels[index + 2];
	normal.x = (rgb.r / 255.0f) * 2.0f - 1.0f;
	normal.y = (rgb.g / 255.0f) * 2.0f - 1.0f;
	normal.z = (rgb.b / 255.0f) * 2.0f - 1.0f;
	return (normalize(normal));
}

void	get_sphere_normal(t_obj *sphere, t_ray *ray)
{
	t_v3		map;
	t_v3		tangent;
	t_v3		bitangent;

	if (sphere->material.texture)
	{
		map = get_normal_from_map(sphere, ray, 0, 0);
		calc_sp_tb(ray->normal, &tangent, &bitangent);
		ray->normal = transform_tws(tangent, bitangent, ray->normal, map);
	}
}
