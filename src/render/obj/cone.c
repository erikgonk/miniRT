/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 12:26:50 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cone(t_ray *ray, t_obj *cone, float *t)
{
	t_v3		oc;
	double		half_angle;
	double		k;
	t_quadratic	quad;
	double		height_check;
	t_v3		point;
	t_v3		cone_to_point;
	double		m;
	t_v3		scaled_axis;

	oc = vsub(ray->origin, cone->pos);
	half_angle = cone->size * 0.5f * (M_PI / 180.0f);
	k = tan(half_angle);
	k = k * k;
	quad.a = dot(ray->direction, cone->axis) * dot(ray->direction, cone->axis) - k;
	quad.b = 2.0f * (dot(ray->direction, cone->axis) * dot(oc, cone->axis)
		- dot(ray->direction, oc) * k);
	quad.c = dot(oc, cone->axis) * dot(oc, cone->axis) - dot(oc, oc) * k;
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad) || quad.t1 == INFINITY)
		return false;
	point = vadd(ray->origin, vmul(quad.t1, ray->direction));
	height_check = dot(vsub(point, cone->pos), cone->axis);
	if (height_check < 0.0f || height_check > cone->height)
		return false;
	if (*t > quad.t1)
	{
		*t = quad.t1;
		ray->point = point;
		cone_to_point = vsub(point, cone->pos);
		m = dot(cone_to_point, cone->axis);
		scaled_axis = vmul(m, cone->axis);
		ray->normal = normalize(vsub(cone_to_point, scaled_axis));
	}
	return true;
}
