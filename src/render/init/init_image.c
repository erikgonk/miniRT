/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:37:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 13:31:51 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"


void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!data->mlx)
		exit(er("Failed to initialize MLX42", NULL));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		exit(er("Failed to create image\n", NULL));
	}
}

//Memmory for the final image
uint32_t	**init_image_(void)
{
	uint32_t	**image;
	int			y;
	int			j;
	size_t		row_size;


	image = malloc(HG * sizeof(uint32_t *));
	row_size = WH * sizeof(uint32_t);
	if (!image)
		return (NULL);
	y = 0;
	while (y < HG)
	{
		image[y] = malloc(row_size);
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
