/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 12:03:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

#include "threads.h"

void	*process_rows(void *arg)
{
	t_thread_data	*data;
	int				id;
	int				y;
	int				x;

	data = (t_thread_data *)arg;
	id = data->thread_id;
	y = id;
	while (y < W_HG)
	{
		x = 0;
		while (x < W_WH)
		{
			data->image[y][x] = trace_ray(data->rays[y][x], data->data);
			x++;
		}
		y += NUM_THREADS;
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

uint32_t	**render(t_data *data, int x, int y)
{
	t_ray		**rays;
	t_vp		*vp;
	uint32_t	**image;

	(void)x;
	(void)y;
	vp = init_viewport(data->cam, W_WH, W_HG);
	rays = init_rays(data->cam, vp);
	image = init_image_();
	if (!image)
		return (NULL);
	render_with_threads(data, rays, image);
	free_render(vp, rays);
	return (image);
}

