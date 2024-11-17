/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:41:39 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/17 17:59:23 by erigonza         ###   ########.fr       */
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

float	calculate_lighting(t_v3 point, t_v3 normal, t_v3 light_position) {
    // Vector from the point on the sphere to the light source
    t_v3 light_dir = subtract(light_position, point);
    
    // Normalize the light direction
    float mag = sqrtf(dot(light_dir, light_dir));
    light_dir.x /= mag;
    light_dir.y /= mag;
    light_dir.z /= mag;
    
    // Calculate the dot product between the normal and the light direction
    float intensity = fmaxf(dot(normal, light_dir), 0.0f); // Prevent negative lighting
    
    return intensity; // Return the intensity, which will be between 0 and 1
}

void	ft_sphere(t_data *data, mlx_image_t *img)
{
	t_v3		ray_direction;
	t_v3		intersection_point;
	float		mag;
	float		t; 

	float aR = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;					// Calculate aspect ratio
	int y = -1;
	while (++y < WINDOW_HEIGHT)											// Loop through each pixel in the window
	{
		int x = -1;
		while (++x < WINDOW_WIDTH)
		{
            t_v3 ray_direction = vDefine(								// Set up a direction from the camera to this pixel
                ((x - WINDOW_WIDTH / 2.0f) / (float)WINDOW_WIDTH) * aR,
                (y - WINDOW_HEIGHT / 2.0f) / (float)WINDOW_HEIGHT,
                1.0f
            );
            mag = sqrtf(dot(ray_direction, ray_direction));				// Normalize (scale) the direction to make it a unit vector
			ray_direction = vDefine(ray_direction.x /= mag,
									ray_direction.y /= mag,
									ray_direction.z /= mag);
            t = sphere_ray_intersect(data->ray_start, ray_direction,	// Check if this ray hits the sphere
					data->sphere_center, data->sphere_radius);
            if (t > 0.0f)												// If t > 0, it means the ray hit the sphere
			{
                t_v3 intersection_point = vDefine(
								data->ray_start.x + t * ray_direction.x,// Find the exact hit point on the sphere
								data->ray_start.y + t * ray_direction.y,
								data->ray_start.z + t * ray_direction.z);// Draw the pixel with the calculated color
                draw_pixel(img, x, y, data->color);
            }
		}
	}
}
