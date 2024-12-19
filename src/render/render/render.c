/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:09:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

uint32_t	**render(t_data *scene, int x, int y)
{
	t_ray		**rays;
	t_vp		*vp;
	uint32_t	**image;

	vp = init_viewport(scene->cam, WH, HG);
	rays = init_rays(scene->cam, vp);
	image = init_image_();
	if (!image)
		return (NULL);
	while (y < HG)
	{
		x = 0;
		while (x < WH)
		{
			image[y][x] = trace_ray(rays[y][x], scene);
			x++;
		}
		y++;
	}
	free_render(vp, rays);
	return (image);
}
