/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 12:25:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

/**
 * solve_quadratic - Resuelve una ecuación cuadrática
 * en la forma ax^2 + bx + c = 0.
 * @quad: Puntero a la estructura t_quadratic que contiene los coeficientes
 *        a, b, c y donde se almacenarán las soluciones t1 y t2.
 * Retorna true si la ecuación tiene soluciones reales, o false si no las tiene.
 * t1 y t2 representa cuando el rayo entra y sale del objeto, si solo hay t2,
 * significa que el rayo empezó dentro del objeto, y solo esta el
 * impacto de salida
 */
bool	solve_quadratic(t_quadratic *quad)
{
	float	sqrt_discriminant;
	float	temp;

	if (quad->discriminant < 0 || fabs(quad->a) < EPSILON)
		return (false);
	sqrt_discriminant = sqrtf(quad->discriminant);
	quad->t1 = (-quad->b - sqrt_discriminant) / (2.0f * quad->a);
	quad->t2 = (-quad->b + sqrt_discriminant) / (2.0f * quad->a);
	if (quad->t1 > quad->t2)
	{
		temp = quad->t1;
		quad->t1 = quad->t2;
		quad->t2 = temp;
	}
	return (true);
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
		|| (obj->type == CY && hit_cy(ray, obj, &t) \
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

/**
 * trace_ray - Determina el color del píxel intersectado por un rayo.
 * @ray: Puntero al rayo que se desea trazar.
 * @scene: Puntero a la estructura que representa
 * la escena (objetos, luces, etc.).
 *
 * Esta función recorre todos los objetos en la escena para determinar cuál es
 * el más cercano que intersecta el rayo. Si se encuentra un objeto, ajusta su
 * color base utilizando la iluminación ambiental de la escena.
 * Si no hay intersección,
 * retorna un color de fondo (negro por defecto).
 *
 * Retorna un t_rgb que representa el color del píxel correspondiente al rayo.
 */
uint32_t	trace_ray(t_ray ray, t_data *scene)
{
	float	t_min;
	t_v3	norm;
	t_obj	*closest_obj;
	t_rgb	color;

	t_min = INFINITY;
	closest_obj = find_closest_object(&ray, scene->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	color = phong(scene, &ray, closest_obj);
	return (get_colour(color));
}
