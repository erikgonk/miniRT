/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:31:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/27 12:20:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_obj(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		obj->rgb_checker = (t_rgb){25, 25, 25};
		obj->board_scale = -0.5;
		obj->material = 0;
		if (obj->type == SP)
			obj->material = 2;
		obj->a_rgb = apply_ambient_light(obj->rgb, data->a_light);
		if (obj->type == PL)
		{
			obj->numerator = dot(vsub(obj->pos, data->cam->pos), obj->axis);
			obj->i_axis = vmul(-1.0f, obj->axis);
		}
		else
			init_obj_normi(data, obj);
		obj = obj->next;
	}
}

void	init_obj_normi(t_data *data, t_obj *obj)
{
	obj->radius = obj->size * 0.5f;
	obj->radius2 = obj->radius * obj->radius;
	if (obj->type != SP)
		obj->axis = normalize(obj->axis);
	obj->oc_par = vmul(dot(vsub(data->cam->pos, obj->pos), obj->axis), \
						obj->axis);
	obj->oc_perp = vsub(vsub(data->cam->pos, obj->pos), obj->oc_par);
	obj->c = dot(obj->oc_perp, obj->oc_perp) - obj->radius2;
	obj->half_height = obj->height * 0.5f;
	obj->upper_cap.cap_center = vadd(obj->pos, vmul(obj->half_height, \
												obj->axis));
	obj->btm_cap.cap_center = vsub(obj->pos, vmul(obj->half_height, obj->axis));
	obj->upper_cap.radius = obj->size * 0.5f;
	obj->btm_cap.radius = obj->size * 0.5f;
	obj->upper_cap.cap_normal = obj->axis;
	obj->btm_cap.cap_normal = vmul(-1.0f, obj->axis);
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
