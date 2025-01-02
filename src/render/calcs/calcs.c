/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/02 17:58:46 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/render.h"
#include "../../lib/libvector/libvct.h"
#include <float.h>

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void swap(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
		|| obj->type == CAP && hit_cap(ray, obj, &t) \
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

t_rgb color_mul(t_rgb c, float factor)
{
	t_rgb result;

	result.r = fmin(c.r * factor, 255);
	result.g = fmin(c.g * factor, 255);
	result.b = fmin(c.b * factor, 255);
	return result;
}

t_rgb color_add(t_rgb c1, t_rgb c2)
{
	t_rgb result;

	result.r = fmin(c1.r + c2.r, 255);
	result.g = fmin(c1.g + c2.g, 255);
	result.b = fmin(c1.b + c2.b, 255);
	return result;
}

t_v3 refract(t_obj *obj, t_v3 dir, t_v3 normal, float refractive_index)
{
	float cosi;
	float eta;
	float k;

	cosi = fmax(-1, fmin(1, dot(dir, normal)));
	eta = obj->calcs.eta2;
	if (cosi > 0)
		eta = obj->calcs.eta_reverse2;
	k = 1 - eta * (1 - cosi * cosi);
	if (k < 0)
		return ((t_v3){0, 0, 0});
	return (vadd(vmul(eta, dir), vmul(eta * cosi - sqrtf(k), normal)));
}

t_v3 reflect(t_v3 dir, t_v3 normal)
{
	return vsub(dir, vmul(2 * dot(dir, normal), normal));
}

float fresnel(t_obj *obj, t_v3 dir, t_v3 normal, float refractive_index)
{
	float cosi;
	float etai_etat;
	float etai;
	float etat;
	float sint;
	float cost;
	float Rs;
	float Rp;

	etat = obj->calcs.etat;
	etai = obj->calcs.etai;
	etai_etat = obj->calcs.etai_etat;
	cosi = fabs(dot(dir, normal));
	if (dot(dir, normal) > 0)
	{
		etat = obj->calcs.etai;
		etai = obj->calcs.etat;
		etai_etat = obj->calcs.etai_etat_reverse;
	}
	sint = etai_etat * sqrtf(fmax(0.f, 1 - cosi * cosi));
	if (sint >= 1)
		return 1;
	cost = sqrtf(fmax(0.f, 1 - sint * sint));
	Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
	Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
	return (Rs * Rs + Rp * Rp) / 2;
}

t_rgb glass_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray refracted_ray;
	t_ray reflected_ray;
	t_rgb reflected_color;
	t_rgb refracted_color;
	float kr;

	kr = fresnel(closest_object, ray->direction, ray->normal, 1.5);
	refracted_ray.origin = vadd(ray->point, vmul(-EPSILON, ray->normal));
	refracted_ray.direction = refract(closest_object, ray->direction, ray->normal, 1.5);
	reflected_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	reflected_ray.direction = reflect(ray->direction, ray->normal);
	reflected_color = path_trace(&reflected_ray, data, depth - 1);
	refracted_color = path_trace(&refracted_ray, data, depth - 1);
	return color_add(color_mul(reflected_color, kr),
					 color_mul(refracted_color, 1.0f - kr));
}

t_rgb mirror_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray		new_ray;
	t_v3		normal;
	t_rgb		pt;
	t_rgb		res;

	normal = ray->normal;
	new_ray.origin = vadd(ray->point, vmul(EPSILON, normal));
	new_ray.direction = reflect(ray->direction, normal);
	pt = path_trace(&new_ray, data, depth - 1);
	res = color_mul(pt, closest_object->material.reflectivity);
	return (res);
}

t_v3 perturb_vector(t_v3 direction, float roughness, t_v3 normal)
{
	t_v3 random_vector;
	random_vector = random_in_hemisphere(normal);
	return normalize(vadd(direction, vmul(roughness, random_vector)));
}

t_rgb metallic_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray		new_ray;
	t_v3		perturbed_direction;
	t_v3		adjusted_normal;

	new_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	new_ray.direction = reflect(ray->direction, ray->normal);
	if (closest_object->material.roughness > 0)
	{

		perturbed_direction = perturb_vector(new_ray.direction, closest_object->material.roughness, ray->normal);
		new_ray.direction = perturbed_direction;
	}
	return (color_mul(path_trace(&new_ray, data, depth - 1), closest_object->material.reflectivity));
}


