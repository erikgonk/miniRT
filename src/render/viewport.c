/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:40:08 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/10 17:22:57 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "miniRT.h"

static t_v3	calculate_up(t_v3 forward, t_v3 right)
{
	return (normalize(cross(forward, right)));
}

static t_v3	calculate_right(t_v3 forward)
{
	t_v3	arbitrary;

	if (fabs(forward.y) > 0.999)
		arbitrary = (t_v3){1, 0, 0};
	else
		arbitrary = (t_v3){0, 1, 0};
	return (normalize(cross(arbitrary, forward)));
}

t_vp	*init_viewport(t_cam *camera, int width, int height)
{
	t_vp	*viewport;
	float	aspect_ratio;
	t_v3	forward;
	t_v3	right;
	t_v3	up;

	viewport = malloc(sizeof(t_vp));
	if (!viewport)
		return (NULL);
	aspect_ratio = (float)width / (float)height;
	viewport->viewport_width = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0);
	viewport->viewport_height = viewport->viewport_width / aspect_ratio;
	forward = camera->axis;
	right = calculate_right(forward);
	up = calculate_up(forward, right);
	viewport->origin = camera->pos;
	viewport->horizontal = vmul(viewport->viewport_width, right);
	viewport->vertical = vmul(viewport->viewport_height, up);
	viewport->lower_left = vsubstract(vsubstract(vsubstract(viewport->origin, \
							scalar_div(viewport->horizontal, 2)), \
							scalar_div(viewport->vertical, 2)), forward);
	return (viewport);
}
