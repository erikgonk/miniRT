/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:21 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 12:04:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	check_cap(t_ray *ray, t_cap cap, float *t)
{
	t_v3	point;
	float	t_cap;

	t_cap = dot(vsub(cap.cap_center, ray->origin), cap.cap_normal)
		/ dot(ray->direction, cap.cap_normal);
	if (t_cap > EPSILON && t_cap < *t)
	{
		point = vadd(ray->origin, vmul(t_cap, ray->direction));
		if (vlength(vsub(point, cap.cap_center)) <= cap.radius)
		{
			*t = t_cap;
			ray->point = point;
			ray->normal = cap.cap_normal;
			return (true);
		}
	}
	return (false);
}

bool	cy_caps(t_ray *ray, t_obj *cy, float *t, float current_t)
{
	t_v3	top_center;
	t_v3	bottom_center;
	bool	hit;

	hit = false;
	if (check_cap(ray, cy->upper_cap, t))
		hit = true;
	if (check_cap(ray, cy->btm_cap, t))
		hit = true;
	return (hit);
}

void	set_cy_axis(t_quadratic *quad, t_obj *cy, t_ray *ray, t_v3 *ray_origin)
{
	t_v3	d_par;
	t_v3	d_perp;
	t_v3	oc_par;
	t_v3	oc_perp;

	if (ray_origin)
	{
		oc_par = vmul(dot(vsub(*ray_origin, cy->pos), cy->axis), cy->axis);
		oc_perp = vsub(vsub(ray->origin, cy->pos), oc_par);
		quad->c = dot(oc_perp, oc_perp) - cy->radius2;
	}
	else
	{
		oc_par = cy->oc_par;
		oc_perp = cy->oc_perp;
		quad->c = cy->c;
	}
	d_par = vmul(dot(ray->direction, cy->axis), cy->axis);
	d_perp = vsub(ray->direction, d_par);
	quad->a = dot(d_perp, d_perp);
	quad->b = 2.0f * dot(oc_perp, d_perp);
}

float	set_ray_t(t_ray *ray, t_obj *cy, float *t, float quadt1)
{
	float		proj;
	t_v3		point;
	float		t_min;

	t_min = INFINITY;
	point = vadd(ray->origin, vmul(quadt1, ray->direction));
	proj = dot(vsub(point, cy->pos), cy->axis);
	if (proj > -(cy->half_height) && proj < cy->half_height)
	{
		t_min = quadt1;
		if (t_min < *t)
		{
			*t = quadt1;
			ray->point = point;
			ray->normal = normalize(vsub(point, \
				vadd(cy->pos, vmul(proj, cy->axis))));
		}
	}
	return (t_min);
}

bool	hit_cy(t_ray *ray, t_obj *cy, float *t, t_v3 *ray_origin)
{
	t_quadratic	quad;
	float		t_min;

	t_min = INFINITY;
	set_cy_axis(&quad, cy, ray, ray_origin);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (solve_quadratic(&quad))
	{
		if (quad.t1 <= EPSILON)
			return (false);
		t_min = set_ray_t(ray, cy, t, quad.t1);
	}
	if (cy_caps(ray, cy, t, t_min))
		return (true);
	return (t_min != INFINITY);
}
