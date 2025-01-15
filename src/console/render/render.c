/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 01:56:28 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 03:01:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"
#include "threads.h"

uint32_t	trace_fast(t_ray ray, t_data *data)
{
	double	t_min;
	t_obj	*closest_obj;
	t_rgb	alight;

	alight.r = 50;
	alight.g = 50;
	alight.b = 50;
	t_min = INFINITY;
	closest_obj = find_closest(data, &ray, data->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	return (get_colour(color_add(alight, closest_obj->a_rgb)));
}

void	*cprocess_rows(void *arg)
{
	t_thread_data	*data;
	int				idyx[3];

	data = (t_thread_data *)arg;
	idyx[0] = data->thread_id;
	idyx[1] = idyx[0];
	while (idyx[1] < data->data->y)
	{
		idyx[2] = -1;
		while (++idyx[2] < data->data->x)
		{
			if (idyx[1] % 2 == 0 && idyx[2] % 2 == 0)
				data->image[idyx[1]][idyx[2]] = \
					trace_fast(data->rays[idyx[1]][idyx[2]], data->data);
			if (idyx[1] != 0 && idyx[2] != 0)
				data->image[idyx[1] - 1][idyx[2] -1] = \
				data->image[idyx[1]][idyx[2]];
		}
		idyx[1] += NUM_THREADS;
	}
	pthread_exit(NULL);
}

void	c_render(t_data *data, t_ray **rays, uint32_t **image)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].thread_id = i;
		thread_data[i].rays = rays;
		thread_data[i].data = data;
		thread_data[i].image = image;
		pthread_create(&threads[i], NULL, cprocess_rows, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

uint32_t	**console_render(t_data *data)
{
	t_ray		**rays;
	t_vp		*vp;
	uint32_t	**image;

	vp = init_viewport(data->cam, data->x, data->y);
	rays = init_raysc(data, data->cam, vp);
	image = init_image_(data);
	if (!image)
		return (NULL);
	c_render(data, rays, image);
	free_render(data, vp, rays);
	return (image);
}
