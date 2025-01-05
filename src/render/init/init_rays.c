/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2025/01/05 13:23:58 by shurtado         ###   ########.fr       */
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

t_v3	random_in_unit_disk(void)
{
	t_v3	res;
    float theta;
    float r;

	r = sqrt((float)rand() / RAND_MAX);
	theta = 2.0f * M_PI * ((float)rand() / RAND_MAX);
	res.x =  r * cos(theta);
	res.y = r * sin(theta);
    return (res);
}

void generate_dof_ray(t_ray *ray, t_cam *cam)
{
	t_v3 rd;
	t_v3 offset;
	t_v3 focus_point;
	//a meter en la camara ->
	cam->u = normalize(cross(cam->frame.up,cam->frame.forward));
	cam->v = cross(cam->frame.forward, cam->u);
	// Generar un punto aleatorio en el disco de la lente
	t_v3 random_point = random_in_unit_disk();
	rd.x = random_point.x * cam->focus_dist;
	rd.y = random_point.y * cam->focus_dist;
	rd.z = 0.0f; // En el plano de la lente, no hay componente Z

	// Desplazamiento en el plano de la cámara
	offset = vadd(vmul(rd.x, cam->u), vmul(rd.y, cam->v));

	// Calcular el punto de enfoque en el plano focal
	focus_point = vadd(ray->origin, vmul(cam->focus_dist, ray->direction));

	// Calcular el nuevo origen del rayo desplazado por el disco de la lente
	ray->origin = vadd(ray->origin, offset);

	// Calcular la nueva dirección hacia el punto de enfoque desde el nuevo origen
	ray->direction = normalize(vsub(focus_point, ray->origin));
}

void	init_single_ray(t_ray *ray, t_vp *vp, t_cam *cam, float *uv)
{
	t_v3	pixel_position;

	pixel_position = vadd(vadd(vp->lower_left, vmul(uv[0], vp->horizontal)),
			vmul(uv[1], vp->vertical));
	ray->origin = cam->pos;
	ray->direction = normalize(vsub(pixel_position, cam->pos));
	ray->i_direction = normalize(vneg(ray->direction));
	if (cam->focus_dist)
		generate_dof_ray(ray, cam);
}

t_ray	*init_ray_row(t_data *data, t_cam *cam, t_vp *vp, int y)
{
	t_ray	*row;
	int		x;
	float	uv[2];
	float	r_x;
	float	r_y;

	row = malloc(data->x * sizeof(t_ray));
	if (!row)
		return (NULL);
	x = 0;
	while (x < data->x)
	{
		r_x = (float)rand() / (float)RAND_MAX;
		r_y = (float)rand() / (float)RAND_MAX;
		uv[0] = ((float)x + r_x) / (float)(data->x- 1);
		uv[1] =  1.0f - ((float)y + r_y) / (float)(data->y - 1);
		// uv[0] = ((float)x) / (float)(data->x- 1);
		// uv[1] =  1.0f - ((float)y) / (float)(data->y - 1);
		init_single_ray(&row[x], vp, cam, uv);
		x++;
	}
	return (row);
}

t_ray	**init_rays(t_data *data, t_cam *cam, t_vp *vp)
{
	t_ray	**rays;
	int		y;

	rays = malloc(data->y * sizeof(t_ray *));
	if (!rays)
		return (NULL);
	y = 0;
	while (y < data->y)
	{
		rays[y] = init_ray_row(data, cam, vp, y);
		if (!rays[y])
		{
			free_rays(rays, y);
			return (NULL);
		}
		y++;
	}
	return (rays);
}
