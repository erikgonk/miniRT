/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 09:44:49 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	print_t_rgb(const char *label, t_rgb rgb)
{
	printf("%s -> r: %u, g: %u, b: %u\n", label, rgb.r, rgb.g, rgb.b);
}

void	print_t_v3(const char *label, t_v3 vec)
{
	printf("%s -> x: %.2f, y: %.2f, z: %.2f\n", label, vec.x, vec.y, vec.z);
}

void	print_t_data(t_data *data)
{
	if (data == NULL)
	{
		printf("t_data is NULL\n");
		return;
	}

	// Print ambient light details
	if (data->aLight)
	{
		printf("Ambient Light:\n");
		printf("\tBrightness: %.2f\n", data->aLight->br);
		print_t_rgb("\tColor", data->aLight->rgb);
	}
	else
	{
		printf("Ambient Light: NULL\n");
	}

	// Print camera details
	if (data->cam)
	{
		printf("Camera:\n");
		print_t_v3("\tPosition", data->cam->pos);
		printf("\tFOV: %d\n", data->cam->fov);
		print_t_v3("\tAxis (Orientation)", data->cam->axis);
	}
	else
	{
		printf("Camera: NULL\n");
	}

	// Print spot lights details
	if (data->sLight)
	{
		printf("Spot Lights:\n");
		t_sLight *sLight = data->sLight;
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

	// Print objects details
	if (data->obj)
	{
		printf("Objects:\n");
		t_obj *obj = data->obj;
		while (obj)
		{
			printf("\tType: %d\n", obj->type);
			printf("\tIndex: %d\n", obj->i);
			print_t_v3("\tPosition", obj->pos);
			print_t_v3("\tAxis (Orientation)", obj->axis);
			print_t_rgb("\tColor", obj->rgb);
			printf("\tSize: %.2f\n", obj->size);
			printf("\tHeight: %.2f\n", obj->height);
			printf("\tSphere Radius: %.2f\n", obj->sphere_radius);
			print_t_v3("\tRay Start (Camera Position)", obj->ray_start);
			print_t_v3("\tSphere Center", obj->sphere_center);
			printf("\n");
			obj = obj->next;
		}
	}
	else
	{
		printf("Objects: NULL\n");
	}
}
