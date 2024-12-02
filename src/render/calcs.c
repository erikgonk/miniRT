/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 13:47:51 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

/**
 * solve_quadratic - Resuelve una ecuación cuadrática en la forma ax^2 + bx + c = 0.
 * @quad: Puntero a la estructura t_quadratic que contiene los coeficientes
 *        a, b, c y donde se almacenarán las soluciones t1 y t2.
 *
 * Esta función calcula el discriminante de la ecuación cuadrática (b^2 - 4ac).
 * Si el discriminante es negativo, no hay soluciones reales, y la función
 * retorna false. Si el discriminante es no negativo, calcula las dos raíces t1 y t2
 * y las almacena en la estructura t_quadratic.
 *
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
	quad->t1 = (-quad->b - sqrt_discriminant) / (2.0f * quad->a);
	quad->t2 = (-quad->b + sqrt_discriminant) / (2.0f * quad->a);
	return (true);
}

/**
 * trace_ray - Determina el color del píxel intersectado por un rayo.
 * @ray: Puntero al rayo que se desea trazar.
 * @scene: Puntero a la estructura que representa la escena (objetos, luces, etc.).
 *
 * Esta función recorre todos los objetos en la escena para determinar cuál es
 * el más cercano que intersecta el rayo. Si se encuentra un objeto, ajusta su
 * color base utilizando la iluminación ambiental de la escena. Si no hay intersección,
 * retorna un color de fondo (negro por defecto).
 *
 * Retorna un t_rgb que representa el color del píxel correspondiente al rayo.
 */
int trace_ray(t_ray ray, t_obj *objects)
{
	float	t_min = INFINITY; // Distancia mínima inicializada en infinito
	t_obj	*closest_object = NULL;
	// Iterar sobre todos los objetos
	for (t_obj *obj = objects; obj; obj = obj->next)
	{
		float t = INFINITY;
		// Determinar intersección en función del tipo de objeto
		if (obj->type == 's' && intersect_sphere(ray, obj, &t))
		{
			if (t < t_min)
			{
				t_min = t;
				closest_object = obj;
			}
		}
		// Otros tipos de objetos pueden añadirse aquí
		// e.g., if (obj->type == 'p') intersect_plane(ray, obj, &t);
	}
	// Retornar el color del objeto más cercano, o un color de fondo si no hay intersección
	if (closest_object)
		return get_colour(closest_object->rgb);
	return (0x000000); // Fondo negro
}
