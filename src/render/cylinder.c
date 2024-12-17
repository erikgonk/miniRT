/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:21 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 10:46:56 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	cy_caps(t_ray *ray, t_obj *cy, float *t, float current_t)
{
	t_v3	top_center;
	t_v3	bottom_center;
	t_v3	point;
	float	t_cap;

	top_center = vadd(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	bottom_center = vsub(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	t_cap = dot(vsub(top_center, ray->origin), cy->axis)
		/ dot(ray->direction, cy->axis);
	if (t_cap > EPSILON && t_cap < current_t)
	{
		point = vadd(ray->origin, vmul(t_cap, ray->direction));
		if (vlength(vsub(point, top_center)) <= (cy->size
				* 0.5f))
		{
			if (t_cap < *t)
			{
				*t = t_cap;
				ray->point = point;
				ray->normal = cy->axis;
			}
			return (true);
		}
	}
	t_cap = dot(vsub(bottom_center, ray->origin), cy->axis)
		/ dot(ray->direction, cy->axis);
	if (t_cap > EPSILON && t_cap < current_t)
	{
		point = vadd(ray->origin, vmul(t_cap, ray->direction));
		if (vlength(vsub(point, bottom_center)) <= (cy->size
				* 0.5f))
		{
			if (t_cap < *t)
			{
				*t = t_cap;
				ray->point = point;
				ray->normal = vmul(-1.0f, cy->axis);
			}
			return (true);
		}
	}
	return (false);
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
