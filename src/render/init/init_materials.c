/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 13:04:45 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_materials_mt_mr(t_obj *obj)
{
	if (obj->material.m_type == MT)
	{
		obj->material.reflectivity = 0.8f;
		obj->material.transmittance = 0.0f;
		obj->material.roughness = 0.3f;
		obj->material.absorption = 1.0f;
		obj->material.specularity = 0.9f;
	}
	else if (obj->material.m_type == MR)
	{
		obj->material.reflectivity = 1.0f;
		obj->material.transmittance = 0.0f;
		obj->material.roughness = 0.0f;
		obj->material.absorption = 0.0f;
		obj->material.specularity = 1.0f;
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
		}
		else
			init_materials_mt_mr(obj);
		obj = obj->next;
	}
}
