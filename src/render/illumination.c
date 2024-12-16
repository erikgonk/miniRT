/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:09:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 00:53:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	scene_shadow(t_data *scene, t_ray *shadow_ray, float max_dist)
{
	t_obj	*current_obj;
	float	t;

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
		// Agregar más tipos de objetos si es necesario
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

	// Luz ambiental (escalado del color)
	ambient_color.r = (unsigned char)(obj->rgb.r * scene->aLight->br);
	ambient_color.g = (unsigned char)(obj->rgb.g * scene->aLight->br);
	ambient_color.b = (unsigned char)(obj->rgb.b * scene->aLight->br);
	color = ambient_color;

	// Luz difusa y sombras
	for (int i = 0; i < 1; i++)
	{
		// Dirección hacia la luz
		light_dir = normalize(vsubstract(scene->sLight[i].pos, ray->point));

		// Sombras: verificar si hay un objeto entre el punto y la luz
		shadow_origin = vadd(ray->point, vmul(EPSILON, ray->normal));
		shadow_ray.origin = shadow_origin;
		shadow_ray.direction = light_dir;

		shadow_t = INFINITY;
		if (scene_shadow(scene, &shadow_ray, vlength(vsubstract(scene->sLight[i].pos, ray->point))))
			continue;

		// Cálculo de iluminación difusa
		diffuse_intensity = dot(light_dir, ray->normal);
		if (diffuse_intensity > 0.0f)
		{
			diffuse_color.r = (unsigned char)(scene->sLight[i].rgb.r * diffuse_intensity * scene->sLight[i].br);
			diffuse_color.g = (unsigned char)(scene->sLight[i].rgb.g * diffuse_intensity * scene->sLight[i].br);
			diffuse_color.b = (unsigned char)(scene->sLight[i].rgb.b * diffuse_intensity * scene->sLight[i].br);

			// Acumular iluminación difusa
			color.r = fmin(color.r + (obj->rgb.r * diffuse_color.r) / 255, 255);
			color.g = fmin(color.g + (obj->rgb.g * diffuse_color.g) / 255, 255);
			color.b = fmin(color.b + (obj->rgb.b * diffuse_color.b) / 255, 255);
		}
	}

	return (color);
}


/*
t_material	init_material(void)
{
	t_material	material;

	material.c_ambien = 0.1f;   // Reflexión ambiental por defecto
	material.c_diffuse = 0.7f;  // Reflexión difusa por defecto
	material.c_specular = 0.2f; // Reflexión especular por defecto
	material.n = 50;           
		// Exponente especular por defecto (brillo concentrado)
	return (material);
}

t_v3	get_normal(t_obj *obj, t_v3 point)
{
	t_v3	axis_normalized;
	t_v3	proj;

	if (obj->type == SP)
	{
		return (normalize(vsubstract(point, obj->pos)));
	}
	else if (obj->type == PL)
	{
		return (normalize(obj->axis));
	}
	else if (obj->type == CY)
	{
		// Considerar las tapas del cilindro
		axis_normalized = normalize(obj->axis);
		proj = vmul(dot(vsubstract(point, obj->pos), axis_normalized),
				axis_normalized);
		// Si el punto está en las tapas
		if (fabs(dot(vsubstract(point, obj->pos),
					axis_normalized)) >= obj->height / 2.0)
			return (axis_normalized);
		// Normal de la superficie lateral
		return (normalize(vsubstract(vsubstract(point, obj->pos), proj)));
	}
	// Default normal if no specific type matches
	return ((t_v3){0, 0, 0});
}
/*
t_v3	get_normal(t_obj *obj, t_v3 point)
{
	t_v3	proj;

	if (obj->type == SP)
		return (normalize(vsubstract(point, obj->pos)));
	else if (obj->type == PL)
		return (obj->axis);
	else if (obj->type == CY)
	{
		proj = vmul(dot(vsubstract(point, obj->pos), obj->axis), obj->axis);
		return (normalize(vsubstract(vsubstract(point, obj->pos), proj)));
	}
	// Default normal if no specific type matches
	return ((t_v3){0, 0, 0});
}

t_rgb	add_colors(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	result.r = fmin(c1.r + c2.r, 255);
	result.g = fmin(c1.g + c2.g, 255);
	result.b = fmin(c1.b + c2.b, 255);
	return (result);
}

t_rgb	phong_illumination(t_obj *obj, t_v3 point, t_v3 normal, t_ray ray,
		t_sLight light)
{
	t_rgb	color;
	t_v3 l;        // Vector hacia la luz
	t_v3 r;        // Vector reflejado
	t_v3 v;        // Vector hacia el observador
	float ambient; //F Componente ambiental
	float diff;    // Componente difusa
	float spec;    // Componente especular

	obj->material = init_material();
// Calcular el vector hacia la luz
	l = normalize(vsubstract(light.pos, point));
// Calcular el vector hacia el observador (desde el punto hacia el origen del rayo)
	v = normalize(vsubstract(ray.origin, point));
// Componente ambiental: una fracción constante de la luz ambiental
	ambient = 0.2 * obj->material.c_ambien;
// Componente difusa: depende del ángulo entre la luz y la normal
	diff = dot(normal, l);
// Si el ángulo es mayor de 90 grados, la luz no afecta
	if (diff < 0)
		diff = 0;
	diff *= light.br * obj->material.c_diffuse;
// Ajustar con el coeficiente difuso
// Vector reflejado respecto a la normal
	r = vsubstract(vmul(2 * dot(normal, l), normal), l);
// Componente especular: brillo concentrado hacia el observador
	spec = dot(r, v);
// Si el ángulo reflejado no apunta hacia el observador, no hay brillo
	if (spec < 0)
		spec = 0;
	spec = pow(spec, obj->material.n);          
// Elevar al exponente especular para concentrar el brillo
	spec *= light.br * obj->material.c_specular;
// Ajustar con el coeficiente especular
// Combinar todas las componentes y multiplicar por el color de la luz
	color.r = light.rgb.r * (ambient + diff + spec);
	color.g = light.rgb.g * (ambient + diff + spec);
	color.b = light.rgb.b * (ambient + diff + spec);
// Limitar los valores del color a 255
	color.r = fmin(color.r, 255);
	color.g = fmin(color.g, 255);
	color.b = fmin(color.b, 255);
	return (color);
}

// Función principal para calcular la iluminación Phong
// Se llama para cada punto de intersección
t_rgb	render_phong(t_ray ray, t_obj *obj, t_sLight *lights, float t)
{
	t_v3		point;
	t_v3		normal;
	t_sLight	*current_light;
	t_rgb		pixel;

	obj->axis = normalize(obj->axis);
	pixel = (t_rgb){0, 0, 0};
// Calcular el punto de intersección
	point = vadd(ray.origin, vmul(t, ray.direction));
// Obtener la normal en el punto de intersección
	normal = get_normal(obj, point);
// Recorrer todas las luces en la escena
	current_light = lights;
	while (current_light)
	{
// Sumar la contribución de cada luz
		pixel = add_colors(obj->rgb, phong_illumination(obj, point, normal, ray,
					*current_light));
		current_light = current_light->next;
	}
	return (pixel);
}
*/