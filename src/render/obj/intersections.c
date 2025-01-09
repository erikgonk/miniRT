/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/08 14:03:53 by shurtado         ###   ########.fr       */
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

bool	hit_sp(t_ray *ray, t_obj *sphere, double *t)
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

bool	hit_pl(t_ray *ray, t_obj *plane, double *t)
{
	t_v3			hit_point;
	t_v3			local_hit;
	t_v3			half_size;
	double			denominator;
	double			numerator;
	double			result;
	double			x;
	double			y;

	denominator = dot(ray->direction, plane->axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	numerator = dot(vsub(plane->pos, ray->origin), plane->axis);
	result = numerator / denominator;
	if (result <= EPSILON || result >= *t)
		return (false);
	hit_point = vadd(ray->origin, vmul(result, ray->direction));
	if (plane->type == SIDE)
	{
		local_hit = vsub(hit_point, plane->pos);
		x = dot(local_hit, plane->right);
		y = dot(local_hit, plane->up);
		half_size = vmul(0.5, plane->cube_size);
		if (fabs(x) > half_size.x || fabs(y) > half_size.y)
			return (false);
	}
	*t = result;
	ray->point = hit_point;
	if (denominator > EPSILON)
		ray->normal = vmul(-1.0, plane->axis);
	else
		ray->normal = plane->axis;
	return (true);
}




