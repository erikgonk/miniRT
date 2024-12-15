/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/15 17:23:30 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	calc_quad_sphere(t_obj *sphere, t_ray ray, t_quadratic *quad)
{
	t_v3	oc;
	float	radius;

	oc = vsubstract(ray.origin, sphere->pos);
	quad->a = dot(ray.direction, ray.direction);
	quad->b = 2.0f * dot(ray.direction, oc);
	radius = sphere->size / 2.0f;
	quad->c = dot(oc, oc) - (radius * radius);
	init_quadratic(quad, quad->a, quad->b, quad->c);
	if (!solve_quadratic(quad))
		return (false);
	return (true);
}

bool	intersect_sphere(t_ray ray, t_obj *sphere, float *t)
{
	t_quadratic	quad;

	if (!calc_quad_sphere(sphere, ray, &quad))
		return (false);
	if (quad.t1 > 0)
		*t = quad.t1; // entra y sale
	else if (quad.t2 > 0)
		*t = quad.t2; // sale
	else
		return (false);
	return (true);
}

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

bool	cy_caps(t_ray ray, t_obj *cy, float *t, float current_t)
{
	t_v3	top_center;
	t_v3	bottom_center;
	t_v3	intersection_point;
	float	t_cap;

	top_center = vadd(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	bottom_center = vsubstract(cy->pos, vmul((cy->height * 0.5f), cy->axis));
	t_cap = dot(vsubstract(top_center, ray.origin), cy->axis)
		/ dot(ray.direction, cy->axis);
	if (t_cap > 0.0f && (current_t < 0 || t_cap < current_t))
	{
		intersection_point = vadd(ray.origin, vmul(t_cap, ray.direction));
		if (vlength(vsubstract(intersection_point, top_center)) <= (cy->size
				* 0.5f))
		{
			*t = t_cap;
			return (true);
		}
	}
	t_cap = dot(vsubstract(bottom_center, ray.origin), cy->axis)
		/ dot(ray.direction, cy->axis);
	if (t_cap > 0.0f && (current_t < 0 || t_cap < current_t))
	{
		intersection_point = vadd(ray.origin, vmul(t_cap, ray.direction));
		if (vlength(vsubstract(intersection_point, bottom_center)) <= (cy->size
				* 0.5f))
		{
			*t = t_cap;
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
	d_perp = vsubstract(ray->direction, d_par);
	oc_par = vmul(dot(vsubstract(ray->origin, cy->pos), cy->axis), cy->axis);
	oc_perp = vsubstract(vsubstract(ray->origin, cy->pos), oc_par);
	quad->a = dot(d_perp, d_perp);
	quad->b = 2.0f * dot(oc_perp, d_perp);
	quad->c = dot(oc_perp, oc_perp) - radius * radius;
}

bool	intersect_cylinder(t_ray ray, t_obj *cy, float *t)
{
	t_quadratic	quad;
	float		half_height;
	float		proj;
	t_v3		p;
	bool		hit;

	hit = false;
	cy->axis = normalize(cy->axis);
	half_height = cy->height * 0.5f;
	set_cy_axis(&quad, cy, &ray, (cy->size * 0.5f));
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (solve_quadratic(&quad))
	{
		if (quad.t1 > 0.0f)
		{
			p = vadd(ray.origin, vmul(quad.t1, ray.direction));
			proj = dot(vsubstract(p, cy->pos), cy->axis);
			if (proj > -half_height && proj < half_height)
			{
				*t = quad.t1;
				hit = true;
			}
		}
		if (quad.t2 > 0.0f)
		{
			p = vadd(ray.origin, vmul(quad.t2, ray.direction));
			proj = dot(vsubstract(p, cy->pos), cy->axis);
			if (proj > -half_height && proj < half_height)
			{
				*t = quad.t2;
				hit = true;
			}
		}
	}
	if (!hit)
		hit = cy_caps(ray, cy, t, -1);
	else
		cy_caps(ray, cy, t, *t);
	return (hit);
}

bool	intersect_plane(t_ray ray, t_obj *plane, float *t)
{
	float	denominator;
	float	numerator;
	t_v3	oc;

	plane->axis = normalize(plane->axis);
	denominator = dot(ray.direction, plane->axis);
	if (fabs(denominator) < 1e-6)
		return (false);
	oc = vsubstract(plane->pos, ray.origin);
	numerator = dot(oc, plane->axis);
	*t = numerator / denominator;
	if (*t <= 0)
		return (false);
	return (true);
}
