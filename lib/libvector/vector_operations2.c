/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:32:52 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/11 17:50:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvct.h"

// Calcula la magnitud (que tan larga es la flecha)
// La magnitud de un vector indica qué tan "larga" es esa flecha, y se
// calcula usando el Teorema de Pitágoras:
// magnitud = sqrt(x^2 + y^2 + z^2).
double	mod(t_v3 v)
{
	return (sqrt(dot(v, v)));
}

// Normaliza un vector para que su magnitud sea 1, manteniendo su dirección.
t_v3	normalize(t_v3 p)
{
	t_v3	nv;
	double	mod;

	mod = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	nv.x = p.x / mod;
	nv.y = p.y / mod;
	nv.z = p.z / mod;
	return (nv);
}

// Calcula el seno del ángulo entre dos vectores.
double	vsin(t_v3 a, t_v3 b)
{
	return (sqrt(1 - pow(vcos(a, b), 2)));
}

// Calcula el coseno del ángulo entre dos vectores.
double	vcos(t_v3 a, t_v3 b)
{
	return (dot(a, b) / (mod(a) * mod(b)));
}

// Escala un vector multiplicándolo por un escalar.
// Hace un vector mas grande o mas pequeno
t_v3	vmul(double n, t_v3 p)
{
	t_v3	v;

	v.x = n * p.x;
	v.y = n * p.y;
	v.z = n * p.z;
	return (v);
}
