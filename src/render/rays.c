/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:36:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/10 17:22:57 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "miniRT.h"

// Subfunción para liberar la memoria en caso de error
static void	free_rays(t_ray **rays, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(rays[i]);
		i++;
	}
	free(rays);
}

// Subfunción para inicializar un rayo individual
static void	init_single_ray(t_ray *ray, t_vp *vp, t_cam *camera, float *uv)
{
	t_v3	pixel_position;

	pixel_position = vadd(vadd(vp->lower_left, vmul(uv[0], \
				vp->horizontal)), vmul(uv[1], vp->vertical));
	ray->origin = camera->pos;
	ray->direction = normalize(vsubstract(pixel_position, camera->pos));
}

// Subfunción para inicializar una fila de rayos
static t_ray	*init_ray_row(t_cam *camera, t_vp *vp, int y)
{
	t_ray	*row;
	int		x;
	float	uv[2];

	row = malloc(WH * sizeof(t_ray));
	if (!row)
		return (NULL);
	x = 0;
	while (x < WH)
	{
		uv[0] = (float)x / (float)(WH - 1);
		uv[1] = (float)y / (float)(HG - 1);
		init_single_ray(&row[x], vp, camera, uv);
		x++;
	}
	return (row);
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
t_ray	**init_rays(t_cam *camera, t_vp *vp)
{
	t_ray	**rays;
	int		y;

	rays = malloc(HG * sizeof(t_ray *));
	if (!rays)
		return (NULL);
	y = 0;
	while (y < HG)
	{
		rays[y] = init_ray_row(camera, vp, y);
		if (!rays[y])
		{
			free_rays(rays, y);
			return (NULL);
		}
		y++;
	}
	return (rays);
}