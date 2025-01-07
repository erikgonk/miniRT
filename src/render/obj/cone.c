/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 14:47:31 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cone(t_ray *ray, t_obj *cone, double *t)
{
	t_v3		oc;
	double		half_angle;
	double		cos_half;
	double		k;
	t_quadratic	quad;
	double		height_check;
	t_v3		point;
	t_v3		cone_to_point;
	double		m;
	t_v3		scaled_axis;

	oc = vsub(ray->origin, cone->pos);
	half_angle = (cone->size * 0.5f) * (M_PI / 180.0f);
	cos_half = cos(half_angle);
	k = cos_half * cos_half;
	quad.a = dot(ray->direction, cone->axis) * dot(ray->direction, cone->axis) - k * dot(ray->direction, ray->direction);
	quad.b = 2.0f * (dot(ray->direction, cone->axis) * dot(oc, cone->axis) - k * dot(ray->direction, oc));
	quad.c = dot(oc, cone->axis) * dot(oc, cone->axis) - k * dot(oc, oc);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return false;
	if (quad.t1 < EPSILON)
	{
		if (quad.t2 < EPSILON)
			return false;
		quad.t1 = quad.t2;
	}
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
		if (dot(ray->direction, ray->normal) > 0)
			ray->normal = vmul(-1.0f, ray->normal);
	}
	return true;
}
