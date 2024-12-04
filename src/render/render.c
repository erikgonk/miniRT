/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/04 16:38:26 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

void print_ray_directions(t_ray **rays, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            printf("Ray[%d][%d] direction: (%f, %f, %f)\n",
                   y, x,
                   rays[y][x].direction.x,
                   rays[y][x].direction.y,
                   rays[y][x].direction.z);
        }
    }
}
//Returns bidimensional RGB array to make the final image, x and y must be 0
int	**render(t_data *scene)
{
	t_ray	**rays;
	t_vp	*vp;
	uint32_t		**image;

	vp = init_viewport(scene->cam, WH, HG);
	rays = init_rays(scene->cam, vp, WH, HG);
	image = init_image_(WH, HG);
	if (!image)
		return (NULL);
	for (int y = 0; y < HG; y++) // Fila
	{
		for (int x = 0; x < WH; x++) // Columna
		{
			int color = trace_ray(rays[y][x], scene->obj);
		    image[y][x] = color;
		}
	}
	return (image);
}
