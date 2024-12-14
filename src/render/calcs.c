/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/14 13:36:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

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

	if (quad->discriminant < 0)
		return (false);
	sqrt_discriminant = sqrtf(quad->discriminant);
	quad->t1 = (-quad->b - sqrt_discriminant) / (2.0f * quad->a); // entrada (entra en la figura)
	quad->t2 = (-quad->b + sqrt_discriminant) / (2.0f * quad->a); // salida (sale de la figura)

	return (true);
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
uint32_t	trace_ray(t_ray ray, t_obj *objects, t_aLight *light, t_sLight *sLight)
{
	float	t_min;
	float	t;
	t_obj	*obj;
	t_obj	*closest_object;

	t_min = INFINITY;
	closest_object = NULL;
	obj = objects;
	while (obj)
	{
		t = INFINITY;
		if (obj->type == SP && intersect_sphere(ray, obj, &t) && t < t_min)
		{
			t_min = t;
			closest_object = obj;
		}
		else if (obj->type == PL && intersect_plane(ray, obj, &t) && t < t_min)
		{
			t_min = t;
			closest_object = obj;
		}
		else if (obj->type == CY && intersect_cylinder(ray, obj, &t) && t < t_min)
		{
			t_min = t;
			closest_object = obj;
		}
		obj = obj->next;
	}
	if (closest_object)
		return (get_colour(render_phong(ray, closest_object, sLight, t)));
	return (BLACK);
}
