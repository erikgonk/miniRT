/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/21 10:49:02 by shurtado         ###   ########.fr       */
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
	while (y < HG)
	{
		x = 0;
		while (x < WH)
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

	i = -1;
	while (++i < NUM_THREADS)
	{
		thread_data[i].thread_id = i;
		thread_data[i].rays = rays;
		thread_data[i].data = data;
		thread_data[i].image = image;
		pthread_create(&threads[i], NULL, process_rows, &thread_data[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
}

uint32_t	***init_image_samples(int aa)
{
	int			i;
	uint32_t	***image;

	image = malloc(sizeof(uint32_t **) * (aa + 1));
	if (!image)
		return (NULL);
	image[aa] = NULL;
	i = -1;
	while (++i < aa)
		image[i] = init_image_();
	return (image);
}

t_ray	***init_rays_aa(int aa, t_v3 origin, t_vp *vp)
{
	int			i;
	t_ray		***rays;

	rays = malloc(sizeof(t_ray **) * (aa + 1));
	if (!rays)
		return (NULL);
	rays[aa] = NULL;
	i = -1;
	while (++i < aa)
		rays[i] = init_rays(origin, vp);
	return (rays);
}

uint32_t	**render(t_data *data)
{
	t_ray		***rays;
	t_vp		*vp;
	uint32_t	***samples;
	uint32_t	**i_result;
	int			i;


	vp = init_viewport(data->cam, WH, HG);
	rays = init_rays_aa(data->aa, data->cam->pos, vp);
	samples = init_image_samples(data->aa);
	i = -1;
	while (++i < data->aa)
	{
		render_with_threads(data, rays[i], samples[i]);
		printf("sample %d done\n", i + 1);
	}
	i_result = average_samples(samples, data->aa, WH, HG);
	return (i_result);
}
// free ***rays
//	free_render(vp, rays[0]);
