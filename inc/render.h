/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:25:17 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/15 23:39:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
// short alias for window size
# define WH WINDOW_WIDTH
# define HG WINDOW_HEIGHT

# define PPLANEDISTANCE 1.0f
# define BLACK 0xFF000000

typedef unsigned char	t_uchar;
# define EPSILON 1e-6
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_frame
{
	t_v3	forward;
	t_v3	right;
	t_v3	up;
}	t_frame;

typedef struct s_viewport
{
	t_v3	origin;
	t_v3	horizontal;
	t_v3	vertical;
	t_v3	lower_left;
	float	viewport_width;
	float	viewport_height;
}	t_vp;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
	t_v3	normal;
	t_v3	point;
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

// Return int color without alpha
uint32_t	get_colour(t_rgb color);

//Calcula el pano de proyeccion, a traves del fov.
t_vp		*init_viewport(t_cam *camera, int width, int height);

//establece el origen y destino de un array bidimensional de rayos
t_ray		**init_rays(t_cam *camera, t_vp *vp);

//Inicia la estructura de datos para una ecuacion cuadratica
void		init_quadratic(t_quadratic *quad, float a, float b, float c);

//Resuelve una ecuacion cuadratica,
//para almacenar en t1 y t2 las intersecciones si las hay (t > 0)
bool		solve_quadratic(t_quadratic *quad);

//lanza un rayo, devuelve el color del objeto, o el de fondo si no choca.
uint32_t	trace_ray(t_ray ray, t_data *scene);

//cambia el colo de un pixel, teniendo en cuenta el brillo de la luz ambiental.
t_rgb		apply_ambient_light(t_rgb obj_color, t_aLight *ambient_light);

//renderiza toda la escena y devuelve un array bidimensional de pixels
uint32_t	**render(t_data *scene, int x, int y);

//true si el rayo intesecciona con x objeto
bool		hit_sp(t_ray *ray, t_obj *sphere, float *t);
bool		hit_cy(t_ray *ray, t_obj *cylinder, float *t);
bool		hit_pl(t_ray *ray, t_obj *plane, float *t);

uint32_t	**init_image_(void);
void		free_render(t_vp *vp, t_ray **rays);

t_rgb		phong(t_data *scene, t_ray *ray, t_obj *obj);
float		vlength(t_v3 v);

#endif