t_v3 random_in_hemisphere(t_v3 normal)
{
	t_v3		random_vector;
	float		u1;
	float		u2;
	float		theta;
	float		phi;

	u1 = (float)rand() / FLT_MAX;
	u2 = (float)rand() / FLT_MAX;
	theta = acos(sqrt(1 - u1));
	phi = 2 * M_PI * u2;
	random_vector.x = sin(theta) * cos(phi);
	random_vector.y = sin(theta) * sin(phi);
	random_vector.z = cos(theta);
	if (dot(random_vector, normal) < 0)
		random_vector = vmul(-1.0f, random_vector);
	return normalize(random_vector);
}

t_v3 calculate_ray_direction(t_ray *ray, t_obj *obj)
{
	t_v3 adjusted_normal;

	if (obj->type == CY)
	{
		adjusted_normal = vsub(ray->point, vadd(obj->pos, vmul(dot(vsub(ray->point, obj->pos), obj->axis), obj->axis)));
		adjusted_normal = normalize(adjusted_normal);
		return (random_in_hemisphere(adjusted_normal));
	}
	else
		return (random_in_hemisphere(ray->normal));
}

t_rgb diffuse_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray new_ray;
	t_v3 normal;
	t_rgb trace_color;

	new_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	normal = ray->normal;
	new_ray.direction = calculate_ray_direction(ray, closest_object);
	trace_color = path_trace(&new_ray, data, depth - 1);
	return (color_mul(trace_color, closest_object->material.reflectivity));
}

t_rgb compute_direct_light(t_obj *obj, t_data *data, t_ray *ray, t_rgb color)
{
	t_slight	*slight;
	t_ray		shadow_ray;
	t_rgb		specular_color;
	float		intensity;
	t_v3		vsub_pos_point;
	t_v3		reflect_dir;
	t_v3		view_dir;
	float		spec_intensity;

	specular_color = RGB_BLACK;
	slight = data->s_light;
	while (slight)
	{
		vsub_pos_point = vsub(slight->pos, ray->point);
		shadow_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
		shadow_ray.direction = normalize(vsub_pos_point);
		if (data_shadow(data, &shadow_ray, vlength(vsub_pos_point)))
		{
			slight = slight->next;
			continue;
		}
		intensity = fmax(0.0f, dot(shadow_ray.direction, ray->normal));
		difuse_light(&color, slight, obj, intensity);
		if (obj->material.specularity > 0)
		{
			reflect_dir = reflect(vmul(-1, shadow_ray.direction), ray->normal);
			view_dir = normalize(vmul(-1, ray->direction));
			spec_intensity = pow(fmax(dot(reflect_dir, view_dir), 0.00), obj->material.shininess);
			specular_color = color_add(specular_color, color_mul(slight->rgb, spec_intensity * obj->material.specularity));
		}
		slight = slight->next;
	}
	return (color_add(color, specular_color));
}

t_rgb path_trace(t_ray *ray, t_data *data, int depth)
{
	t_obj		*closest_object;
	t_rgb		direct_light;
	t_rgb		indirect_light;
	float		t;
	t_rgb		result;
	t_rgb		base_color;

	t = INFINITY;
	closest_object = find_closest_object(ray, data->obj, &t);
	if (!closest_object)
		return (RGB_BLACK);
	if (closest_object->type == PL && closest_object->material.board_scale != -1)
		base_color = checkerboard_color(closest_object, ray->point);
	else
		base_color = closest_object->a_rgb;
	if (depth <= 0)
		return (RGB_BLACK);
	direct_light = compute_direct_light(closest_object, data, ray, base_color);
// hasta aqui juntos (revisar proximo dia por si ves algo que yo no vi)
	indirect_light = (RGB_BLACK);
	if (closest_object->material.m_type == -1)
		indirect_light = diffuse_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == MT)
		indirect_light = metallic_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == MR)
		indirect_light = mirror_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == GL)
		indirect_light = glass_ray(ray, closest_object, data, depth);
	result = color_add(color_add(base_color, color_add(closest_object->a_rgb, direct_light)), indirect_light);
	return (result);
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
	pthread_mutex_lock(data->m_trace);
	if (data->trace_flag)
		c_global = phong(data, &ray, closest_obj);
	else
		c_global = path_trace(&ray, data, MAX_DEPTH);
	pthread_mutex_unlock(data->m_trace);
	return (get_colour(c_global));
}
