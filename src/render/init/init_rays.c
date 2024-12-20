/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:36:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/20 12:41:48 by shurtado         ###   ########.fr       */
/*                                                                            */
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

t_ray	***init_multiple_rays(t_data *data, t_vp *vp)
{
	t_ray	***rays;
	t_v3	origin[data->aa];

	rays = malloc (sizeof(t_ray) * data->aa);
	return (rays);
}

t_ray	***init_rays(t_data *data, t_cam *camera, t_vp *vp)
{
	t_ray 	***full;
	t_ray	**rays;
	int		y;

	if (data->aa != 0)
		return (init_multiple_rays(data, vp));
	full = malloc(sizeof(t_ray **) * 2);
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
	full[0] = rays;
	full[1] = NULL;
	return (full);
}
