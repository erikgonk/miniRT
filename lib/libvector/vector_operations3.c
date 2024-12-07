/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:32:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/02 13:14:42 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvct.h"

float		distance(t_p3 p1, t_p3 p2)
{
	float d;

	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	return (d);
}

t_p3		x_axis_rotation(t_p3 vec, float angle)
{
	t_p3	row1;
	t_p3	row2;
	t_p3	row3;
	t_p3	rotated;
	float	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_p3){1, 0, 0};
	row2 = (t_p3){0, cos(rad_angle), -sin(rad_angle)};
	row3 = (t_p3){0, sin(rad_angle), cos(rad_angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_p3		y_axis_rotation(t_p3 vec, float angle)
{
	t_p3	row1;
	t_p3	row2;
	t_p3	row3;
	t_p3	rotated;
	float	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_p3){cos(rad_angle), 0, sin(rad_angle)};
	row2 = (t_p3){0, 1, 0};
	row3 = (t_p3){-sin(rad_angle), 0, cos(rad_angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_p3		z_axis_rotation(t_p3 vec, float angle)
{
	t_p3	row1;
	t_p3	row2;
	t_p3	row3;
	t_p3	rotated;
	float	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_p3){cos(rad_angle), -sin(rad_angle), 0};
	row2 = (t_p3){sin(rad_angle), cos(rad_angle), 0};
	row3 = (t_p3){0, 0, 1};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_v3 scalar_div(t_v3 vec, float scalar)
{
	t_v3 result;
	
	if (scalar == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return result;
	}
	result.x = vec.x / scalar;
	result.y = vec.y / scalar;
	result.z = vec.z / scalar;
	return result;
}
