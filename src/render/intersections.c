/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/06 19:27:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

//Return true if ray impacts on sphere object, t to save closest intersection
bool	intersect_sphere(t_ray ray, t_obj *sphere, float *t)
{
	t_v3		oc;
	t_quadratic	quad;
	float		radius;

	oc = vsubstract(ray.origin, sphere->pos);
	quad.a = dot(ray.direction, ray.direction);
	quad.b = 2.0f * dot(ray.direction, oc);
	radius = sphere->size / 2.0f;
	quad.c = dot(oc, oc) - (radius * radius);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
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

bool	intersect_plane(t_ray ray, t_obj *plane, float *t)
{
	float	denominator;
	float	numerator;
	t_v3	oc;

	denominator = dot(ray.direction, plane->axis);
	if (fabs(denominator) < 1e-6)
		return (false);
	oc = vsubstract(plane->pos, ray.origin);
	numerator = dot(oc, plane->axis);
	*t = numerator / denominator;
	if (*t <= 0)
		return (false);
	return (true);
}

