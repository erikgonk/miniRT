/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:39:47 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/08 14:04:32 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void create_side(t_obj **side, t_obj *cube)
{
    t_v3 right;
    t_v3 up;
    t_v3 forward;
    t_v3 half_size;

    forward = normalize(cube->axis);
    right = normalize(cross((t_v3){0,1,0}, forward));
    if (vlength(right) < EPSILON)
        right = normalize(cross((t_v3){1,0,0}, forward));
    up = normalize(cross(forward, right));
    half_size = vmul(0.5, cube->cube_size);
    side[0]->axis = forward;
    side[0]->right = right;
    side[0]->up = up;
    side[0]->pos = vadd(cube->pos, vmul(half_size.z, forward));
    side[1]->axis = vmul(-1.0, forward);
    side[1]->right = vmul(-1.0, right);
    side[1]->up = up;
    side[1]->pos = vadd(cube->pos, vmul(-half_size.z, forward));
    side[2]->axis = vmul(-1.0, right);
    side[2]->right = vmul(-1.0, forward);
    side[2]->up = up;
    side[2]->pos = vadd(cube->pos, vmul(-half_size.x, right));
    side[3]->axis = right;
    side[3]->right = forward;
    side[3]->up = up;
    side[3]->pos = vadd(cube->pos, vmul(half_size.x, right));
    side[4]->axis = vmul(-1.0, up);
    side[4]->right = right;
    side[4]->up = vmul(-1.0, forward);
    side[4]->pos = vadd(cube->pos, vmul(-half_size.y, up));
    side[5]->axis = up;
    side[5]->right = right;
    side[5]->up = forward;
    side[5]->pos = vadd(cube->pos, vmul(half_size.y, up));
}
void	init_sides(t_data *data)
{
	t_obj	*obj;
	t_obj	**side;
	int		i;

	i = -1;
	obj = data->obj;
	while (obj && obj->type != CU)
		obj = obj->next;
	if (!obj)
		return ;
	side = malloc(sizeof(t_obj *) * 8);
	if (!side)
		exit(er("error: init_sides: malloc", NULL));
	while (++i < 6)
	{
		side[i] = malloc(sizeof(t_obj));
		ft_memcpy(side[i], obj, sizeof(t_obj));
		side[i]->type = SIDE;
		side[i]->next = NULL;
		objadd_back(&data->obj, side[i]);
	}
	create_side(side, obj);
	free(side);
}
