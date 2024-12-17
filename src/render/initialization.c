/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:37:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 14:32:12 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

//init Data for a quadratic equation
void	init_quadratic(t_quadratic *quad, float a, float b, float c)
{
	if (fabs(a) < EPSILON)
	{
		quad->a = 0.0f;
		quad->discriminant = -1.0f;
		quad->t1 = INFINITY;
		quad->t2 = INFINITY;
		return ;
	}
	quad->a = a;
	quad->b = b;
	quad->c = c;
	quad->discriminant = b * b - 4 * a * c;
	quad->t1 = INFINITY;
	quad->t2 = INFINITY;
}

//Memmory for the final image
uint32_t	**init_image_(void)
{
	uint32_t	**image;
	int			y;
	int			j;

	image = malloc(HG * sizeof(uint32_t *));
	if (!image)
		return (NULL);
	y = 0;
	while (y < HG)
	{
		image[y] = malloc(WH * sizeof(uint32_t));
		if (!image[y])
		{
			j = 0;
			while (j < y)
			{
				free(image[j]);
				j++;
			}
			free(image);
			return (NULL);
		}
		y++;
	}
	return (image);
}
