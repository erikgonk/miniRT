/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:25:17 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/13 12:47:01 by shurtado         ###   ########.fr       */
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

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct	s_viewport {
	t_v3	origin;      // Centro del viewport en el espacio 3D
	t_v3	horizontal;  // Vector que define el ancho del viewport
	t_v3	vertical;    // Vector que define la altura del viewport
	t_v3	lower_left;	// Esquina inferior izquierda del viewport
	float	viewport_width;
	float	viewport_height;
}	t_vp; //Viewport

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
uint32_t	trace_ray(t_ray ray, t_obj *objects, t_aLight *light, t_sLight *sLight);

//cambia el colo de un pixel, teniendo en cuenta el brillo de la luz ambiental.
t_rgb		apply_ambient_light(t_rgb obj_color, t_aLight *ambient_light);

//renderiza toda la escena y devuelve un array bidimensional de pixels
uint32_t	**render(t_data *scene, int x, int y);

//true si el rayo intesecciona con x objeto
bool		intersect_sphere(t_ray ray, t_obj *sphere, float *t);
bool		intersect_cylinder(t_ray ray, t_obj *cylinder, float *t);
bool		intersect_plane(t_ray ray, t_obj *plane, float *t);

uint32_t	**init_image_(void);
void		free_render(t_vp *vp, t_ray **rays);

t_rgb		render_phong(t_ray ray, t_obj *obj, t_sLight *lights);


#endif
