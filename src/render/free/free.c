/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:12 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 12:03:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"

void	free_rays_all(t_ray **rays)
{
	int	i;

	i = W_HG - 1;
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
	while (y < W_HG)
	{
		if (image[y])
			free(image[y]);
		y++;
	}
	free(image);
}
