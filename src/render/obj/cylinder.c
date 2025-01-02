/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:21 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/02 17:04:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

// bool	check_cap(t_ray *ray, t_cap cap, float *t)
// {
// 	t_v3	point;
// 	float	t_cap;

// 	t_cap = dot(vsub(cap.cap_center, ray->origin), cap.cap_normal)
// 		/ dot(ray->direction, cap.cap_normal);
// 	if (t_cap > EPSILON && t_cap < *t)
// 	{
// 		point = vadd(ray->origin, vmul(t_cap, ray->direction));
// 		if (vlength(vsub(point, cap.cap_center)) <= cap.radius)
// 		{
// 			*t = t_cap;
// 			ray->point = point;
// 			ray->normal = cap.cap_normal;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// bool	cy_caps(t_ray *ray, t_obj *cy, float *t)
// {
// 	bool	hit;

// 	hit = false;
// 	if (check_cap(ray, cy->calcs.upper_cap, t) || check_cap(ray, cy->calcs.btm_cap, t))
// 		hit = true;
// 	return (hit);
// }

void	set_cy_axis(t_quadratic *quad, t_obj *cy, t_ray *ray, t_v3 *ray_origin)
{
	t_v3	oc_perp;
	t_v3	d_perp;
	float	oc_axis_dot;
	float	d_axis_dot;
	t_v3	oc;

	oc = vsub(ray->origin, cy->pos);
	oc_axis_dot = dot(oc, cy->axis);
	d_axis_dot = dot(ray->direction, cy->axis);
	oc_perp = vsub(oc, vmul(oc_axis_dot, cy->axis));
	d_perp = vsub(ray->direction, vmul(d_axis_dot, cy->axis));
	quad->c = dot(oc_perp, oc_perp) - cy->calcs.radius2;
	quad->a = dot(d_perp, d_perp);
	quad->b = 2.0f * dot(oc_perp, d_perp);
}

float	set_ray_t(t_ray *ray, t_obj *cy, float *t, t_quadratic quad)
{
	float		proj;
	t_v3		point;
	float		t_min;

	t_min = INFINITY;
	if (quad.t1 > EPSILON && quad.t1 < quad.t2)
	{
		point = vadd(ray->origin, vmul(quad.t1, ray->direction));
		t_min = quad.t1;
	}
	else if (quad.t2 > EPSILON)
	{
		point = vadd(ray->origin, vmul(quad.t2, ray->direction));
		t_min = quad.t2;
	}
	proj = dot(vsub(point, cy->pos), cy->axis);
	if (proj > -cy->calcs.hh_e_sum && proj < cy->calcs.hh_e_res && t_min < *t)
	{
		*t = t_min;
		ray->point = point;
		ray->normal = normalize(vsub(point, \
			vadd(cy->pos, vmul(proj, cy->axis))));
		if (t_min == quad.t2 && dot(ray->direction, ray->normal) > 0)
				ray->normal = vmul(-1, ray->normal);
	}
	return (t_min);
}

bool	hit_cy(t_ray *ray, t_obj *cy, float *t, t_v3 *ray_origin)
{
	t_quadratic	quad;/*  */
	float		t_min;

	t_min = INFINITY;
	set_cy_axis(&quad, cy, ray, ray_origin);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (solve_quadratic2(&quad))
	{
		if (quad.t1 <= EPSILON && quad.t2 <= EPSILON)
			return (false);
		t_min = set_ray_t(ray, cy, t, quad);
	}
	return (t_min != INFINITY);
}
