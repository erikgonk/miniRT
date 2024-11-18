/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:41:39 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/18 16:55:31 by erigonza         ###   ########.fr       */
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

int is_in_shadow(t_sphere *sp, t_v3 point, t_light *light) {
    t_v3 light_dir = subtract(light->pos, point);
    float mag = sqrtf(dot(light_dir, light_dir));
    light_dir = vDefine(light_dir.x / mag, light_dir.y / mag, light_dir.z / mag);

    // Cast a shadow ray from the point to the light source
    float t = sphere_ray_intersect(point, light_dir, sp->sphere_center, sp->sphere_radius);
    
    // If the ray intersects the sphere before reaching the light, it's in shadow
    return (t > 0.0f && t < mag);
}

uint32_t	new_light(t_light *l, t_sphere *sp, t_v3 iPoint)
{
	float			mag;
	uint32_t		color; 
	t_v3			normal;
	t_v3			dir;	// light dir
	float			i;		// intensity 
	

	normal = subtract(iPoint, sp->sphere_center);
	mag = sqrtf(dot(normal, normal));
	normal = vDefine(normal.x / mag, normal.y / mag, normal.z / mag);

	// Calculate light direction
	dir = subtract(l->pos, iPoint);
	mag = sqrtf(dot(dir, dir));
	dir = vDefine(dir.x / mag, dir.y / mag, dir.z / mag);

	// Calculate lighting intensity
	i = fmaxf(dot(normal, dir), 0.0f) * l->br;

	if (is_in_shadow(sp, iPoint, l))
		i = 0.0f;  // No light if in shadow
	else
		i = fmaxf(dot(normal, dir), 0.0f) * l->br;
	// Apply lighting intensity to color
	color = sp->color;
	uint8_t r = fminf(((color >> 16) & 0xFF) * i, 255);
	uint8_t g = fminf(((color >> 8) & 0xFF) * i, 255);
	uint8_t b = fminf((color & 0xFF) * i, 255);
	return ((r << 16) | (g << 8) | b);
}

void	ft_sphere(t_sphere *sp, t_light *light, mlx_image_t *img)
{
	t_v3		ray_direction;
	t_v3		iPoint; // intersection_point
	float		mag;
	float		t; 
	uint32_t	pixelColor;

	if (light->br < 0.0f || light->br > 1.0f)
		er("normal light\n", NULL);
	float aR = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;					// Calculate aspect ratio
	int y = -1;
	while (++y < WINDOW_HEIGHT)											// Loop through each pixel in the window
	{
		int x = -1;
		while (++x < WINDOW_WIDTH)
		{
            ray_direction = vDefine(								// Set up a direction from the camera to this pixel
                ((x - WINDOW_WIDTH / 2.0f) / (float)WINDOW_WIDTH) * aR,
                (y - WINDOW_HEIGHT / 2.0f) / (float)WINDOW_HEIGHT,
                1.0f
            );
            mag = sqrtf(dot(ray_direction, ray_direction));				// Normalize (scale) the direction to make it a unit vector
			ray_direction = vDefine(ray_direction.x / mag,
									ray_direction.y / mag,
									ray_direction.z / mag);
            t = sphere_ray_intersect(sp->ray_start, ray_direction,	// Check if this ray hits the sphere
					sp->sphere_center, sp->sphere_radius);
            if (t > 0.0f)												// If t > 0, it means the ray hit the sphere
			{
                iPoint = vDefine(
								sp->ray_start.x + t * ray_direction.x,// Find the exact hit point on the sphere
								sp->ray_start.y + t * ray_direction.y,
								sp->ray_start.z + t * ray_direction.z);// Draw the pixel with the calculated color
				if (light->br < 0.0f || light->br > 1.0f)
					draw_pixel(img, x, y, sp->color);
				else
				{
					pixelColor = new_light(light, sp, iPoint);
					draw_pixel(img, x, y, pixelColor);
				}
            }
		}
	}
}
