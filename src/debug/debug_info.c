/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/04 15:59:07 by shurtado         ###   ########.fr       */
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
			printf("\n");
			obj = obj->next;
		}
	}
	else
	{
		printf("Objects: NULL\n");
	}
}


t_data *init_example_data(void)
{
    // Asignar memoria para t_data
    t_data *data = malloc(sizeof(t_data));
    if (!data)
        return NULL;

    // Inicializar Ambient Light
    data->aLight = malloc(sizeof(t_aLight));
    if (!data->aLight)
        return NULL;
    data->aLight->br = 0.2;
    data->aLight->rgb = (t_rgb){255, 255, 255};

    // Inicializar Cámara
    data->cam = malloc(sizeof(t_cam));
    if (!data->cam)
        return NULL;
    data->cam->pos = (t_v3){-50.0, 0.0, 20.0};
    data->cam->axis = (t_v3){0.0, 0.0, 1.0};
    data->cam->fov = 70;

    // Inicializar Luz
    data->sLight = malloc(sizeof(t_sLight));
    if (!data->sLight)
        return NULL;
    data->sLight->pos = (t_v3){-40.0, 50.0, 0.0};
    data->sLight->br = 0.6;
    data->sLight->rgb = (t_rgb){10, 0, 255};
    data->sLight->next = NULL;

    // Inicializar Objetos
    data->obj = NULL;

    // Crear el plano
    t_obj *plane = malloc(sizeof(t_obj));
    if (!plane)
        return NULL;
    *plane = (t_obj){
        .type = 'p',
        .pos = (t_v3){0.0, 0.0, -10.0},
        .axis = (t_v3){0.0, 1.0, 0.0},
        .rgb = (t_rgb){0, 0, 225},
        .size = 0.0,
        .height = 0.0,
        .next = data->obj
    };
    data->obj = plane;

    // Crear la esfera
    t_obj *sphere = malloc(sizeof(t_obj));
    if (!sphere)
        return NULL;
    *sphere = (t_obj){
        .type = 's',
        .pos = (t_v3){-50.0, 0.0, 0.0},
        .axis = {0},
        .rgb = (t_rgb){255, 0, 0},
        .size = 10.0,
        .height = 0.0,
        .next = data->obj
    };
    data->obj = sphere;

    // Crear el cilindro
    t_obj *cylinder = malloc(sizeof(t_obj));
    if (!cylinder)
        return NULL;
    *cylinder = (t_obj){
        .type = 'c',
        .pos = (t_v3){50.0, 0.0, 20.6},
        .axis = (t_v3){0.0, 0.0, 1.0},
        .rgb = (t_rgb){10, 0, 255},
        .size = 14.2,
        .height = 21.42,
        .next = data->obj
    };
    data->obj = cylinder;

    return data;
}
