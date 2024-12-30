/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:31:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/30 17:08:15 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_obj(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		if (obj->material.m_type != MR)
			obj->a_rgb = apply_ambient_light(obj->rgb, data->a_light);
		if (obj->type == PL)
		{
			obj->calcs.numerator = dot(vsub(obj->pos, data->cam->pos), obj->axis);
			obj->calcs.i_axis = vmul(-1.0f, obj->axis);
		}
		else
			init_obj_normi(data, obj);
		obj = obj->next;
	}
}

void	init_obj_normi(t_data *data, t_obj *obj)
{
	obj->calcs.radius = obj->size * 0.5f;
	obj->calcs.radius2 = obj->calcs.radius * obj->calcs.radius;
	if (obj->type != SP)
		obj->axis = normalize(obj->axis);
	obj->calcs.oc_par = vmul(dot(vsub(data->cam->pos, obj->pos), obj->axis), \
						obj->axis);
	obj->calcs.oc_perp = vsub(vsub(data->cam->pos, obj->pos), obj->calcs.oc_par);
	obj->calcs.c= dot(obj->calcs.oc_perp, obj->calcs.oc_perp) - obj->calcs.radius2;
	obj->calcs.half_height = obj->height * 0.5f;
	obj->calcs.upper_cap.cap_center = vadd(obj->pos, vmul(obj->calcs.half_height, \
												obj->axis));
	obj->calcs.btm_cap.cap_center = vsub(obj->pos, vmul(obj->calcs.half_height, obj->axis));
	obj->calcs.upper_cap.radius = obj->size * 0.5f;
	obj->calcs.btm_cap.radius = obj->size * 0.5f;
	obj->calcs.upper_cap.cap_normal = obj->axis;
	obj->calcs.btm_cap.cap_normal = vmul(-1.0f, obj->axis);
}

void	init_light(t_data *data)
{
	t_slight	*slight;

	slight = data->s_light;
	while (slight)
	{
		slight->rgb_inty.r = (unsigned char)(slight->rgb.r * slight->br);
		slight->rgb_inty.g = (unsigned char)(slight->rgb.g * slight->br);
		slight->rgb_inty.b = (unsigned char)(slight->rgb.b * slight->br);
		slight = slight->next;
	}
}
