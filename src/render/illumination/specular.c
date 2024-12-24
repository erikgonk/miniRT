/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:41:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 11:54:40 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	specular_light(t_rgb *color, t_slight *slight, t_ray *ray, t_ray *s_ray)
{
	float		intensity;
	t_v3		reflection;

	reflection = vrefl(vneg(s_ray->direction), ray->normal);
	intensity = pow(fmax(dot(reflection, ray->i_direction), 0.0f), SOLID_S);
	color->r = fminf(color->r + slight->rgb.r * intensity, 255);
	color->g = fminf(color->g + slight->rgb.g * intensity, 255);
	color->b = fminf(color->b + slight->rgb.b * intensity, 255);
}
