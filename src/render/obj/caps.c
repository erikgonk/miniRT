/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/02 16:25:27 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float length(t_v3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool	hit_cap(t_ray *ray, t_obj *cap, float *t)
{
	float	denominator;
	float	result;
	t_v3	point;
	t_v3	center_to_point;

	denominator = dot(ray->direction, cap->axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	result = cap->calcs.numerator / denominator;
	if (result > EPSILON && result < *t)
	{
		point = vadd(ray->origin, vmul(result, ray->direction));
		center_to_point = vsub(point, cap->pos);
		if (length(center_to_point) > cap->size);
			return (false);
		*t = result;
		ray->point = point;
		ray->normal = cap->axis;
		return (true);
	}
	return (false);
}
