/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:37:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 16:43:05 by shurtado         ###   ########.fr       */
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

uint32_t	**average_samples(uint32_t **sample1, uint32_t **sample2)
{
	uint32_t	**res;
	int 		x;
	int			y;

	x = -1;
	res = init_image_();
	while (++x < W_HG)
	{
		y = -1;
		while (++y < W_WH)
			res[x][y] = ((uint64_t)sample1[x][y] + (uint64_t)sample2[x][y]) / 2;
	}
	return (res);
}

float	*generate_uv(int x, int y)
{
	float	*uv;

	uv = malloc(2 * sizeof(float));
	if (!uv)
		return (NULL);
	// uv[0] = (float)x / (float)(WH - 1) + ((float)rand() \
			// / (RAND_MAX + 1.0)) / (float)(WH - 1);
	// uv[1] = 1.0f - (float)y / (float)(HG - 1) + ((float)rand() \
			// / (RAND_MAX + 1.0)) / (float)(HG - 1);
	uv[0] = (float)x / (float)(W_WH - 1) + (((float)rand() / (RAND_MAX + 1.0)) / 2.0f) / (float)(W_WH - 1);
	uv[1] = 1.0f - (float)y / (float)(W_HG - 1) + (((float)rand() / (RAND_MAX + 1.0)) / 2.0f) / (float)(W_HG - 1);
	return (uv);
}

uint32_t	**render(t_data *data, int x, int y)
{
	t_ray		**rays;
	t_vp		*vp;
	uint32_t	**image;
	static int 	flag;


	(void)x;
	(void)y;
	vp = init_viewport(data->cam, W_WH, W_HG);
	rays = init_rays(data->cam, vp);
	image = init_image_();
	if (!image)
	        return (NULL);
	render_with_threads(data, rays, image);
	//render_without_threads(data, rays, image);
	free_render(vp, rays);
	return (image);
}

