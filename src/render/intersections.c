/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/04 16:02:36 by shurtado         ###   ########.fr       */
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

	oc = vsubstract(ray.origin, sphere->pos);
	float a = dot(ray.direction, ray.direction);
	float b = 2.0f * dot(ray.direction, oc);
	float radius = sphere->size / 2.0f;
	float c = dot(oc, oc) - (radius * radius);
	float discriminante = (b * b) - (4 * a * c);
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
