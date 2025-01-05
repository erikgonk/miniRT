/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/05 15:01:33 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cone_axis(t_quadratic *quad, t_obj *cone, t_ray *ray)
{
	t_v3 co;
	float cos2;
	float sin2;

	co = vsub(ray->origin, cone->pos);
	cos2 = cos(cone->size) * cos(cone->size);
	sin2 = 1.0f - cos2;
	quad->a = dot(ray->direction, ray->direction) -
				cos2 * pow(dot(ray->direction, cone->axis), 2);
	quad->b = 2.0f * (dot(ray->direction, co) -
				cos2 * dot(ray->direction, cone->axis) * dot(co, cone->axis));
	quad->c = dot(co, co) - cos2 * pow(dot(co, cone->axis), 2);
}

bool	hit_cone(t_ray *ray, t_obj *cone, float *t)
{
	t_quadratic quad;

	set_cone_axis(&quad, cone, ray);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return false;
	float h0 = dot(vsub(vadd(ray->origin, vmul(quad.t1, ray->direction)), cone->pos), cone->axis);
	float h1 = dot(vsub(vadd(ray->origin, vmul(quad.t2, ray->direction)), cone->pos), cone->axis);
	if (h0 < 0 || h0 > cone->height)
		quad.t1 = INFINITY;
	if (h1 < 0 || h1 > cone->height)
		quad.t2 = INFINITY;
	if (*t > quad.t1 && quad.t1 < INFINITY)
		*t = quad.t1;
	return (quad.t1 < INFINITY);
}
