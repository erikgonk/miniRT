/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 12:40:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_gl(t_obj *obj)
{
	obj->material.reflectivity = 0.1f;
	obj->material.transmittance = 0.9f;
	obj->material.roughness = 0.0f;
	obj->material.absorption = 0.1f;
	obj->material.specularity = 0.9f;
	obj->material.shininess = 150;
}

void	init_mt(t_obj *obj)
{
	obj->material.reflectivity = 0.4f;
	obj->material.transmittance = 0.0f;
	obj->material.roughness = 1.0f;
	obj->material.absorption = 1.0f;
	obj->material.specularity = 0.9f;
	obj->material.shininess = 170;
}

void	init_mr(t_obj *obj)
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

void	init_materials_render(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		obj->material.texture = NULL;
		if (obj->material.m_type == GL)
			init_gl(obj);
		else if (obj->material.m_type == MT)
		{
			init_mt(obj);
		}
		else if (obj->material.m_type == MR)
		{
			init_mr(obj);
		}
		else
		{
			obj->material.specularity = 0.1f;
			obj->material.shininess = 50;
		}
		obj = obj->next;
	}
}
