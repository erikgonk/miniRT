/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 11:06:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/render.h"
#include "../../lib/libvector/libvct.h"

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

#define MAX_DEPTH 5

t_rgb	combine_colors(t_rgb c_local, t_rgb c_global)
{
	t_rgb	c_final;

	c_final.r = fminf((c_global.r * G_WEIGHT) + (c_local.r * L_WEIGHT), 255.0f);
	c_final.g = fminf((c_global.g * G_WEIGHT) + (c_local.g * L_WEIGHT), 255.0f);
	c_final.b = fminf((c_global.b * G_WEIGHT) + (c_local.b * L_WEIGHT), 255.0f);
	return (c_final);
}

t_v3 scalar_mult(t_v3 v, float scalar)
{
	t_v3 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

t_v3 reflect(t_ray *ray)
{
	float	dot_product;
	t_v3	scaled_normal;
	t_v3	reflected;

	dot_product = dot(ray->direction, ray->normal);
	scaled_normal = scalar_mult(ray->normal, 2 * dot_product);
	reflected = vsub(ray->direction, scaled_normal);
	return normalize(reflected);
}

float get_reflection_ratio(t_v3 incident, t_v3 normal, float n1, float n2)
{
    float cos_theta_i;
    float sin_theta_t2;
    float cos_theta_t;
    float r_perpendicular;
    float r_parallel;
    float reflection_ratio;

    cos_theta_i = fabs(dot(incident, normal));
    sin_theta_t2 = (n1 / n2) * (n1 / n2) * (1.0f - cos_theta_i * cos_theta_i);
    if (sin_theta_t2 > 1.0f)
        return (1.0f);
    cos_theta_t = sqrtf(1.0f - sin_theta_t2);
    r_perpendicular = (n1 * cos_theta_i - n2 * cos_theta_t) /
                      (n1 * cos_theta_i + n2 * cos_theta_t);
    r_parallel = (n2 * cos_theta_i - n1 * cos_theta_t) /
                 (n2 * cos_theta_i + n1 * cos_theta_t);
    r_perpendicular = r_perpendicular * r_perpendicular;
    r_parallel = r_parallel * r_parallel;
    reflection_ratio = (r_perpendicular + r_parallel) / 2.0f;

    return (reflection_ratio);
}

t_rgb blend_colors(t_rgb color1, t_rgb color2, t_obj *obj)
{
    t_rgb	result;
	float	weight1;
	float	weight2;

	if (obj->material.m_type == MT)
	{
		weight1 = 0.7;
		weight2 = 0.3;
	}
	if (obj->material.m_type == GL)
	{
		weight1 = 0;
		weight2 = 1;
	}
    result.r = fmin(255, fmax(0, color1.r * weight1 + color2.r * weight2));
    result.g = fmin(255, fmax(0, color1.g * weight1 + color2.g * weight2));
    result.b = fmin(255, fmax(0, color1.b * weight1 + color2.b * weight2));
    return result;
}

float get_reflection_ratio_non_metallic(float cos_theta_i)
{
    float R_0 = 0.04;
    return R_0 + (1 - R_0) * pow(1 - cos_theta_i, 5);
}

t_rgb	path_tracer(t_data *data, t_ray ray, t_obj *obj, int m_depth)
{
	t_obj	*closest_obj;
	t_ray	new_ray;
	t_rgb	color = {0, 0, 0};
	t_rgb	reflected_color = {0, 0, 0};
	t_rgb	diffuse_color = {0, 0, 0};
	float	reflection_ratio = 0;
	float	t_min = INFINITY;
	int		flag = 0;

		printf("entra\n");
	if (m_depth <= 0)
		return ((t_rgb){0, 0, 0});

	closest_obj = find_closest_object(&ray, obj, &t_min);
	if (!closest_obj)
		return ((t_rgb){0, 0, 0});
	diffuse_color = phong(data, &ray, closest_obj);

	if (closest_obj->material.m_type != 0)
	{
		reflection_ratio = get_reflection_ratio(ray.direction, ray.normal, 1.0f, 1.5f);
		// reflection_ratio *= closest_obj->material.m_type;
		new_ray.origin = vadd(ray.point, vmul(EPSILON, ray.normal));
		new_ray.direction = reflect(&ray);
		reflected_color = path_tracer(data, new_ray, closest_obj, m_depth - 1);
		color = blend_colors(diffuse_color, reflected_color, obj);
	}
	else
	{
		reflection_ratio = get_reflection_ratio_non_metallic(dot(ray.direction, ray.normal));
		color = diffuse_color;
	}
	return (color);
}

uint32_t	trace_ray(t_ray ray, t_data *data)
{
	float	t_min;
	t_obj	*closest_obj;
	t_rgb	c_global;

	t_min = INFINITY;
	closest_obj = find_closest_object(&ray, data->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	if (closest_obj->material.m_type != -1)
		
	else
	{
		c_global = phong(data, &ray, closest_obj);
		specular_light(&c_global, data, &ray);
	}
	return (get_colour(c_global));
}
