/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/16 01:14:24 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

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

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
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

bool	hit_cy(t_ray *ray, t_obj *cy, float *t)
{
	t_quadratic	quad;
	float		half_height;
	float		proj;
	float		t_min;
	t_v3		point;

	t_min = INFINITY;
	half_height = cy->height * 0.5f;
	set_cy_axis(&quad, cy, ray, (cy->size * 0.5f));
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (solve_quadratic(&quad))
	{
		if (quad.t1 > EPSILON)
		{
			point = vadd(ray->origin, vmul(quad.t1, ray->direction));
			proj = dot(vsub(point, cy->pos), cy->axis);
			if (proj > -half_height && proj < half_height)
			{
				t_min = quad.t1;
				if (t_min < *t)
				{
					*t = quad.t1;
					ray->point = point;
					ray->normal = normalize(vsub(point, \
						vadd(cy->pos, vmul(proj, cy->axis))));
				}
			}
		}
	}
	if (cy_caps(ray, cy, t, t_min))
		return (true);
	return (t_min != INFINITY);
}

