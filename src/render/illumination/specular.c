/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:41:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/20 09:46:15 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	vneg(t_v3 v)
{
	t_v3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

t_v3	reflect(t_v3 v, t_v3 n)
{
	float	dot_product;
	t_v3	result;

	dot_product = dot(v, n);
	result.x = v.x - 2 * dot_product * n.x;
	result.y = v.y - 2 * dot_product * n.y;
	result.z = v.z - 2 * dot_product * n.z;
	return (result);
}

void	specular_light(t_rgb *color, t_slight *slight, t_ray *ray, t_ray *s_ray)
{
	float		intensity;
	t_v3		view_dir;
	t_v3		reflection;

	view_dir = normalize(vneg(ray->direction));
	reflection = reflect(vneg(s_ray->direction), ray->normal);
	intensity = pow(fmax(dot(reflection, view_dir), 0.0f), 32);
	color->r = fminf(color->r + slight->rgb.r * intensity, 255.0f);
	color->g = fminf(color->g + slight->rgb.g * intensity, 255.0f);
	color->b = fminf(color->b + slight->rgb.b * intensity, 255.0f);
}
