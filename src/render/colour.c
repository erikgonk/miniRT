/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:19:01 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/15 17:23:13 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"

// From 0-255 BRGA colour Returns uint32 colour
uint32_t	get_acolour(t_uchar alpha, t_uchar r, t_uchar g, t_uchar b)
{
	return ((alpha << 24) | (b << 16) | (g << 8) | r);
}

uint32_t	get_colour(t_rgb color)
{
	return (get_acolour(255, color.r, color.g, color.b));
}

/**
 * Calcula el color final del objeto aplicando iluminación ambiental.
 * @obj_color: Color base del objeto (antes de la iluminación).
 * @ambient_light: Puntero a la luz ambiental que contiene el brillo y el color.
 *
 * Esta función ajusta el color del objeto en función de la luz ambiental.
 * La iluminación ambiental se calcula multiplicando el color base del objeto
 * por el brillo de la luz ambiental y sumando el color de la luz ambiental
 * ajustado por el mismo brillo. Los valores resultantes de cada canal (R, G, B)
 * se limitan al rango [0, 255] para evitar desbordamientos (con fminf).
 *
 * Retorna el color ajustado (t_rgb) con la iluminación ambiental aplicada.
 */
t_rgb	apply_ambient_light(t_rgb obj_color, t_aLight *ambient_light)
{
	t_rgb	result;
	float	bright;

	bright = ambient_light->br;
	result.r = fminf(obj_color.r * bright + ambient_light->rgb.r * bright, 255);
	result.g = fminf(obj_color.g * bright + ambient_light->rgb.g * bright, 255);
	result.b = fminf(obj_color.b * bright + ambient_light->rgb.b * bright, 255);
	return (result);
}
