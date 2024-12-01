/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:25:17 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/01 21:25:02 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
// short alias for window size
# define WH WINDOW_WIDTH
# define HG WINDOW_HEIGHT

# define PPLANEDISTANCE 1.0f

typedef unsigned char	t_uchar;

typedef struct s_projection_plane
{
	float	width;
	float	height;
	float	distance;
	t_v3	forward;
	t_v3	right;
	t_v3	up;
}		t_projplane;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}				t_ray;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t1; //inteseccion de entrada
	float	t2; //interseccion de salida
}			t_quadratic;


// Return uint32 colour with alpha.
uint32_t	get_acolour(t_uchar alpha, t_uchar r, t_uchar g, t_uchar b);
t_projplane	*init_projection_plane(t_cam *cam);
void		init_rays(t_ray **rays, t_projplane *pplane, t_cam *cam);
void		init_quadratic(t_quadratic *quad, float a, float b, float c);
bool		solve_quadratic(t_quadratic *quad);
t_rgb		trace_ray(t_ray *ray, t_data *scene);
t_rgb		apply_ambient_light(t_rgb obj_color, t_aLight *ambient_light);
t_rgb		**render(t_data *scene, int x, int y);
bool		intersect_sphere(t_ray *ray, t_obj *sphere, float *t);
t_rgb		**init_image_(int width, int height);

#endif
