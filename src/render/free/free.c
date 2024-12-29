/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:12 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 11:04:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"

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

void	free_data(t_data *data)
{
	t_obj		*obj;
	t_slight	*slight;

	obj = data->obj;
	slight = data->s_light;
	free(data->cam);
	free(data->a_light);
	while (data->s_light)
	{
		data->s_light = data->s_light->next;
		free(slight);
		slight = data->s_light;
	}
	free(data->s_light);
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
	if (data)
		free(data);
}

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
