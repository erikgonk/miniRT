/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2024/12/21 11:45:09 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

void	free_rays(t_ray **rays, int rows)
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

void	init_single_ray(t_ray *ray, t_vp *vp, t_cam *camera, float *uv)
{
	t_v3	pixel_position;

	pixel_position = vadd(vadd(vp->lower_left, vmul(uv[0], vp->horizontal)),
			vmul(uv[1], vp->vertical));
	ray->origin = camera->pos;
	ray->direction = normalize(vsub(pixel_position, camera->pos));
	ray->i_direction = normalize(vneg(ray->direction));
}

t_ray	*init_ray_row(t_cam *camera, t_vp *vp, int y)
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
		uv[1] = 1.0f - (float)y / (float)(HG - 1);
		init_single_ray(&row[x], vp, camera, uv);
		x++;
	}
	return (row);
}

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
