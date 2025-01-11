/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:40:12 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 12:26:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

t_rgb	checkerboard_color(t_obj *obj, t_v3 point)
{
	int	x;
	int	y;

	x = (int)floor(point.x * obj->material.board_scale);
	y = (int)floor(point.z * obj->material.board_scale);
	if ((x + y) % 2 == 0)
		return (obj->a_rgb);
	else
		return (obj->material.rgb_checker);
}
