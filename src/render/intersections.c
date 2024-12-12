/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/12 12:35:02 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

//Return true if ray impacts on sphere object, t to save closest intersection
bool	intersect_sphere(t_ray ray, t_obj *sphere, float *t)
{
	t_v3		oc;
	t_quadratic	quad;
	float		radius;

	oc = vsubstract(ray.origin, sphere->pos);
	quad.a = dot(ray.direction, ray.direction);
	quad.b = 2.0f * dot(ray.direction, oc);
	radius = sphere->size / 2.0f;
	quad.c = dot(oc, oc) - (radius * radius);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return (false);
	if (quad.t1 > 0)
		*t = quad.t1; // entra y sale
	else if (quad.t2 > 0)
		*t = quad.t2; // sale
	else
		return (false);
	return (true);
}

void	set_cy_axis(t_quadratic *quad, t_obj *cy, t_ray *ray, float radius)
{
	t_v3		d_par;
	t_v3		d_perp;
	t_v3		oc_par;
	t_v3		oc_perp;

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

	cy->axis = normalize(cy->axis);
	half_height = cy->height * 0.5f;
	set_cy_axis(&quad, cy, &ray, (cy->size * 0.5f));
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return (false);
	if (quad.t1 > 0.0f)
	{
		p = vadd(ray.origin, vmul(quad.t1, ray.direction));
		proj = dot(vsubstract(p, cy->pos), cy->axis);
		if (proj > -half_height && proj < half_height)
		{
			*t = quad.t1;
			return (true);
		}
	}
	if (quad.t2 > 0.0f)
	{
		p = vadd(ray.origin, vmul(quad.t2, ray.direction));
		proj = dot(vsubstract(p, cy->pos), cy->axis);
		if (proj > -half_height && proj < half_height)
		{
			*t = quad.t2;
			return (true);
		}
	}
	return (false);
}



bool	intersect_plane(t_ray ray, t_obj *plane, float *t)
{
	float	denominator;
	float	numerator;
	t_v3	oc;

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
