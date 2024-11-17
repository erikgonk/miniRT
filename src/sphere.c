/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:41:39 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 13:06:03 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

float sphere_ray_intersect(t_v3 ray_start, t_v3 ray_direction,
		t_v3 sphere_center, float sphere_radius)
{
    t_v3		s;
    float		b;
    float		c;
    float		h;

	s =  subtract(ray_start, sphere_center);		// Find vector from sphere center to ray start
	b = dot(s, ray_direction);						// Check alignment of ray and sphere center
	c = dot(s, s) - sphere_radius * sphere_radius;	// Check if the ray is close enough to hit
	h = b * b - c;									// Calculate if there’s an actual hit
    if (h < 0.0)
        return (-1.0f);								// If h < 0, there’s no hit (miss)
    h = sqrtf(h);									// Calculate the exact distance to the hit point
    return (fmaxf(-b - h, 0.0f));					// Return the closest hit distance
}

void	ft_sphere(t_data *data, mlx_image_t *img)
{
	int			y;
	int			x;
	t_v3		ray_direction;
	float		mag;
	float		t; 
	t_v3		intersection_point;
	uint32_t	color;

	y = -1;
    // Loop through each pixel in the window
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (x < WINDOW_WIDTH)
		{
            // Set up a direction from the camera to this pixel
        	ray_direction = vDefine(x - WINDOW_WIDTH / 2.0f / (float)WIDTH,
					y - WINDOW_HEIGHT / 2.0f / (float)HEIGHT, 1.0);
 			// Normalize (scale) the direction to make it a unit vector
            mag = sqrtf(dot(ray_direction, ray_direction));
			ray_direction = vDefine(ray_direction.x /= mag,
					ray_direction.y /= mag, ray_direction.z /= mag);

            // Check if this ray hits the sphere
            t = sphere_ray_intersect(data->ray_start, ray_direction,
					data->sphere_center, data->sphere_radius);
            if (t > 0.0f)							// If t > 0, it means the ray hit the sphere
			{
                // Find the exact hit point on the sphere
                t_v3 intersection_point = vDefine(data->ray_start.x + t * ray_direction.x,
						data->ray_start.y + t * ray_direction.y,
						data->ray_start.z + t * ray_direction.z);
                color = ((int)(25) << 16) | ((int)(25) << 8) | (int)(255) | 0xFF000000;

                // Draw the pixel with the calculated color
                draw_pixel(img, x, y, color);
            }

		}
	}
}
