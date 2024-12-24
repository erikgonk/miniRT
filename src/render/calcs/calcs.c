/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 11:54:24 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_obj	*find_closest_object(t_ray *ray, t_obj *objs, float *t_min)
{
	t_obj	*closest_obj;
	t_obj	*obj;
	float	t;

	closest_obj = NULL;
	obj = objs;
	while (obj)
	{
		t = *t_min;
		if ((obj->type == SP && hit_sp(ray, obj, &t)) \
		|| (obj->type == PL && hit_pl(ray, obj, &t)) \
		|| (obj->type == CY && hit_cy(ray, obj, &t, NULL) \
			))
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

t_v3	get_normal(t_obj *obj, t_v3 point)
{
	t_v3	proj;

	if (obj->type == SP)
		return (normalize(vsub(point, obj->pos)));
	else if (obj->type == PL)
		return (obj->axis);
	else if (obj->type == CY)
	{
		proj = vmul(dot(vsub(point, obj->pos), obj->axis), \
										obj->axis);
		return (normalize(vsub(vsub(point, obj->pos), proj)));
	}
	return ((t_v3){0, 0, 0});
}

t_rgb	combine_colors(t_rgb c_local, t_rgb c_global)
{
	t_rgb	c_final;

	c_final.r = fmaxf((c_global.r * G_WEIGHT) + (c_local.r * L_WEIGHT), 255.0f);
	c_final.g = fmaxf((c_global.g * G_WEIGHT) + (c_local.g * L_WEIGHT), 255.0f);
	c_final.b = fmaxf((c_global.b * G_WEIGHT) + (c_local.b * L_WEIGHT), 255.0f);
	return (c_final);
}

uint32_t	trace_ray(t_ray ray, t_data *data)
{
	float	t_min;
	t_obj	*closest_obj;
	t_rgb	color;

	t_min = INFINITY;
	closest_obj = find_closest_object(&ray, data->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	color = phong(data, &ray, closest_obj);
	// final_clolor = combine_colors(color, global_color);
	return (get_colour(color));
}
