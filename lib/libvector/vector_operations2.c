/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:32:52 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/10 11:30:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvct.h"

// Calcula la magnitud (que tan larga es la flecha)
// La magnitud de un vector indica qué tan "larga" es esa flecha, y se calcula usando el Teorema de Pitágoras:
// magnitud = sqrt(x^2 + y^2 + z^2).
float		mod(t_p3 v)
{
	return (sqrt(dot(v, v)));
}

// Normaliza un vector para que su magnitud sea 1, manteniendo su dirección.
t_p3		normalize(t_p3 p)
{
	t_p3	nv;
	float	mod;

	mod = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	nv.x = p.x / mod;
	nv.y = p.y / mod;
	nv.z = p.z / mod;
	return (nv);
}

// Calcula el seno del ángulo entre dos vectores.
float		vsin(t_p3 a, t_p3 b)
{
	return (sqrt(1 - pow(vcos(a, b), 2)));
}

// Calcula el coseno del ángulo entre dos vectores.
float		vcos(t_p3 a, t_p3 b)
{
	return (dot(a, b) / (mod(a) * mod(b)));
}

// Escala un vector multiplicándolo por un escalar.
// Hace un vector mas grande o mas pequeno
t_p3		scal_x_vec(float n, t_p3 p)
{
	t_p3	v;

	v.x = n * p.x;
	v.y = n * p.y;
	v.z = n * p.z;
	return (v);
}
