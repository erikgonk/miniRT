/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:44 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 13:16:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

bool	calc_quad_sphere(t_obj *sphere, t_ray ray, t_quadratic *quad)
{
	t_v3	oc;

	oc = vsub(ray.origin, sphere->pos);
	quad->a = dot(ray.direction, ray.direction);
	quad->b = 2.0f * dot(ray.direction, oc);
	quad->c = dot(oc, oc) - (sphere->calcs.radius2);
	init_quadratic(quad, quad->a, quad->b, quad->c);
	if (!solve_quadratic(quad))
		return (false);
	return (true);
}

bool	hit_sp(t_ray *ray, t_obj *sphere, double *t)
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
	if (sphere->material.texture)
		get_sphere_normal(sphere, ray);
	return (true);
}

bool	side_mode(t_obj *plane, t_ray *ray, double value)
{
	t_v3	local_hit;
	t_v3	hit_point;
	double	x;
	double	y;

	hit_point = vadd(ray->origin, vmul(value, ray->direction));
	local_hit = vsub(hit_point, plane->pos);
	x = dot(local_hit, plane->right);
	y = dot(local_hit, plane->up);
	if (plane->face == 1 && (fabs(x) > plane->calcs.half_size.y || \
		fabs(y) > plane->calcs.half_size.z))
		return (false);
	else if (plane->face == 2 && (fabs(x) > plane->calcs.half_size.x \
				|| fabs(y) > plane->calcs.half_size.z))
		return (false);
	else if (plane->face == 3 && (fabs(x) > plane->calcs.half_size.x \
				|| fabs(y) > plane->calcs.half_size.y))
		return (false);
	ray->point = hit_point;
	return (true);
}

bool	hit_pl(t_data *data, t_ray *ray, t_obj *plane, double *t)
{
	double			dnrxy[3];

	dnrxy[0] = dot(ray->direction, plane->axis);
	if (fabs(dnrxy[0]) < EPSILON)
		return (false);
	if (v3_compare(data->cam->pos, ray->origin))
		dnrxy[1] = plane->calcs.numerator;
	else
		dnrxy[1] = dot(vsub(plane->pos, ray->origin), plane->axis);
	dnrxy[2] = dnrxy[1] / dnrxy[0];
	if (dnrxy[2] <= EPSILON || dnrxy[2] >= *t)
		return (false);
	if (plane->type == SIDE)
		if (!side_mode(plane, ray, dnrxy[2]))
			return (false);
	*t = dnrxy[2];
	if (dnrxy[0] > EPSILON)
		ray->normal = plane->calcs.i_axis;
	else
		ray->normal = plane->axis;
	if (plane->material.texture)
		get_plane_normal(plane, ray->point, ray);
	return (true);
}
