/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 13:53:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

//Return true if ray impacts on sphere object
bool	intersect_sphere(t_ray ray, t_obj *sphere, float *t)
{
	t_v3		oc;
	t_quadratic	quad;

	oc = vsubstract(ray.origin, sphere->pos);  // Vector desde el origen del rayo al centro de la esfera
	// Coeficientes de la ecuación cuadrática
	float a = dot(ray.direction, ray.direction);
	float b = 2.0f * dot(oc, ray.direction);
	float c = dot(oc, oc) - sphere->size * sphere->size; // size = radio
	init_quadratic(&quad, a, b, c);
	if (!solve_quadratic(&quad))
		return (false);
	if (quad.t1 > 0)
		*t = quad.t1;
	else if (quad.t2 > 0)
		*t = quad.t2;
	else
		return (false);
	return (true);
}
