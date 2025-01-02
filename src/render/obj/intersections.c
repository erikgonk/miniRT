/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/02 17:35:15 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	calc_quad_sphere(t_obj *sphere, t_ray ray, t_quadratic *quad)
{
	t_v3	oc;

	oc = vsub(ray.origin, sphere->pos);
	quad->a = dot(ray.direction, ray.direction);
	quad->b = 2.0f * dot(ray.direction, oc);
	quad->c = dot(oc, oc) - (sphere->calcs.radius2);
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
	float	result;
	float	numerator;

	numerator = dot(vsub(plane->pos, ray->origin), plane->axis);
	denominator = dot(ray->direction, plane->axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	result = numerator / denominator;
	if (result > EPSILON && result < *t)
	{
		*t = result;
		ray->point = vadd(ray->origin, vmul(*t, ray->direction));
		if (dot(ray->direction, plane->axis) > EPSILON)
			ray->normal = plane->calcs.i_axis;
		else
			ray->normal = plane->axis;
		return (true);
	}
	return (false);
}
