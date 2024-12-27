/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:09:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/27 14:06:32 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

t_rgb	apply_ambient_light(t_rgb obj_color, t_alight *a_light)
{
	t_rgb	result;
	float	a_r;
	float	a_g;
	float	a_b;

	a_r = a_light->rgb.r / 255.0f;
	a_g = a_light->rgb.g / 255.0f;
	a_b = a_light->rgb.b / 255.0f;
	result.r = (unsigned char)fminf(obj_color.r * a_r * a_light->br, 255.0f);
	result.g = (unsigned char)fminf(obj_color.g * a_g * a_light->br, 255.0f);
	result.b = (unsigned char)fminf(obj_color.b * a_b * a_light->br, 255.0f);
	return (result);
}

void	difuse_light(t_rgb *color, t_slight *slight, t_obj *obj, float inty)
{
	t_rgb	dif_color;

	if (inty > 0.0f)
	{
		dif_color.r = (unsigned char)(slight->rgb_inty.r * inty);
		dif_color.g = (unsigned char)(slight->rgb_inty.g * inty);
		dif_color.b = (unsigned char)(slight->rgb_inty.b * inty);
		color->r = fmin(color->r + (obj->rgb.r * dif_color.r) / 255, 255);
		color->g = fmin(color->g + (obj->rgb.g * dif_color.g) / 255, 255);
		color->b = fmin(color->b + (obj->rgb.b * dif_color.b) / 255, 255);
	}
}

bool	data_shadow(t_data *data, t_ray *shadow_ray, float max_dist)
{
	t_obj	*current_obj;
	float	t;

	t = INFINITY;
	current_obj = data->obj;
	while (current_obj)
	{
		if (current_obj->type == SP && hit_sp(shadow_ray, current_obj, &t) && \
				(t > EPSILON && t < max_dist))
			return (true);
		else if (current_obj->type == CY && hit_cy(shadow_ray, current_obj, &t, \
				&shadow_ray->origin) && (t > EPSILON && t < max_dist))
			return (true);
		else if (current_obj->type == PL && hit_pl(shadow_ray, current_obj, &t) \
				&& (t > EPSILON && t < max_dist))
			return (true);
		current_obj = current_obj->next;
	}
	return (false);
}

t_rgb	phong(t_data *data, t_ray *ray, t_obj *obj)
{
	t_rgb		color;
	t_ray		shadow_ray;
	t_slight	*slight;
	float		intensity;

	if (obj->type == PL && obj->material.board_scale > 0)
		color = checkerboard_color(ray->point, obj->rgb, obj->material.rgb_checker, obj->material.board_scale);
	else
		color = obj->a_rgb;
	if (obj->type == SP)
		printf("hola\n");
	slight = data->s_light;
	while (slight)
	{
		shadow_ray.origin = vadd(ray->point, vmul(1e-3, ray->normal));
		shadow_ray.direction = normalize(vsub(slight->pos, ray->point));
		if (data_shadow(data, &shadow_ray, vlength(vsub(slight->pos,
						ray->point))))
		{
			slight = slight->next;
			continue ;
		}
		intensity = fmax(dot(shadow_ray.direction, ray->normal), 0.0f);
		difuse_light(&color, slight, obj, intensity);
		slight = slight->next;
	}
	return (color);
}
