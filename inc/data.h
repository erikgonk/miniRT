/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:14 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/10 16:23:04 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include "libvct.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_frame
{
	t_v3				forward;
	t_v3				right;
	t_v3				up;
}						t_frame;

typedef struct s_cap
{
	double				radius;
	t_v3				cap_center;
	t_v3				cap_normal;
}	t_cap;

typedef struct s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}					t_rgb;

typedef struct s_cam
{
	t_v3				pos;
	int					fov;
	t_v3				axis; // orientation
	double				focus_dist;
	double				aperture;
	double				pi2;
	t_v3				u;
	t_v3				v;
	t_frame				frame;
}					t_cam;

typedef struct s_a_light
{
	double				br; // brightness
	t_rgb				rgb;
}					t_alight;

typedef struct s_light
{
	double				br;
	t_v3				pos;
	t_rgb				rgb;
	t_rgb				rgb_inty;
	struct s_light		*next;
}					t_slight;

typedef struct s_material
{
	int					m_type;
	double				reflectivity;
	double				transmittance;
	double				roughness;
	double				absorption;
	double				specularity;
	int					shininess;
	void				*get_normal;
	t_rgb				rgb_checker;
	double				board_scale;
	double				emision;
	double				self_emision;
	mlx_texture_t		*texture;
}				t_material;

typedef struct s_calcs
{
	double				radius; // sp cy
	double				radius2; // sp cy
	t_v3				i_axis; // cy
	t_v3				oc_par; // cy
	t_v3				oc_perp; // cy
	t_v3				oc_perp2;
	double				c; // cy
	double				half_height;
	double				hh_e_sum;
	double				hh_e_res;
	t_cap				upper_cap; // cy
	t_cap				btm_cap; // cy
//		para refract
	double				etai;
	double				etat;
	double				eta;
	double				eta_reverse;
	double				eta2;
	double				eta_reverse2;
//		para fresnel
	double				etai_etat;
	double				etai_etat_reverse;
//		caps
	t_v3				caps_normal;
//		cone
	double				half_angle;
	double				cos_half;
	double				k;
	double				numerator;
	t_v3				half_size;
	t_v3				oc;
	double				dot_oc_axis;
}	t_calcs;


typedef struct s_obj
{
	int					i;
	int					type;
	uint32_t			color;
	t_v3				pos;
	t_v3				axis;
	t_rgb				rgb;
	t_rgb				a_rgb;
	double				size;
	t_v3				cube_size;
	t_v3				axis_x;
	t_v3				axis_y;
	t_v3				axis_z;
	double				height;
	t_calcs				calcs;
	t_material			material;
	unsigned int		parent;
	t_v3				right;
	t_v3				up;
	int					face;
	struct s_obj		*next;
}					t_obj;

typedef struct s_data
{
	t_alight			*a_light;
	t_cam				*cam;
	t_slight			*s_light;
	t_obj				*obj;
	int					aa; // antialising (check if is useful)
	int					bl; // blur
	mlx_t				*mlx;
	mlx_image_t			*img;
	bool				trace_flag;
	pthread_mutex_t		*m_trace;
	uint32_t			**img_last;
	int					x;
	int					y;
	pthread_mutex_t		*m_god;
	bool				god;

}					t_data;

#endif
