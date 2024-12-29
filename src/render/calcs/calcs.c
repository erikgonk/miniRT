/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 14:15:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/render.h"
#include "../../lib/libvector/libvct.h"

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

t_v3 refract(t_v3 dir, t_v3 normal, float refractive_index)
{
	float cosi;
	float etai;
	float etat;
	float eta;
	float k;

	cosi = fmax(-1, fmin(1, dot(dir, normal)));
	etai = 1;
	etat = refractive_index;
	if (cosi > 0)
		swap(&etai, &etat);
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		return (t_v3){0, 0, 0};
	return vadd(vmul(eta, dir), vmul(eta * cosi - sqrtf(k), normal));
}

t_v3 reflect(t_v3 dir, t_v3 normal)
{
	return vsub(dir, vmul(2 * dot(dir, normal), normal));
}

float fresnel(t_v3 dir, t_v3 normal, float refractive_index)
{
	float cosi;
	float etai;
	float etat;
	float sint;
	float cost;
	float Rs;
	float Rp;

	cosi = fabs(dot(dir, normal));
	etai = 1;
	etat = refractive_index;
	if (dot(dir, normal) > 0)
		swap(&etai, &etat);
	sint = etai / etat * sqrtf(fmax(0.f, 1 - cosi * cosi));
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
	t_v3 normal;
	float kr;

	// Calcular la normal según el tipo de objeto
	if (closest_object->type == CY)
	{
		normal = vsub(ray->point, vadd(closest_object->pos, vmul(dot(vsub(ray->point, closest_object->pos), closest_object->axis), closest_object->axis)));
		normal = normalize(normal);
	}
	else
	{
		normal = ray->normal;
	}

	kr = fresnel(ray->direction, normal, 1.5);

	refracted_ray.origin = vadd(ray->point, vmul(-EPSILON, normal));
	refracted_ray.direction = refract(ray->direction, normal, 1.5);

	reflected_ray.origin = vadd(ray->point, vmul(EPSILON, normal));
	reflected_ray.direction = reflect(ray->direction, normal);

	reflected_color = path_trace(&reflected_ray, data, depth - 1);
	refracted_color = path_trace(&refracted_ray, data, depth - 1);

	return color_add(color_mul(reflected_color, kr),
					 color_mul(refracted_color, 1.0f - kr));
}

t_rgb mirror_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray new_ray;
	t_v3 normal;

	// Calcular la normal según el tipo de objeto
	if (closest_object->type == CY)
	{
		normal = vsub(ray->point, vadd(closest_object->pos, vmul(dot(vsub(ray->point, closest_object->pos), closest_object->axis), closest_object->axis)));
		normal = normalize(normal);
	}
	else
	{
		normal = ray->normal;
	}

	new_ray.origin = vadd(ray->point, vmul(EPSILON, normal));
	new_ray.direction = reflect(ray->direction, normal);

	return color_mul(
		path_trace(&new_ray, data, depth - 1),
		closest_object->material.reflectivity);
}

t_v3 perturb_vector(t_v3 direction, float roughness, t_v3 normal)
{
	t_v3 random_vector;
	random_vector = random_in_hemisphere(normal);
	return normalize(vadd(direction, vmul(roughness, random_vector)));
}

t_rgb metallic_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray new_ray;
	t_v3 perturbed_direction;

	new_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	new_ray.direction = reflect(ray->direction, ray->normal);

	if (closest_object->material.roughness > 0)
	{
		if (closest_object->type == CY)
		{
			t_v3 adjusted_normal = vsub(ray->point, vadd(closest_object->pos, vmul(dot(vsub(ray->point, closest_object->pos), closest_object->axis), closest_object->axis)));
			adjusted_normal = normalize(adjusted_normal);
			perturbed_direction = perturb_vector(new_ray.direction, closest_object->material.roughness, adjusted_normal);
		}
		else
		{
			perturbed_direction = perturb_vector(new_ray.direction, closest_object->material.roughness, ray->normal);
		}
		new_ray.direction = perturbed_direction;
	}

	return color_mul(
		path_trace(&new_ray, data, depth - 1),
		closest_object->material.reflectivity);
}


