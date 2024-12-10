/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/10 17:48:02 by shurtado         ###   ########.fr       */
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

bool	intersect_cylinder(t_ray ray, t_obj *cy, float *t)
{
	t_v3		oc;
	t_quadratic	quad;
	float		y1;
	float		y2;
	float		half_height;

	oc = vsubstract(ray.origin, cy->pos);
	quad.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	quad.b = 2.0f * (oc.x * ray.direction.x + oc.z * ray.direction.z);
	quad.c = oc.x * oc.x + oc.z * oc.z - ((cy->size / 2.0f) * (cy->size / 2.0f));
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return (false);
	y1 = ray.origin.y + quad.t1 * ray.direction.y;
	y2 = ray.origin.y + quad.t2 * ray.direction.y;
	half_height = cy->height * 0.5f;
	if (y1 > cy->pos.y - half_height && y1 < cy->pos.y + half_height)
	{
		*t = quad.t1;
		return (true);
	}
	if (y2 > cy->pos.y - half_height && y2 < cy->pos.y + half_height)
	{
		*t = quad.t2;
		return (true);
	}
	return (false);
}

/*
bool	intersect_cylinder(t_ray ray, t_obj *cy, float *t)
{
	t_v3		OC;
	t_v3		D_par;		// Componente paralela del rayo
	t_v3		D_perp;		// Componente perpendicular del rayo
	t_v3		OC_par;
	t_v3		OC_perp;
	t_quadratic	quad;
	float		half_height;
	float		proj;

	OC = vsubstract(ray.origin, cy->pos);
	half_height = cy->height * 0.5f;

	// Proyecciones
	D_par = vmul(cy->axis, vdot(ray.direction, cy->axis));
	D_perp = vsubstract(ray.direction, D_par);
	OC_par = vmul(cy->axis, vdot(OC, cy->axis));
	OC_perp = vsubstract(OC, OC_par);

	// Coeficientes cuadráticos
	quad.a = vdot(D_perp, D_perp);
	quad.b = 2.0f * vdot(OC_perp, D_perp);
	quad.c = vdot(OC_perp, OC_perp) - (cy->size / 2.0f) * (cy->size / 2.0f);

	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return false;

	// Comprobar t1
	if (quad.t1 > 0.0f)
	{
		t_v3 p = vadd(ray.origin, vmul(ray.direction, quad.t1));
		proj = vdot(vsubstract(p, cy->pos), cy->axis);
		if (proj > -half_height && proj < half_height)
		{
			*t = quad.t1;
			return true;
		}
	}

	// Comprobar t2
	if (quad.t2 > 0.0f)
	{
		t_v3 p = vadd(ray.origin, vmul(ray.direction, quad.t2));
		proj = vdot(vsubstract(p, cy->pos), cy->axis);
		if (proj > -half_height && proj < half_height)
		{
			*t = quad.t2;
			return true;
		}
	}

	return false;
}

*/

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
