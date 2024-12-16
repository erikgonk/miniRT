/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:33:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/16 01:14:24 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvct.h"

// Crea y devuelve un vector 3D con las coordenadas especificadas.
t_v3	vdefine(float x, float y, float z)
{
	t_v3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

// Suma dos vectores 3D y devuelve el vector resultante.
t_v3	vadd(t_v3 a, t_v3 b)
{
	t_v3	p;

	p.x = a.x + b.x;
	p.y = a.y + b.y;
	p.z = a.z + b.z;
	return (p);
}

// Resta dos vectores 3D y devuelve el vector resultante.
t_v3	vsub(t_v3 a, t_v3 b)
{
	t_v3	p;

	p.x = a.x - b.x;
	p.y = a.y - b.y;
	p.z = a.z - b.z;
	return (p);
}

// Calcula y devuelve el producto punto de dos vectores 3D.
float	dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Calcula y devuelve el producto cruz de dos vectores 3D.
t_v3	cross(t_v3 a, t_v3 b)
{
	t_v3	cp;

	cp.x = a.y * b.z - a.z * b.y;
	cp.y = a.z * b.x - a.x * b.z;
	cp.z = a.x * b.y - a.y * b.x;
	return (cp);
}
