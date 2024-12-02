/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:25:17 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/02 11:35:22 by shurtado         ###   ########.fr       */
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
int	get_acolour(t_uchar alpha, t_uchar r, t_uchar g, t_uchar b);
//Calcula el pano de proyeccion, a traves del fov.
t_projplane	*init_projection_plane(t_cam *cam);
//establece el origen y destino de un array bidimensional de rayos
void		init_rays(t_ray **rays, t_projplane *pplane, t_cam *cam);
//Inicia la estructura de datos para una ecuacion cuadratica
void		init_quadratic(t_quadratic *quad, float a, float b, float c);
//Resuelve una ecuacion cuadratica, para almacenar en t1 y t2 las intersecciones si las hay (t > 0)
bool		solve_quadratic(t_quadratic *quad);
t_rgb		trace_ray(t_ray *ray, t_data *scene);
//cambia el colo de un pixel X, teniendo en cuenta el brillo de la luz ambiental.
t_rgb		apply_ambient_light(t_rgb obj_color, t_aLight *ambient_light);
//renderiza toda la escena y devuelve un array bidimensional de pixels
t_rgb		**render(t_data *scene, int x, int y);
//true si el rayo intesecciona con una esfera.
bool		intersect_sphere(t_ray *ray, t_obj *sphere, float *t);
t_rgb		**init_image_(int width, int height);

#endif
