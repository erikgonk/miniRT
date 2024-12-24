/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:37:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 12:04:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(W_WH, W_HG, "miniRT", true);
	if (!data->mlx)
		exit(er("Failed to initialize MLX42", NULL));
	data->img = mlx_new_image(data->mlx, W_WH, W_HG);
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

	image = malloc(W_HG * sizeof(uint32_t *));
	row_size = W_WH* sizeof(uint32_t);
	if (!image)
		return (NULL);
	y = -1;
	while (++y < W_HG)
	{
		image[y] = malloc(row_size);
		if (!image[y])
		{
			j = -1;
			while (++j < y)
				free(image[j]);
			free(image);
			return (NULL);
		}
	}
	return (image);
}
