/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:33:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/10 14:57:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVCT_H
# define LIBVCT_H

# include <math.h>
# include <stdbool.h>

typedef struct s_v3
{
	double			x;
	double			y;
	double			z;
}					t_v3;

t_v3			vdefine(double x, double y, double z);
t_v3			vadd(t_v3 a, t_v3 b);
t_v3			vsub(t_v3 a, t_v3 b);
t_v3			vproduct(t_v3 a, t_v3 b);
double			dot(t_v3 a, t_v3 b);
t_v3			cross(t_v3 a, t_v3 b);
double			mod(t_v3 v);
t_v3			normalize(t_v3 p);
double			vsin(t_v3 a, t_v3 b);
double			vcos(t_v3 a, t_v3 b);
t_v3			vmul(double n, t_v3 p);
double			distance(t_v3 p1, t_v3 p2);
t_v3			x_axis_rotation(t_v3 vec, double angle);
t_v3			y_axis_rotation(t_v3 vec, double angle);
t_v3			z_axis_rotation(t_v3 vec, double angle);
t_v3			scalar_div(t_v3 vec, double scalar);
t_v3			vneg(t_v3 v);
t_v3			vrefl(t_v3 v, t_v3 n);
bool			v3_compare(t_v3 a, t_v3 b);
double			length(t_v3 v);

#endif
