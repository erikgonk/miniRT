/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/10 12:55:08 by shurtado         ###   ########.fr       */
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

	oc = vsubstract(ray.origin, cy->pos);
	quad.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	quad.b = 2.0f * (oc.x * ray.direction.x + oc.z * ray.direction.z);
	quad.c = oc.x * oc.x + oc.z * oc.z - ((cy->size / 2.0f) * (cy->size / 2.0f));
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return (false);
	y1 = ray.origin.y + quad.t1 * ray.direction.y;
	y2 = ray.origin.y + quad.t2 * ray.direction.y;
	if (y1 > -0.5f && y1 < 0.5f)
	{
		*t = quad.t1;
		return (true);
	}
	if (y2 > -0.5f && y2 < 0.5f)
	{
		*t = quad.t2;
		return (true);
	}
	return (false);
}

// t_xnode	*ft_intersect_cylinder(t_obj *o, t_ray r)
// {
// 	t_quadratics	q;
// 	t_xnode			*xs;
// 	double			t;

// 	xs = NULL;
// 	r = ft_transform_ray(o -> transform_inverse, r);
// 	q.a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
// 	if (q.a < EPSILON)
// 		return (ft_add_caps_cy(o, r, &xs));
// 	q.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
// 	q.c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1;
// 	q.d = pow(q.b, 2) - 4 * q.a * q.c;

	// if (q.d >= 0)
	// {
	// 	t = (-q.b - sqrt(q.d)) / (2 * q.a);
	// 	if (ft_pt_bound_cycone(o, r, t))
	// 		xs = ft_xnew(o, t);
	// 	if (q.d > 0)
	// 	{
	// 		t = (-q.b + sqrt(q.d)) / (2 * q.a);
	// 		if (ft_pt_bound_cycone(o, r, t))
	// 			ft_xadd_back(&xs, ft_xnew(o, t));
	// 	}
	// }
// 	return (ft_add_caps_cy(o, r, &xs));
// }

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
