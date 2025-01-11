/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 12:36:06 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include "render.h"

void	print_t_rgb(const char *label, t_rgb rgb)
{
	printf("%s -> r: %u, g: %u, b: %u\n", label, rgb.r, rgb.g, rgb.b);
}

void	print_t_v3(const char *label, t_v3 vec)
{
	printf("%s -> x: %.2f, y: %.2f, z: %.2f\n", label, vec.x, vec.y, vec.z);
}

uint32_t	**render_without_threads(t_data *data, t_ray **rays, \
		uint32_t **image)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->y)
	{
		x = 0;
		while (x < data->x)
		{
			image[y][x] = trace_ray(rays[y][x], data);
			x++;
		}
		y++;
	}
	return (image);
}
