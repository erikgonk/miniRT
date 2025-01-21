/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:12 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/21 12:48:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"

void	free_render(t_data *data, t_vp *vp, t_ray **rays)
{
	free(vp);
	free_rays_all(data, rays);
}

void	free_image_all(t_data *data, uint32_t **image)
{
	int	y;

	if (!image)
		return ;
	y = 0;
	while (y < data->y)
	{
		if (image[y])
			free(image[y]);
		y++;
	}
	free(image);
}

void	free_rays_all(t_data *data, t_ray **rays)
{
	int	i;

	i = data->y - 1;
	while (i >= 0)
	{
		free(rays[i]);
		i--;
	}
	free(rays);
}
