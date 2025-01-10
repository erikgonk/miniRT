/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/10 14:54:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cone(t_data *data, t_ray *ray, t_obj *cone, double *t)
{
	t_v3		oc;
	t_quadratic	quad;
	double		height_check;
	t_v3		point;
	t_v3		cone_to_point;
	double		m;
	t_v3		scaled_axis;
	double		dot_oc_axis;
	double		dot_dir_axis;
	t_v3		vsub_point_pos;

	if (v3_compare(data->cam->pos, ray->origin))
	{
		oc = cone->calcs.oc;
		dot_oc_axis = cone->calcs.dot_oc_axis;
	}
	else
	{
		oc = vsub(ray->origin, cone->pos);
		dot_oc_axis = dot(oc, cone->axis);
	}
	dot_dir_axis = dot(ray->direction, cone->axis);
	quad.a = dot_dir_axis * dot_dir_axis - cone->calcs.k * dot(ray->direction, ray->direction);
	quad.b = 2.0f * (dot_dir_axis * dot_oc_axis - cone->calcs.k * dot(ray->direction, oc));
	quad.c = dot_oc_axis * dot_oc_axis - cone->calcs.k * dot(oc, oc);
	init_quadratic(&quad, quad.a, quad.b, quad.c);
	if (!solve_quadratic(&quad))
		return (false);
	if (quad.t1 < EPSILON)
	{
		if (quad.t2 < EPSILON)
			return (false);
		quad.t1 = quad.t2;
	}
	point = vadd(ray->origin, vmul(quad.t1, ray->direction));
	vsub_point_pos = vsub(point, cone->pos);
	height_check = dot(vsub_point_pos, cone->axis);
	if (height_check < 0.0f || height_check > cone->height)
		return (false);
	if (*t > quad.t1)
	{
		*t = quad.t1;
		ray->point = point;
		cone_to_point = vsub_point_pos;
		m = dot(cone_to_point, cone->axis);
		scaled_axis = vmul(m, cone->axis);
		ray->normal = normalize(vsub(cone_to_point, scaled_axis));
		if (dot(ray->direction, ray->normal) > 0)
			ray->normal = vmul(-1.0f, ray->normal);
	}
	return (true);
}
