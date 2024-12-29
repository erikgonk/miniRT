/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:25:17 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 17:05:53 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"

# define PPLANEDISTANCE 1.0f
# define BLACK 0xFF000000
# define RGB_BLACK (t_rgb){1, 1, 1}

typedef unsigned char	t_uchar;
# define EPSILON 1e-6
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Materials
# define SOLID_S 12

// Color Weight
# define G_WEIGHT 0.7
# define L_WEIGHT 0.3

typedef struct s_frame
{
	t_v3				forward;
	t_v3				right;
	t_v3				up;
}						t_frame;

typedef struct s_viewport
{
	float				viewport_width;
	float				viewport_height;
	t_v3				origin;
	t_v3				horizontal;
	t_v3				vertical;
	t_v3				lower_left;
}						t_vp;

typedef struct s_ray
{
	t_v3				origin;
	t_v3				direction;
	t_v3				i_direction;
	t_v3				normal;
	t_v3				point;
}						t_ray;

typedef struct s_quadratic
{
	float				a;
	float				b;
	float				c;
	float				discriminant;
	float				t1;
	float				t2;
}						t_quadratic;

//		calcs
float					vlength(t_v3 v);
t_obj					*find_closest_object(t_ray *ray, t_obj *objs,
							float *t_min);
uint32_t				trace_ray(t_ray ray, t_data *data);

//		quadratic
void					init_quadratic(t_quadratic *quad, float a, float b,
							float c);
bool					solve_quadratic(t_quadratic *quad);

//		color
uint32_t				get_acolour(t_uchar alpha, t_uchar r, t_uchar g,
							t_uchar b);
uint32_t				get_colour(t_rgb color);

//		extras
t_rgb					checkerboard_color(t_obj *obj, t_v3 point);

//		init_general
void					init_all(t_data *data);
void					init_data(t_data **data);

//		init_image
void					init_mlx(t_data *data);
uint32_t				**init_image_(void);

//		init_obj
void					init_obj(t_data *data);
void					init_obj_normi(t_data *data, t_obj *obj);
void					init_light(t_data *data);

//		init_rays
void					init_single_ray(t_ray *ray, t_vp *vp, t_cam *camera,
							float *uv);
t_ray					*init_ray_row(t_cam *camera, t_vp *vp, int y);
t_ray					**init_rays(t_cam *camera, t_vp *vp);

//		init_materials
void					init_materials_mt_mr(t_obj *obj);
void					init_materials_render(t_data *data);

//		cylinder
bool					check_cap(t_ray *ray, t_cap cap, float *t);
bool					cy_caps(t_ray *ray, t_obj *cy, float *t);
void					set_cy_axis(t_quadratic *quad, t_obj *cy, t_ray *ray,
							t_v3 *ray_origin);
float					set_ray_t(t_ray *ray, t_obj *cy, float *t,
							float quadt1);
bool					hit_cy(t_ray *ray, t_obj *cy, float *t,
							t_v3 *ray_origin);

//		illumination
t_rgb					apply_ambient_light(t_rgb obj_color, t_alight *a_light);
void					difuse_light(t_rgb *color, t_slight *slight, t_obj *obj,
							float inty);
bool					data_shadow(t_data *data, t_ray *shadow_ray,
							float max_dist);
t_rgb					phong(t_data *data, t_ray *ray, t_obj *obj);

//		specular
void					specular_light(t_rgb *color, t_data *data, t_ray *ray);

//		intersections
bool					calc_quad_sphere(t_obj *sphere, t_ray ray,
							t_quadratic *quad);
bool					hit_sp(t_ray *ray, t_obj *sphere, float *t);
bool					hit_pl(t_ray *ray, t_obj *plane, float *t);

//		viewport
t_v3					calculate_up(t_v3 forward, t_v3 right);
t_v3					calculate_right(t_v3 forward);
t_vp					*init_viewport(t_cam *camera, int width, int height);

//		render
uint32_t				**render(t_data *data, int x, int y);

//		free
void					free_rays_all(t_ray **rays);
void					free_render(t_vp *vp, t_ray **rays);
void					free_image_all(uint32_t **image);
void					free_data(t_data *data);
void					free_rays(t_ray **rays, int rows);

//		PATH_TRACER
t_rgb					path_trace(t_ray *ray, t_data *data, int depth, t_rgb last_color);
t_v3 random_in_hemisphere(t_v3 normal);
float	*generate_uv(int x, int y);
uint32_t	**average_samples(uint32_t **sample1, uint32_t **sample2);

#endif