t_v3 random_in_hemisphere(t_v3 normal)
{
	t_v3 random_vector;

	random_vector.x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	random_vector.y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	random_vector.z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	while (vlength(random_vector) > 1.0f || vlength(random_vector) == 0)
	{
		random_vector.x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
		random_vector.y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
		random_vector.z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	}

	if (dot(random_vector, normal) < 0)
		random_vector = vmul(-1.0f, random_vector);

	return normalize(random_vector);
}

t_v3 calculate_ray_direction(t_ray *ray, t_obj *obj)
{
	if (obj->type == CY)
	{
		// Cilindro: ajustar normal según la superficie
		t_v3 adjusted_normal = vsub(ray->point, vadd(obj->pos, vmul(dot(vsub(ray->point, obj->pos), obj->axis), obj->axis)));
		adjusted_normal = normalize(adjusted_normal);
		return random_in_hemisphere(adjusted_normal);
	}
	else
		return random_in_hemisphere(ray->normal);
}

t_rgb diffuse_ray(t_ray *ray, t_obj *closest_object, t_data *data, int depth)
{
	t_ray	new_ray;
	t_rgb	base_color;
	t_rgb	trace_color;

	new_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
	new_ray.direction = calculate_ray_direction(ray, closest_object);
	trace_color = path_trace(&new_ray, data, depth - 1);
	base_color.r = fminf(trace_color.r * (base_color.r / 255), 255);
	base_color.g = fminf(trace_color.g * (base_color.g / 255), 255);
	base_color.b = fminf(trace_color.b * (base_color.b / 255), 255);

	return (base_color);
}

t_rgb compute_direct_light(t_obj *obj, t_data *data, t_ray *ray)
{
	t_rgb result;
	t_slight *slight;
	t_ray shadow_ray;
	float intensity;

	result = (t_rgb){0, 0, 0};
	slight = data->s_light;
	while (slight)
	{
		// Generar un rayo hacia la luz
		shadow_ray.origin = vadd(ray->point, vmul(EPSILON, ray->normal));
		shadow_ray.direction = normalize(vsub(slight->pos, ray->point));

		// Verificar sombras
		if (data_shadow(data, &shadow_ray, vlength(vsub(slight->pos,
						ray->point))))
		{
			slight = slight->next;
			continue;
		}

		// Calcular intensidad difusa
		intensity = fmax(0.0f, dot(shadow_ray.direction, ray->normal));
		result = color_add(result, color_mul(slight->rgb, intensity));
		slight = slight->next;
	}
	return result;
}

t_rgb path_trace(t_ray *ray, t_data *data, int depth)
{
	t_obj *closest_object;
	t_rgb direct_light;
	t_rgb indirect_light;
	float t;

	t = INFINITY;
	if (depth <= 0)
		return (RGB_BLACK);
	closest_object = find_closest_object(ray, data->obj, &t);
	if (!closest_object)
		return (RGB_BLACK);
	direct_light = compute_direct_light(closest_object, data, ray);
	indirect_light = (RGB_BLACK);
	if (closest_object->material.m_type == -1)
		indirect_light = diffuse_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == MT)
		indirect_light = metallic_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == MR)
		indirect_light = mirror_ray(ray, closest_object, data, depth);
	else if (closest_object->material.m_type == GL)
		indirect_light = glass_ray(ray, closest_object, data, depth);
	return color_add(direct_light, indirect_light);
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
	if (closest_obj->material.m_type == -1)
		c_global = phong(data, &ray, closest_obj);
	else
		c_global = path_trace(&ray, data, MAX_DEPTH);
	if (closest_obj->material.specularity > 0 || closest_obj->material.specularity == -1)
		specular_light(&c_global, data, &ray);
	return (get_colour(c_global));
}
