/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 14:02:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

bool	calc_quad_sphere(t_obj *sphere, t_ray ray, t_quadratic *quad)
{
	t_v3	oc;
	float	radius;

	oc = vsub(ray.origin, sphere->pos);
	quad->a = dot(ray.direction, ray.direction);
	quad->b = 2.0f * dot(ray.direction, oc);
	radius = sphere->size / 2.0f;
	quad->c = dot(oc, oc) - (radius * radius);
	init_quadratic(quad, quad->a, quad->b, quad->c);
	if (!solve_quadratic(quad))
		return (false);
	return (true);
}

bool	hit_sp(t_ray *ray, t_obj *sphere, float *t)
{
	t_quadratic	quad;

	if (!calc_quad_sphere(sphere, *ray, &quad))
		return (false);
	if (quad.t1 > EPSILON && quad.t1 < *t)
		*t = quad.t1;
	else
		return (false);
	ray->point = vadd(ray->origin, vmul(*t, ray->direction));
	ray->normal = normalize(vsub(ray->point, sphere->pos));
	return (true);
}

bool	hit_pl(t_ray *ray, t_obj *plane, float *t)
{
	float	denominator;
	float	numerator;
	t_v3	oc;
	float	result;

	denominator = dot(ray->direction, plane->axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	oc = vsub(plane->pos, ray->origin);
	numerator = dot(oc, plane->axis);
	result = numerator / denominator;
	if (result > EPSILON && result < *t)
	{
		*t = result;
		ray->point = vadd(ray->origin, vmul(*t, ray->direction));
		if (dot(ray->direction, plane->axis) > EPSILON)
			ray->normal = vmul(-1.0f, plane->axis);
		else
			ray->normal = plane->axis;
		return (true);
	}
	return (false);
}
