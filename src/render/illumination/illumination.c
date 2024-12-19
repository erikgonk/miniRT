/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:09:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 17:52:20 by shurtado         ###   ########.fr       */
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

bool	scene_shadow(t_data *scene, t_ray *shadow_ray, float max_dist)
{
	t_obj	*current_obj;
	float	t;

	t = INFINITY;
	current_obj = scene->obj;
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

t_v3 vneg(t_v3 v)
{
	t_v3 result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;

	return result;
}

t_v3 reflect(t_v3 v, t_v3 n)
{
    float dot_product;
    t_v3 result;

    // Calcular el producto escalar (v . n)
    dot_product = dot(v, n);

    // Aplicar la fórmula de reflexión
    result.x = v.x - 2 * dot_product * n.x;
    result.y = v.y - 2 * dot_product * n.y;
    result.z = v.z - 2 * dot_product * n.z;

    return result;
}

void specular_light(t_rgb *color, t_slight *slight, float intensity)
{
    color->r += slight->rgb.r * intensity;
    color->g += slight->rgb.g * intensity;
    color->b += slight->rgb.b * intensity;
}

t_rgb	phong(t_data *scene, t_ray *ray, t_obj *obj)
{
	t_rgb		color;
	t_ray		shadow_ray;
	t_slight	*slight;
	float		intensity;

	color = obj->a_rgb;
	slight = scene->s_light;
	while (slight)
	{
		shadow_ray.origin = vadd(ray->point, vmul(1e-3, ray->normal));
		shadow_ray.direction = normalize(vsub(slight->pos, ray->point));
		if (scene_shadow(scene, &shadow_ray, vlength(vsub(slight->pos,
						ray->point))))
		{
			slight = slight->next;
			continue ;
		}
		intensity = fmax(dot(shadow_ray.direction, ray->normal), 0.0f);
		difuse_light(&color, slight, obj, intensity);
		// specular_light(&color, )
		float		spec_intensity;
		t_v3		view_dir;
		t_v3		reflection;
		view_dir = normalize(vneg(ray->direction));
		reflection = reflect(vneg(shadow_ray.direction), ray->normal);
		spec_intensity = pow(fmax(dot(reflection, view_dir), 0.0f), 252);
		specular_light(&color, slight, spec_intensity);
		slight = slight->next;
	}
	return (color);
}
