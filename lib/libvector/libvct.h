/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:33:09 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 22:27:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVCT_H
# define LIBVCT_H

# include <math.h>

typedef struct s_v3
{
	float			x;
	float			y;
	float			z;
}					t_v3;

t_v3			vdefine(float x, float y, float z);
t_v3			vadd(t_v3 a, t_v3 b);
t_v3			vsubstract(t_v3 a, t_v3 b);
t_v3			vproduct(t_v3 a, t_v3 b);
float			dot(t_v3 a, t_v3 b);
t_v3			cross(t_v3 a, t_v3 b);
float			mod(t_v3 v);
t_v3			normalize(t_v3 p);
float			vsin(t_v3 a, t_v3 b);
float			vcos(t_v3 a, t_v3 b);
t_v3			vmul(float n, t_v3 p);
float			distance(t_v3 p1, t_v3 p2);
t_v3			x_axis_rotation(t_v3 vec, float angle);
t_v3			y_axis_rotation(t_v3 vec, float angle);
t_v3			z_axis_rotation(t_v3 vec, float angle);
t_v3			scalar_div(t_v3 vec, float scalar);

#endif
