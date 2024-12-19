/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:12 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 16:08:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"

void	free_rays_all(t_ray **rays)
{
	int	i;

	i = HG - 1;
	while (i >= 0)
	{
		free(rays[i]);
		i--;
	}
	free(rays);
}

void	free_render(t_vp *vp, t_ray **rays)
{
	free(vp);
	free_rays_all(rays);
}

void	free_image_all(uint32_t **image)
{
	int	y;

	if (!image)
		return ;
	y = 0;
	while (y < HG)
	{
		if (image[y])
			free(image[y]);
		y++;
	}
	free(image);
}
