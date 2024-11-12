/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:17:06 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/12 12:48:19 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Function to calculate the dot product of two vectors
// This helps us determine angles between directions, which we'll need for shading
float dot(Vector3 a, Vector3 b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Function to subtract two vectors (essentially finding the difference between two points)
// We'll use this to find distances between points, like from the camera to the sphere
Vector3 subtract(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

// This function checks if a ray (an imaginary line from our camera) hits the sphere.
// If it does, it returns the distance to the hit point. If not, it returns -1 (no hit).
float sphere_ray_intersect(Vector3 ray_start, Vector3 ray_direction, Vector3 sphere_center, float sphere_radius) {
    Vector3 s = subtract(ray_start, sphere_center); // Find vector from sphere center to ray start
    float b = dot(s, ray_direction);                // Check alignment of ray and sphere center
    float c = dot(s, s) - sphere_radius * sphere_radius; // Check if the ray is close enough to hit
    float h = b * b - c;                            // Calculate if there’s an actual hit
    if (h < 0.0) {
        return -1.0f;                               // If h < 0, there’s no hit (miss)
    }
    h = sqrtf(h);                                   // Calculate the exact distance to the hit point
    return fmaxf(-b - h, 0.0f);                     // Return the closest hit distance
}

// Function to calculate the normal at a point on the sphere’s surface
// This normal direction is used to calculate shading (brightness) on the sphere
Vector3 sphere_normal(Vector3 sphere_center, Vector3 point) {
    Vector3 n = subtract(point, sphere_center); // Find direction from center to the surface point
    float norm = sqrtf(dot(n, n));              // Calculate length of this direction (distance)
    Vector3 result = { n.x / norm, n.y / norm, n.z / norm }; // Normalize (make it length 1)
    return result;
}

// Draw a single pixel at position (x, y) with the specified color if within bounds
void draw_pixel(mlx_image_t* img, int x, int y, uint32_t color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        mlx_put_pixel(img, x, y, color);  // Draw the pixel using MLX42's function
    }
}

int main() {
    // Initialize MLX42 and create a window with specified width and height
    mlx_t* mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Ray-Traced Sphere", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Create an image to draw on within the window
    mlx_image_t* img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img) {
        fprintf(stderr, "Failed to create image\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    Vector3 ray_start = { 0.0, 0.0, -5.0 };      // Camera position (where our rays start from)
    Vector3 sphere_center = { 0.0, 0.0, 0.0 };   // Position of the sphere
    float sphere_radius = 1.0;                   // Radius (size) of the sphere

    // Loop through each pixel in the window
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            // Set up a direction from the camera to this pixel
            Vector3 ray_direction = {
                (x - WINDOW_WIDTH / 2.0f) / (float)WINDOW_WIDTH,
                (y - WINDOW_HEIGHT / 2.0f) / (float)WINDOW_HEIGHT,
                1.0
            };

            // Normalize (scale) the direction to make it a unit vector
            float mag = sqrtf(dot(ray_direction, ray_direction));
            ray_direction.x /= mag;
            ray_direction.y /= mag;
            ray_direction.z /= mag;

            // Check if this ray hits the sphere
            float t = sphere_ray_intersect(ray_start, ray_direction, sphere_center, sphere_radius);
            if (t > 0.0f) {  // If t > 0, it means the ray hit the sphere
                // Find the exact hit point on the sphere
                Vector3 intersection_point = {
                    ray_start.x + t * ray_direction.x,
                    ray_start.y + t * ray_direction.y,
                    ray_start.z + t * ray_direction.z
                };

                // Get the normal at the intersection point for shading
                Vector3 normal = sphere_normal(sphere_center, intersection_point);

                // Simple shading calculation based on the normal
                float shade = fmaxf(0.0f, dot(normal, (Vector3){0.0, 0.0, -1.0}));
                uint32_t color = ((int)(shade * 255) << 16) | ((int)(shade * 255) << 8) | (int)(shade * 255) | 0xFF000000;

                // Draw the pixel with the calculated color
                draw_pixel(img, x, y, color);
            }
        }
    }
    // Display the image
    mlx_image_to_window(mlx, img, 0, 0);

    // Main loop to keep the window open
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
