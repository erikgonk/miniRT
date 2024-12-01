/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilumination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:14:11 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/01 18:29:54 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
/*
int is_in_shadow(t_obj *obj, t_v3 point, t_sLight *light)
{
    t_v3 light_dir = subtract(light->pos, point);
    float mag = sqrtf(dot(light_dir, light_dir));
    light_dir = vDefine(light_dir.x / mag, light_dir.y / mag, light_dir.z / mag);

    // Cast a shadow ray from the point to the light source
    float t = sphere_ray_intersect(point, light_dir, obj->sphere_center, obj->sphere_radius);
    
    // If the ray intersects the sphere before reaching the light, it's in shadow
    return (t > 0.0f && t < mag);
}

uint32_t	new_light(t_sLight *l, t_obj *obj, t_v3 iPoint)
{
	float			mag;
	uint32_t		color; 
	t_v3			normal;
	t_v3			dir;	// light dir
	float			i;		// intensity 
	

	normal = subtract(iPoint, obj->sphere_center);
	mag = sqrtf(dot(normal, normal));
	normal = vDefine(normal.x / mag, normal.y / mag, normal.z / mag);

	// Calculate light direction
	dir = subtract(l->pos, iPoint);
	mag = sqrtf(dot(dir, dir));
	dir = vDefine(dir.x / mag, dir.y / mag, dir.z / mag);

	// Calculate lighting intensity
	i = fmaxf(dot(normal, dir), 0.0f) * l->br;

	if (is_in_shadow(obj, iPoint, l))
		i = 0.0f;  // No light if in shadow
	else
		i = fmaxf(dot(normal, dir), 0.0f) * l->br;
	// Apply lighting intensity to color
	color = obj->color;
	uint8_t r = fminf(((color >> 16) & 0xFF) * i, 255);
	uint8_t g = fminf(((color >> 8) & 0xFF) * i, 255);
	uint8_t b = fminf((color & 0xFF) * i, 255);
	return ((r << 16) | (g << 8) | b);
}

*/