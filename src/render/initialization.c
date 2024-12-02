/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:37:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 14:01:44 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../lib/libvector/libvct.h"
#include "../inc/miniRT.h"

/**
 * init_projection_plane - Inicializa el plano de proyección.
 * @cam: Puntero a la cámara que define la posición, orientación y FOV.
 *
 * Calcula las dimensiones y los vectores ortogonales (forward, right, up)
 * del plano de proyección basado en la cámara. Estos valores son
 * fundamentales para generar rayos que atraviesan cada píxel de la ventana.
 *
 * Retorna una estructura t_projplane inicializada.
 */
t_vp init_viewport(t_cam *camera, int width, int height)
{
    t_vp viewport;
    float aspect_ratio = (float)width / (float)height;
    float viewport_width = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0);
    float viewport_height = viewport_width / aspect_ratio;

    // Vector "forward" basado en la orientación de la cámara
    t_v3 forward = normalize(camera->axis);
    t_v3 right = normalize(cross((t_v3){0, 1, 0}, forward)); // Cruz entre 'up' y 'forward'
    t_v3 up = normalize(cross(forward, right));

    // Centro del plano de proyección
    viewport.origin = camera->pos;

    // Calcular las dimensiones físicas del viewport
	viewport.horizontal = scal_x_vec(viewport_width, right);
	viewport.vertical = scal_x_vec(viewport_height, up);

	// Calcular la esquina inferior izquierda
	viewport.lower_left = vsubstract(
		vsubstract(
			vsubstract(viewport.origin, scalar_div(viewport.horizontal, 2)),
			scalar_div(viewport.vertical, 2)
		),
		forward
	);

    return viewport;
}

/**
 * init_rays - Inicializa todos los rayos de la ventana.
 * @rays: Matriz bidimensional donde se almacenarán los rayos.
 * @pplane: Puntero al plano de proyección previamente inicializado.
 * @cam: Puntero a la cámara que define el origen de los rayos.
 *
 * Recorre todos los píxeles de la ventana y genera un rayo para cada uno
 * utilizando el plano de proyección y la cámara. Los rayos son almacenados
 * en la matriz bidimensional proporcionada.
 */
t_ray	**init_rays(t_cam *camera, t_vp *vp, int width, int height)
{
	t_ray **rays = malloc(height * sizeof(t_ray *));
	if (!rays)
		return NULL;
	for (int y = 0; y < height; y++)
	{
		rays[y] = malloc(width * sizeof(t_ray));
		if (!rays[y])
		{
			// Liberar memoria en caso de error
			for (int j = 0; j < y; j++)
				free(rays[j]);
			free(rays);
			return NULL;
		}
		for (int x = 0; x < width; x++)
		{
			// Calcular la posición del píxel en el viewport
			float u = (float)x / (float)(width - 1);
			float v = (float)y / (float)(height - 1);
			t_v3 pixel_position = vadd(
				vadd(
					vp->lower_left,
					scal_x_vec(u, vp->horizontal)
				),
				scal_x_vec(v, vp->vertical)
			);
			// Crear el rayo
			rays[y][x].origin = camera->pos;
			rays[y][x].direction = normalize(vsubstract(pixel_position, camera->pos));
		}
	}
	return rays;
}

//init Data for a quadratic equation
void	init_quadratic(t_quadratic *quad, float a, float b, float c)
{
	quad->a = a;
	quad->b = b;
	quad->c = c;
	quad->discriminant = b * b - 4 * a * c;
	quad->t1 = INFINITY;
	quad->t2 = INFINITY;
}

//Memmory for the final image
int **init_image_(int width, int height)
{
    // Asignar memoria para las filas
    int **image = malloc(height * sizeof(int *));
    if (!image)
        return NULL;

    // Asignar memoria para cada fila y verificar errores
    for (int y = 0; y < height; y++)
    {
        image[y] = malloc(width * sizeof(int));
        if (!image[y])
        {
            // Liberar memoria asignada en caso de error
            for (int j = 0; j < y; j++)
                free(image[j]);
            free(image);
            return NULL;
        }
    }

    // Inicializar todos los píxeles a un color predeterminado (opcional, por ejemplo, negro)
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = 0x000000; // Negro (RGB: 0,0,0)
        }
    }

    return image;
}
