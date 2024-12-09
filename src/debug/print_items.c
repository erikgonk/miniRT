/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:51:49 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/09 16:53:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_ambient_light(t_aLight *aLight)
{
	if (aLight)
	{
		printf("Ambient Light:\n");
		printf("\tBrightness: %.2f\n", aLight->br);
		print_t_rgb("\tColor", aLight->rgb);
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

void	print_spot_lights(t_sLight *sLight)
{
	if (sLight)
	{
		printf("Spot Lights:\n");
		while (sLight)
		{
			print_t_v3("\tPosition", sLight->pos);
			printf("\tBrightness: %.2f\n", sLight->br);
			print_t_rgb("\tColor", sLight->rgb);
			sLight = sLight->next;
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

	print_ambient_light(data->aLight);
	print_camera(data->cam);
	print_spot_lights(data->sLight);
	print_objects(data->obj);
}
