/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:19:10 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/21 10:58:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	**average_samples(uint32_t ***samples, int n_samples, int width, int height)
{
	uint32_t	**i_result;
	int			i[3];
	uint64_t	sum[3];
	uint8_t		avg[3];
	uint32_t	color;

	i_result = init_image_();
	i[1] = -1;
	while (++i[1] < height)
	{
		i[0] = -1;
		while (++i[0] < width)
		{
			sum[0] = 0;
			sum[1] = 0;
			sum[2] = 0;
			i[2] = -1;
			while (++i[2] < n_samples)
			{
				color = samples[i[2]][i[1]][i[0]];
				sum[0] += (color >> 16) & 0xFF;
				sum[1] += (color >> 8) & 0xFF;
				sum[2] += color & 0xFF;
			}
			avg[0] = sum[0] / n_samples;
			avg[1] = sum[1] / n_samples;
			avg[2] = sum[2] / n_samples;
			i_result[i[1]][i[0]] = (255 << 24) | (avg[0] << 16) \
									| (avg[1] << 8) | avg[2];
		}
	}
	return (i_result);
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
	uv[0] = (float)x / (float)(WH - 1) + (((float)rand() / (RAND_MAX + 1.0)) / 2.0f) / (float)(WH - 1);
	uv[1] = 1.0f - (float)y / (float)(HG - 1) + (((float)rand() / (RAND_MAX + 1.0)) / 2.0f) / (float)(HG - 1);
	return (uv);
}
