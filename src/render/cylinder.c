/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:21 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:08:03 by shurtado         ###   ########.fr       */
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
	t_cap	cap[2];

	cap[0].cap_center = vadd(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	cap[1].cap_center = vsub(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	cap[0].radius = cy->size * 0.5f;
	cap[1].radius = cy->size * 0.5f;
	cap[0].cap_normal = cy->axis;
	cap[1].cap_normal = vmul(-1.0f, cy->axis);
	hit = false;
	if (check_cap(ray, cap[0], t))
		hit = true;
	if (check_cap(ray, cap[1], t))
		hit = true;
	return (hit);
}

void	set_cy_axis(t_quadratic *quad, t_obj *cy, t_ray *ray, float radius)
{
	t_v3	d_par;
	t_v3	d_perp;
	t_v3	oc_par;
	t_v3	oc_perp;

	d_par = vmul(dot(ray->direction, cy->axis), cy->axis);
	d_perp = vsub(ray->direction, d_par);
	oc_par = vmul(dot(vsub(ray->origin, cy->pos), cy->axis), cy->axis);
	oc_perp = vsub(vsub(ray->origin, cy->pos), oc_par);
	quad->a = dot(d_perp, d_perp);
	quad->b = 2.0f * dot(oc_perp, d_perp);
	quad->c = dot(oc_perp, oc_perp) - radius * radius;
}

float	set_ray_t(t_ray *ray, t_obj *cy, float *t, float quadt1)
{
	float		proj;
	t_v3		point;
	float		t_min;

	t_min = INFINITY;
	point = vadd(ray->origin, vmul(quadt1, ray->direction));
	proj = dot(vsub(point, cy->pos), cy->axis);
	if (proj > -(cy->height * 0.5f) && proj < (cy->height * 0.5f))
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

bool	hit_cy(t_ray *ray, t_obj *cy, float *t)
{
	t_quadratic	quad;
	float		t_min;

	t_min = INFINITY;
	set_cy_axis(&quad, cy, ray, (cy->size * 0.5f));
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
