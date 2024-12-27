/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:41:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/27 13:52:12 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	specular_light(t_rgb *color, t_data *data, t_ray *ray)
{
	float		intensity;
	t_v3		reflection;
	t_slight	*sl;

	sl = data->s_light;
	while (sl)
	{
		reflection = vrefl(vneg(normalize(vsub(sl->pos, ray->point))), ray->normal);
		intensity = pow(fmax(dot(reflection, ray->i_direction), 0.0f), SOLID_S);
		color->r = fminf(color->r + sl->rgb.r * intensity, 255);
		color->g = fminf(color->g + sl->rgb.g * intensity, 255);
		color->b = fminf(color->b + sl->rgb.b * intensity, 255);
		sl = sl->next;
	}
}
