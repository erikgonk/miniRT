/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 13:04:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"
#include "threads.h"

void	*process_rows(void *arg)
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
			pthread_mutex_lock(data->data->m_god);
			if (!data->data->god)
			{
				pthread_mutex_unlock(data->data->m_god);
				pthread_exit(NULL);
				return (NULL);
			}
			pthread_mutex_unlock(data->data->m_god);
			data->image[idyx[1]][idyx[2]] = \
					trace_ray(data->rays[idyx[1]][idyx[2]], data->data);
		}
		idyx[1] += NUM_THREADS;
	}
	pthread_exit(NULL);
}

void	render_with_threads(t_data *data, t_ray **rays, uint32_t **image)
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
		pthread_create(&threads[i], NULL, process_rows, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

uint32_t	**average_samples(t_data *data, uint32_t **s1, uint32_t **s2)
{
	uint32_t	**res;
	int			x;
	int			y;

	x = -1;
	res = init_image_(data);
	while (++x < data->y)
	{
		y = -1;
		while (++y < data->x)
			res[x][y] = average(s1[x][y], s2[x][y]);
	}
	return (res);
}

uint32_t	**render(t_data *data)
{
	t_ray		**rays;
	t_vp		*vp;
	uint32_t	**image;

	vp = init_viewport(data->cam, data->x, data->y);
	rays = init_rays(data, data->cam, vp);
	image = init_image_(data);
	if (!image)
		return (NULL);
	render_with_threads(data, rays, image);
	free_render(data, vp, rays);
	return (image);
}
