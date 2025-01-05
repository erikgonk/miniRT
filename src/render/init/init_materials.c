/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/05 10:49:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_materials_mt_mr(t_obj *obj)
{
	if (obj->material.m_type == MT)
	{
		obj->material.reflectivity = 0.4f;
		obj->material.transmittance = 0.0f;
		obj->material.roughness = 1.0f;
		obj->material.absorption = 1.0f;
		obj->material.specularity = 0.9f;
		obj->material.shininess = 170;
	}
	else if (obj->material.m_type == MR)
	{
		obj->rgb = RGB_BLACK;
		obj->a_rgb = RGB_BLACK;
		obj->material.reflectivity = 1.0f;
		obj->material.transmittance = 0.0f;
		obj->material.roughness = 0.0f;
		obj->material.absorption = 0.0f;
		obj->material.specularity = 1.0f;
		obj->material.shininess = 500;
	}
	else
	{
		// obj->material.reflectivity = 0.10f;
		obj->material.specularity = 0.1f;
		obj->material.shininess = 50;
	}
}
void	init_materials_render(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		if (obj->material.m_type == GL)
		{
			obj->material.reflectivity = 0.1f;
			obj->material.transmittance = 0.9f;
			obj->material.roughness = 0.0f;
			obj->material.absorption = 0.1f;
			obj->material.specularity = 0.9f;
			obj->material.shininess = 150;
		}
		else
			init_materials_mt_mr(obj);
		obj = obj->next;
	}
}
