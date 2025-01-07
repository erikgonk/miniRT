/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 16:10:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	transform_to_global(t_v3 axis, t_v3 normal)
{
	t_v3	u, v, w;
	t_v3	global_normal;

	w = normalize(axis);
	u = normalize(cross((t_v3){0, 1, 0}, w)); // Vector ortogonal
	if (fabs(dot(u, w)) > EPSILON) // Asegurar ortogonalidad
		u = normalize(cross((t_v3){1, 0, 0}, w));
	v = cross(w, u); // Tercer eje ortogonal

	global_normal = vadd(vmul(normal.x, u), vmul(normal.y, v));
	global_normal = vadd(global_normal, vmul(normal.z, w));
	return normalize(global_normal);
}

t_v3	transform_to_local(t_v3 pos, t_v3 axis, t_v3 point)
{
	t_v3	transformed;
	t_v3	u, v, w;

	w = normalize(axis);
	u = normalize(cross((t_v3){0, 1, 0}, w)); // Vector ortogonal
	if (fabs(dot(u, w)) > EPSILON) // Asegurar ortogonalidad
		u = normalize(cross((t_v3){1, 0, 0}, w));
	v = cross(w, u); // Tercer eje ortogonal

	point = vsub(point, pos); // Trasladar al origen local
	transformed.x = dot(point, u);
	transformed.y = dot(point, v);
	transformed.z = dot(point, w);
	return (transformed);
}

t_v3 calculate_normal_cuboid(t_obj *obj, t_v3 point)
{
	t_v3	local;
	t_v3	normal;

	local = transform_to_local(obj->pos, obj->axis, point);
	if (fabs(local.x - obj->cube.xmin) < EPSILON)
		normal = (t_v3){-1, 0, 0};
	else if (fabs(local.x - obj->cube.xmax) < EPSILON)
		normal = (t_v3){1, 0, 0};
	else if (fabs(local.y - obj->cube.ymin) < EPSILON)
		normal = (t_v3){0, -1, 0};
	else if (fabs(local.y - obj->cube.ymax) < EPSILON)
		normal = (t_v3){0, 1, 0};
	else if (fabs(local.z - obj->cube.zmin) < EPSILON)
		normal = (t_v3){0, 0, -1};
	else if (fabs(local.z - obj->cube.zmax) < EPSILON)
		normal = (t_v3){0, 0, 1};
	else
		normal = (t_v3){0, 0, 0};

	return transform_to_global(obj->axis, normal);
}



// Función para encontrar la intersección con un obj->cubee axis-aligned
bool	hit_cube(t_ray *ray, t_obj *obj, double *t)
{
	double	tmin, tmax;
	double	tymin, tymax;
	double	tzmin, tzmax;
	double t_res;

	// Calcula tmin y tmax para el eje X
	if (ray->direction.x != 0.0)
	{
		tmin = (obj->cube.xmin - ray->origin.x) / ray->direction.x;
		tmax = (obj->cube.xmax - ray->origin.x) / ray->direction.x;
		if (tmin > tmax)
			swap(&tmin, &tmax);
	}
	else
	{
		if (ray->origin.x < obj->cube.xmin || ray->origin.x > obj->cube.xmax)
			return false;
		tmin = -INFINITY;
		tmax = INFINITY;
	}

	// Calcula tmin y tmax para el eje Y
	if (ray->direction.y != 0.0)
	{
		tymin = (obj->cube.ymin - ray->origin.y) / ray->direction.y;
		tymax = (obj->cube.ymax - ray->origin.y) / ray->direction.y;
		if (tymin > tymax)
			swap(&tymin, &tymax);
	}
	else
	{
		if (ray->origin.y < obj->cube.ymin || ray->origin.y > obj->cube.ymax)
			return false;
		tymin = -INFINITY;
		tymax = INFINITY;
	}

	// Actualiza tmin y tmax con el eje Y
	if ((tmin > tymax) || (tymin > tmax)) //
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	// Calcula tmin y tmax para el eje Z
	if (ray->direction.z != 0.0)
	{
		tzmin = (obj->cube.zmin - ray->origin.z) / ray->direction.z;
		tzmax = (obj->cube.zmax - ray->origin.z) / ray->direction.z;
		if (tzmin > tzmax)
			swap(&tzmin, &tzmax);
	}
	else
	{
		if (ray->origin.z < obj->cube.zmin || ray->origin.z > obj->cube.zmax)
			return false;
		tzmin = -INFINITY;
		tzmax = INFINITY;
	}

	// Actualiza tmin y tmax con el eje Z
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	// Verifica si hay intersección válida
	if (tmax < 0)
		return false; // El cubo está detrás del rayo


	if (tmin >= 0)
		t_res = tmin;
	else
		t_res = tmax;
	if (t_res < *t && t >= 0)
	{
		ray->point = vadd(ray->origin, vmul(*t, ray->direction));
		ray->normal = calculate_normal_cuboid(obj, ray->point);
		*t = t_res;
		return true;
	}

	return false;
}
