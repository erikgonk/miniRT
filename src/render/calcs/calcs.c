/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 17:38:09 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_obj	*find_closest(t_data *data, t_ray *ray, t_obj *objs, \
	double *t_min)
{
	t_obj	*closest_obj;
	t_obj	*obj;
	double	t;

	closest_obj = NULL;
	obj = objs;
	while (obj)
	{
		t = *t_min;
		if ((obj->type == SP && hit_sp(ray, obj, &t)) \
		|| ((obj->type == PL || obj->type == SIDE) && \
							hit_pl(data, ray, obj, &t)) \
		|| (obj->type == CY && hit_cy(ray, obj, &t)) \
		|| (obj->type == CAP && hit_cap(data, ray, obj, &t)) \
		|| (obj->type == CO && hit_cone(ray, obj, &t)))
		{
			if (t > 0 && t < *t_min)
			{
				*t_min = t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	return (closest_obj);
}

t_rgb	diffuse_ray(t_ray *ray, t_obj *closest, t_data *data, int depth)
{
	t_ray	new_ray;
	t_rgb	trace_color;

	if (closest->material.texture)
		return (rgbdefine(0, 0, 0));
	new_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	new_ray.direction = random_in_hemisphere(ray->normal);
	trace_color = path_trace(&new_ray, data, depth - 1);
	return (color_mul(trace_color, closest->material.reflectivity));
}

t_rgb	compute_direct_light(t_obj *obj, t_data *data, \
							t_ray *ray, t_rgb color)
{
	t_obj		*current_obj;
	t_direct	d;

	d.color = &color;
	current_obj = data->obj;
	d.specular_color = rgbdefine(0, 0, 0);
	d.slight = data->s_light;
	if (current_obj)
	{
		while (current_obj)
		{
			if (current_obj->material.m_type == EM && current_obj != obj)
				compute_emissive_light(current_obj, ray, &color, data);
			current_obj = current_obj->next;
		}
	}
	iter_lights(data, obj, ray, d);
	color = color_add(color, d.specular_color);
	return (color);
}

t_rgb	path_trace(t_ray *ray, t_data *data, int depth)
{
	t_obj		*closest;
	t_rgb		dirb[4];
	double		t;

	t = INFINITY;
	closest = find_closest(data, ray, data->obj, &t);
	if (pt_checks(closest, ray, dirb))
		return (rgbdefine(0, 0, 0));
	if (depth <= 0)
		return (rgbdefine(0, 0, 0));
	dirb[0] = compute_direct_light(closest, data, ray, dirb[3]);
	dirb[1] = (rgbdefine(0, 0, 0));
	if (closest->material.m_type == EM)
		dirb[3] = apply_self_emission(closest, dirb[3]);
	if (closest->material.m_type == -1)
		dirb[1] = diffuse_ray(ray, closest, data, depth);
	else if (closest->material.m_type == MT)
		dirb[1] = metallic_ray(ray, closest, data, depth);
	else if (closest->material.m_type == MR)
		dirb[1] = mirror_ray(ray, closest, data, depth);
	else if (closest->material.m_type == GL)
		dirb[1] = glass_ray(ray, closest, data, depth);
	dirb[2] = color_add(color_add(dirb[3], dirb[0]), dirb[1]);
	return (dirb[2]);
}

uint32_t	trace_ray(t_ray ray, t_data *data)
{
	double	t_min;
	t_obj	*closest_obj;
	t_rgb	c_global;

	t_min = INFINITY;
	closest_obj = find_closest(data, &ray, data->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	pthread_mutex_lock(data->m_trace);
	c_global = path_trace(&ray, data, 2);
	pthread_mutex_unlock(data->m_trace);
	return (get_colour(c_global));
}
