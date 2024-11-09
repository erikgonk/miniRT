/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/09 16:13:44 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// Function to calculate the dot product of two vectors
float dot(Vector3 a, Vector3 b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Function to subtract two vectors
Vector3 subtract(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
	return (result);
}

// Sphere-ray intersection function
float sphere_ray_intersect(Vector3 ray_start, Vector3 ray_direction,
		Vector3 sphere_center, float sphere_radius) {
    Vector3 s;
    float b;
    float c;
    float h;
	float t;

	s = subtract(ray_start, sphere_center);
	b = dot(s, ray_direction);
	c = dot(s, s) - sphere_radius * sphere_radius;
	h = b * b - c;
    if (h < 0.0) {
        return 1000.0f; // No intersection
    }

    h = sqrtf(h);
    t = -b - h;
    return (fmaxf(t, 0.0f)); // Return max(t, 0) if the start point is inside the sphere
}

// Function to calculate the normal at a point on the sphere's surface
Vector3 sphere_normal(Vector3 sphere_center, Vector3 point) {
    Vector3 n;
    float norm;

	n = subtract(point, sphere_center);
	norm = sqrtf(dot(n, n));
    Vector3 result;
	result.x = n.x / norm;
	result.y = n.y / norm;
	result.z = n.z / norm;
    return (result);
}

// Example usage
int main() {
    Vector3 ray_start = {0.0, 0.0, -5.0};
    Vector3 ray_direction = {0.0, 0.0, 1.0};
    Vector3 sphere_center = {0.0, 0.0, 0.0};
    float sphere_radius = 1.0;

    float t = sphere_ray_intersect(ray_start, ray_direction, sphere_center, sphere_radius);
    if (t != 1000.0f) {
        printf("Intersection at t = %f\n", t);
        Vector3 intersection_point = {
            ray_start.x + t * ray_direction.x,
            ray_start.y + t * ray_direction.y,
            ray_start.z + t * ray_direction.z
        };
        Vector3 normal = sphere_normal(sphere_center, intersection_point);
        printf("Normal at intersection: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
    } else {
        printf("No intersection\n");
    }

    return 0;
}
