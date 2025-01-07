/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:31:28 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 12:19:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	make_cone_cap(t_obj *cone, t_data *data)
{
	t_obj	*cap;

	cap = malloc(sizeof(t_obj));
	cap->parent = cone->parent;
	cap->material = cone->material;
	cap->rgb = cone->rgb;
	cap->a_rgb = apply_ambient_light(cone->rgb, data->a_light);
	cap->type = CAP;
	cap->size = (cone->height * tan((cone->size * 0.5f) * (M_PI / 180.0f)));
	cap->pos = vadd(cone->pos, vmul(cone->height, cone->axis));
	cap->axis = cone->axis;
	cap->next = NULL;
	objadd_back(&data->obj, cap);
}

void	make_caps(t_data *data, t_obj *obj)
{
	t_obj	*tp_cap;
	t_obj	*bt_cap;

	tp_cap = malloc(sizeof(t_obj));
	bt_cap = malloc(sizeof(t_obj));
	tp_cap->parent = obj->parent;
	bt_cap->parent = obj->parent;
	tp_cap->material = obj->material;
	bt_cap->material = obj->material;
	tp_cap->rgb = obj->rgb;
	bt_cap->rgb = obj->rgb;
	tp_cap->a_rgb = apply_ambient_light(obj->rgb, data->a_light);
	bt_cap->a_rgb = tp_cap->a_rgb;
	tp_cap->type = CAP;
	bt_cap->type = CAP;
	tp_cap->size = obj->calcs.upper_cap.radius;
	bt_cap->size = obj->calcs.btm_cap.radius;
	tp_cap->pos = obj->calcs.upper_cap.cap_center;
	bt_cap->pos = obj->calcs.btm_cap.cap_center;
	tp_cap->axis = obj->calcs.upper_cap.cap_normal;
	bt_cap->axis = obj->calcs.btm_cap.cap_normal;
	tp_cap->calcs.upper_cap.cap_normal = obj->calcs.upper_cap.cap_normal;
	bt_cap->calcs.btm_cap.cap_normal = obj->calcs.btm_cap.cap_normal;
	tp_cap->next = NULL;
	bt_cap->next = NULL;
	if (obj->type == CY)
		objadd_back(&data->obj, tp_cap);
	objadd_back(&data->obj, bt_cap);
}

void	init_obj(t_data *data)
{
	t_obj		*obj;
	int			parent;

	obj = data->obj;
	parent = 0;
	while (obj)
	{
		if (obj->type != CAP)
			obj->parent = parent;
		if (obj->material.m_type != MR)
			obj->a_rgb = apply_ambient_light(obj->rgb, data->a_light);
		if (obj->type == PL)
			obj->calcs.i_axis = vmul(-1.0f, obj->axis);
		else if (obj->type == CY)
		{
			init_obj_normi(data, obj);
			make_caps(data, obj);
		}
		else if (obj->type == CO)
			make_cone_cap(obj, data);
		else
			init_obj_normi(data, obj);
		parent++;
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
	obj->calcs.hh_e_sum = obj->calcs.half_height + EPSILON;
	obj->calcs.hh_e_res = obj->calcs.half_height - EPSILON;
 	obj->calcs.upper_cap.cap_center = vadd(obj->pos, vmul(obj->calcs.half_height, \
												obj->axis));
	obj->calcs.btm_cap.cap_center = vsub(obj->pos, vmul(obj->calcs.half_height, obj->axis));
	obj->calcs.upper_cap.radius = obj->size * 0.5f;
	obj->calcs.btm_cap.radius = obj->size * 0.5f;
	obj->calcs.upper_cap.cap_normal = obj->axis;
	obj->calcs.btm_cap.cap_normal = vmul(-1.0f, obj->axis);
//			refract
	obj->calcs.etai = 1;
	obj->calcs.etat = 1.5; // este es el que se pasa por argumento as refractive_index
	obj->calcs.eta = obj->calcs.etai / obj->calcs.etat;
	obj->calcs.eta_reverse = obj->calcs.etat / obj->calcs.etai;
	obj->calcs.eta2 = obj->calcs.eta * obj->calcs.eta;
	obj->calcs.eta_reverse2 = obj->calcs.eta_reverse * obj->calcs.eta_reverse;
//			fresnel
	obj->calcs.etai_etat = 1 / 1.5;
	obj->calcs.etai_etat_reverse = 1.5 / 1;
//			cb
	if (obj->material.board_scale != -1)
		obj->material.rgb_checker = apply_ambient_light(obj->material.rgb_checker, data->a_light);
}

void	init_light(t_data *data)
{
	t_slight	*slight;

	data->cam->pi2 = 2.0f * M_PI;
	slight = data->s_light;
	while (slight)
	{
		slight->rgb_inty.r = (unsigned char)(slight->rgb.r * slight->br);
		slight->rgb_inty.g = (unsigned char)(slight->rgb.g * slight->br);
		slight->rgb_inty.b = (unsigned char)(slight->rgb.b * slight->br);
		slight = slight->next;
	}
}
