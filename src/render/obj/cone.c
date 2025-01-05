/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/05 15:47:44 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_cone_height(t_ray *ray, t_obj *cone, t_quadratic *quad)
{
	t_v3	tmp;
	float	h;

	tmp = vsub(vadd(ray->origin, vmul(quad->t1, ray->direction)), cone->pos);
	h = dot(tmp, cone->axis);
	if (h < 0.0f || h > cone->height)
		quad->t1 = INFINITY;
	tmp = vsub(vadd(ray->origin, vmul(quad->t2, ray->direction)), cone->pos);
	h = dot(tmp, cone->axis);
	if (h < 0.0f || h > cone->height)
		quad->t2 = INFINITY;
	if (quad->t1 == INFINITY && quad->t2 == INFINITY)
		return (false);
	return (true);
}

static int	calculate_root(t_quadratic *params, t_obj *cone,
	t_ray *ray, t_point *center)
{
	float		hr_ratio;
	t_v3	ray_to_cone;

	hr_ratio = cone->co_attrs->height / cone->co_attrs->radius;
	vsub(center, &ray->origin, &ray_to_cone);
	params->a = ((hr_ratio * hr_ratio) * ((ray->direction.x * ray->direction.x)
				+ (ray->direction.y * ray->direction.y)))
		- (ray->direction.z * ray->direction.z);
	params->b = 2.0 * (hr_ratio * ((hr_ratio * ray->origin.x * ray->direction.x)
				+ (ray->direction.x * center->x)
				+ (hr_ratio * ray->origin.y * ray->direction.y)
				+ (ray->direction.y * center->y))
			- (ray->origin.z * ray->direction.z)
			- (ray->direction.z * center->z));
	params->c = pow(center->x - (hr_ratio * ray->origin.x), 2)
		+ pow(center->y - (hr_ratio * ray->origin.y), 2)
		- pow(center->z - ray->origin.z, 2);
	params->discriminant = (params->b * params->b)
		- (4.0 * params->a * params->c);
	if (params->discriminant < 0.0)
		return (0);
	params->square_root = sqrt(params->discriminant);
	params->roots.close = (-params->b - params->square_root)
		/ (2.0 * params->a);
	return (1);
}

void	set_cone_axis(t_quadratic *quad, t_obj *cone, t_ray *ray)
{
	t_v3	co;
	float	radio;
	float	alpha;
	float	cos2;

	co = vsub(ray->origin, cone->pos);

	/* Asegúrate de que cone->height y cone->size tienen sentido (> 0) */
	radio = cone->size / 2.0f;
	alpha = atanf(radio / cone->height);

	cos2 = cosf(alpha);
	cos2 = cos2 * cos2;

	quad->a = dot(ray->direction, ray->direction)
		- (cos2 * powf(dot(ray->direction, cone->axis), 2.0f));
	quad->b = 2.0f * (dot(ray->direction, co)
		- (cos2 * dot(ray->direction, cone->axis) * dot(co, cone->axis)));
	quad->c = dot(co, co)
		- (cos2 * powf(dot(co, cone->axis), 2.0f));
}

bool	hit_cone(t_ray *ray, t_obj *cone, float *t)
{
	t_quadratic	quad;
	t_v3		hit_point;
	float		h0;
	float		h1;

	set_cone_axis(&quad, cone, ray);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic2(&quad))
		return (false);
	/* Chequea la primera raíz */
	hit_point = vadd(ray->origin, vmul(quad.t1, ray->direction));
	h0 = dot(vsub(hit_point, cone->pos), cone->axis);
	if (h0 < 0.0f || h0 > cone->height)
		quad.t1 = INFINITY;

	/* Chequea la segunda raíz */
	hit_point = vadd(ray->origin, vmul(quad.t2, ray->direction));
	h1 = dot(vsub(hit_point, cone->pos), cone->axis);
	if (h1 < 0.0f || h1 > cone->height)
		quad.t2 = INFINITY;

	/* Escoge la más cercana */
	if (quad.t1 == INFINITY && quad.t2 == INFINITY)
		return (false);
	if (*t > quad.t1 && quad.t1 < INFINITY)
		*t = quad.t1;
	else if (*t > quad.t2 && quad.t2 < INFINITY)
		*t = quad.t2;
	return (true);
}
