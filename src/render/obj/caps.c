/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:09:01 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/10 15:09:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cap(t_data *data, t_ray *ray, t_obj *cap, double *t)
{
	double	denominator;
	double	result;
	double	numerator;
	t_v3	point;
	t_v3	center_to_point;

	if (v3_compare(data->cam->pos, ray->origin))
		numerator = cap->calcs.numerator;
	else
		numerator = dot(vsub(cap->pos, ray->origin), cap->axis);
	denominator = dot(ray->direction, cap->axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	result = numerator / denominator;
	if (result > EPSILON && result < *t)
	{
		point = vadd(ray->origin, vmul(result, ray->direction));
		center_to_point = vsub(point, cap->pos);
		if (length(center_to_point) > cap->size)
			return (false);
		*t = result;
		ray->point = point;
		if (dot(ray->direction, cap->axis) > 0)
			ray->normal = cap->calcs.caps_normal;
		else
			ray->normal = cap->axis;
		return (true);
	}
	return (false);
}
