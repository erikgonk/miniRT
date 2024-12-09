/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/07 15:17:43 by shurtado         ###   ########.fr       */
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
    data->aLight->br = 0.24f;
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
    data->sLight->br = 0.6f;
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
        .axis = (t_v3){0.2, 0.99, 0.1},
        .rgb = (t_rgb){0, 0, 225},
        .size = 0.0,
        .height = 0.0,
        .next = data->obj
    };
    data->obj = plane;

    // Crear la esfera.
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
        .pos = (t_v3){-50.0, 6.9, -550.0},
        .axis = (t_v3){0.01, 1.0, 0.1},
        .rgb = (t_rgb){255, 255, 255},
        .size = 5,
        .height = 6,
        .next = data->obj
    };
    data->obj = cylinder;

    return data;
}
