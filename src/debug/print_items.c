/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:51:49 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 13:47:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_ambient_light(t_alight *a_light)
{
	if (a_light)
	{
		printf("Ambient Light:\n");
		printf("\tBrightness: %.2f\n", a_light->br);
		print_t_rgb("\tColor", a_light->rgb);
	}
	else
		printf("Ambient Light: NULL\n");
}

void	print_camera(t_cam *cam)
{
	if (cam)
	{
		printf("Camera:\n");
		print_t_v3("\tPosition", cam->pos);
		printf("\tFOV: %d\n", cam->fov);
		print_t_v3("\tAxis (Orientation)", cam->axis);
	}
	else
	{
		printf("Camera: NULL\n");
	}
}

void	print_spot_lights(t_slight *s_light)
{
	if (s_light)
	{
		printf("Spot Lights:\n");
		while (s_light)
		{
			print_t_v3("\tPosition", s_light->pos);
			printf("\tBrightness: %.2f\n", s_light->br);
			print_t_rgb("\tColor", s_light->rgb);
			s_light = s_light->next;
		}
	}
	else
	{
		printf("Spot Lights: NULL\n");
	}
}

void	print_objects(t_obj *obj)
{
	if (obj)
	{
		printf("Objects:\n");
		while (obj)
		{
			printf("\tType: %d\n", obj->type);
			printf("\tIndex: %d\n", obj->i);
			print_t_v3("\tPosition", obj->pos);
			print_t_v3("\tAxis (Orientation)", obj->axis);
			print_t_rgb("\tColor", obj->rgb);
			printf("\tSize: %.2f\n", obj->size);
			printf("\tHeight: %.2f\n", obj->height);
			printf("\n");
			obj = obj->next;
		}
	}
	else
		printf("Objects: NULL\n");
}

// Función principal que llama a las subfunciones
void	print_t_data(t_data *data)
{
	if (data == NULL)
	{
		printf("t_data is NULL\n");
		return ;
	}
	print_ambient_light(data->a_light);
	print_camera(data->cam);
	print_spot_lights(data->s_light);
	print_objects(data->obj);
}
