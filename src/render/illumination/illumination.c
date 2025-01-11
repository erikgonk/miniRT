/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:09:03 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 13:39:02 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

t_rgb	apply_al(t_rgb obj_color, t_alight *a_light)
{
	t_rgb	result;
	double	a_r;
	double	a_g;
	double	a_b;

	a_r = a_light->rgb.r / 255.0f;
	a_g = a_light->rgb.g / 255.0f;
	a_b = a_light->rgb.b / 255.0f;
	result.r = (unsigned char)fmin(obj_color.r * a_r * a_light->br, 255.0f);
	result.g = (unsigned char)fmin(obj_color.g * a_g * a_light->br, 255.0f);
	result.b = (unsigned char)fmin(obj_color.b * a_b * a_light->br, 255.0f);
	return (result);
}

void	difuse_light(t_rgb *color, t_slight *slight, t_obj *obj, double inty)
{
	t_rgb	dif_color;

	if (inty > 0.0f)
	{
		dif_color.r = (unsigned char)(slight->rgb_inty.r * inty);
		dif_color.g = (unsigned char)(slight->rgb_inty.g * inty);
		dif_color.b = (unsigned char)(slight->rgb_inty.b * inty);
		color->r = fmin(color->r + (obj->rgb.r * dif_color.r) / 255, 255);
		color->g = fmin(color->g + (obj->rgb.g * dif_color.g) / 255, 255);
		color->b = fmin(color->b + (obj->rgb.b * dif_color.b) / 255, 255);
	}
}

bool	hit_all(t_data *data, t_ray *shdw_ray, t_obj *cr_obj, double *t)
{
	if (cr_obj->type == SP && hit_sp(shdw_ray, cr_obj, t) && \
			(t[0] > EPSILON && *t < t[1]))
		return (true);
	else if ((cr_obj->type == PL || cr_obj->type == SIDE) && \
			hit_pl(data, shdw_ray, cr_obj, t) \
			&& (t[0] > EPSILON && t[0] < t[1]))
		return (true);
	else if (cr_obj->type == CY && hit_cy(shdw_ray, cr_obj, t) \
			&& (t[0] > EPSILON && t[0] < t[1]))
		return (true);
	else if (cr_obj->type == CAP && hit_cap(data, shdw_ray, cr_obj, t) \
			&& (t[0] > EPSILON && t[0] < t[1]))
		return (true);
	else if (cr_obj->type == CO && hit_cone(shdw_ray, cr_obj, t) \
			&& (t[0] > EPSILON && t[0] < t[1]))
		return (true);
	return (false);
}

bool	data_shadow(t_data *data, t_ray *shw_ray, double max_dist, t_obj *self)
{
	t_obj	*cr_obj;
	double	t[2];

	t[0] = INFINITY;
	t[1] = max_dist;
	cr_obj = data->obj;
	while (cr_obj)
	{
		if (cr_obj->type == CAP || (self && (cr_obj == self || \
			cr_obj->parent == self->parent)))
		{
			cr_obj = cr_obj->next;
			continue ;
		}
		if (hit_all(data, shw_ray, cr_obj, t))
			return (true);
		cr_obj = cr_obj->next;
	}
	return (false);
}
