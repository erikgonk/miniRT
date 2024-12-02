/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 14:02:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

//Returns bidimensional RGB array to make the final image, x and y must be 0
int	**render(t_data *scene)
{
	t_ray	**rays;
	t_vp	vp;
	int		**image;

	vp = init_viewport(scene->cam, WH, HG);
	rays = init_rays(scene->cam, &vp, WH, HG);
	image = init_image_(HG, WH);
	if (!image)
		return (NULL);
	for (int y = 0; y < HG; y++) // Fila
	{
		for (int x = 0; x < WH; x++) // Columna
		{
		    image[y][x] = trace_ray(rays[y][x], scene);
		}
	}
	return (image);
}
