/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 11:46:50 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

//Returns bidimensional RGB array to make the final image, x and y must be 0
t_rgb	**render(t_data *scene, int x, int y)
{
	t_ray		**rays;
	t_projplane	*pplane;
	t_rgb		**image;

	rays = malloc(sizeof(t_ray *) * WINDOW_WIDTH);
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		rays[i] = malloc(sizeof(t_ray) * WINDOW_HEIGHT);
	}
	pplane = init_projection_plane(scene->cam);
	init_rays(rays, pplane, scene->cam);
	image = init_image_(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image)
		return (NULL);
	x = 0;
	t_rgb	rgb;


	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			rgb = trace_ray(&rays[x][y], scene);
			image[x][y].r = rgb.r;
			image[x][y].g = rgb.g;
			image[x][y].b = rgb.b;
			y++;
		}
		x++;
	}
	return (image);
}
