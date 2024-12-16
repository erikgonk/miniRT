/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:40:08 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/15 20:28:28 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

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
	t_frame	frame;

	camera->axis = normalize(camera->axis);
	viewport = malloc(sizeof(t_vp));
	if (!viewport)
		return (NULL);
	aspect_ratio = (float)width / (float)height;
	viewport->viewport_width = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0);
	viewport->viewport_height = viewport->viewport_width / aspect_ratio;
	frame.forward = camera->axis;
	frame.right = calculate_right(frame.forward);
	frame.up = calculate_up(frame.forward, frame.right);
	viewport->origin = camera->pos;
	viewport->horizontal = vmul(viewport->viewport_width, frame.right);
	viewport->vertical = vmul(viewport->viewport_height, frame.up);
	viewport->lower_left = vsubstract(vsubstract(vsubstract(viewport->origin, \
										scalar_div(viewport->horizontal, 2)), \
										scalar_div(viewport->vertical, 2)), \
										frame.forward);
	return (viewport);
}
