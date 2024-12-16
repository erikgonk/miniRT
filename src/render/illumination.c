/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:09:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 12:26:03 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	scene_shadow(t_data *scene, t_ray *shadow_ray, float max_dist)
{
	t_obj	*current_obj;
	float	t;

	t = INFINITY;
	current_obj = scene->obj;
	while (current_obj)
	{
		if (current_obj->type == SP && hit_sp(shadow_ray, current_obj, &t))
		{
			if (t > EPSILON && t < max_dist)
				return (true);
		}
		else if (current_obj->type == CY && hit_cy(shadow_ray, current_obj, &t))
		{
			if (t > EPSILON && t < max_dist)
				return (true);
		}
		else if (current_obj->type == PL && hit_pl(shadow_ray, current_obj, &t))
		{
			if (t > EPSILON && t < max_dist)
				return (true);
		}
		current_obj = current_obj->next;
	}
	return (false);
}

t_rgb	phong(t_data *scene, t_ray *ray, t_obj *obj)
{
	t_rgb	color;
	t_rgb	ambient_color;
	t_rgb	diffuse_color;
	t_v3	light_dir;
	t_v3	shadow_origin;
	t_ray	shadow_ray;
	float	diffuse_intensity;
	float	shadow_t;

	ambient_color.r = (unsigned char)(obj->rgb.r * scene->aLight->br);
	ambient_color.g = (unsigned char)(obj->rgb.g * scene->aLight->br);
	ambient_color.b = (unsigned char)(obj->rgb.b * scene->aLight->br);
	color = ambient_color;
	for (int i = 0; i < 1; i++)
	{
		light_dir = normalize(vsub(scene->sLight[i].pos, ray->point));
		shadow_origin = vadd(ray->point, vmul(EPSILON, ray->normal));
		shadow_ray.origin = shadow_origin;
		shadow_ray.direction = light_dir;
		shadow_t = INFINITY;
		if (scene_shadow(scene, &shadow_ray, \
			vlength(vsub(scene->sLight[i].pos, ray->point))))
			continue ;
		diffuse_intensity = dot(light_dir, ray->normal);
		if (diffuse_intensity > 0.0f)
		{
			diffuse_color.r = (unsigned char)(scene->sLight[i].rgb.r * diffuse_intensity * scene->sLight[i].br);
			diffuse_color.g = (unsigned char)(scene->sLight[i].rgb.g * diffuse_intensity * scene->sLight[i].br);
			diffuse_color.b = (unsigned char)(scene->sLight[i].rgb.b * diffuse_intensity * scene->sLight[i].br);
			color.r = fmin(color.r + (obj->rgb.r * diffuse_color.r) / 255, 255);
			color.g = fmin(color.g + (obj->rgb.g * diffuse_color.g) / 255, 255);
			color.b = fmin(color.b + (obj->rgb.b * diffuse_color.b) / 255, 255);
		}
	}
	return (color);
}
