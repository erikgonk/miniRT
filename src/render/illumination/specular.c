/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:41:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/21 13:25:43 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	specular_light(t_rgb *color, t_slight *slight, t_ray *ray, t_ray *s_ray)
{
	float		intensity;
	t_v3		reflection;
	int			roughness;
	float		color_roughness;
	int			r;
	int			g;
	int			b;

	roughness = 64;
	if (roughness < 8)
	{
		color_roughness = 50;
		r = 255;
		g = 255;
		b = 255;
	}
	else if (roughness < 64)
		color_roughness = 150;
	else
		color_roughness = 255;
	if (roughness >= 8)
	{
		r = (color->r + color_roughness) / 2;
		g = (color->g + color_roughness) / 2;
		b = (color->b + color_roughness) / 2;
	}
	reflection = vrefl(vneg(s_ray->direction), ray->normal);
	intensity = pow(fmax(dot(reflection, ray->i_direction), 0.0f), roughness);
	color->r = fminf(color->r + slight->rgb.r * intensity, r);
	color->g = fminf(color->g + slight->rgb.g * intensity, g);
	color->b = fminf(color->b + slight->rgb.b * intensity, b);
}
