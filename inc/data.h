/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/29 10:41:25 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "libvct.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_cap
{
	float	radius;
	t_v3	cap_center;
	t_v3	cap_normal;
}	t_cap;

typedef struct s_rgb
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
}					t_rgb;

typedef struct s_cam
{
	t_v3			pos;
	int				fov;
	t_v3			axis; // orientation
}					t_cam;

typedef struct s_a_light
{
	float			br; // brightness
	t_rgb			rgb;
}					t_alight;

typedef struct s_light
{
	float				br;
	t_v3				pos;
	t_rgb				rgb;
	t_rgb				rgb_inty;
	struct s_light		*next;
}					t_slight;

typedef struct s_material
{
	int				m_type;
	float			reflectivity;
	float			transmittance;
	float			roughness;
	float			absorption;
	float			specularity;
	void			*get_normal;
	t_rgb			rgb_checker;
	float			board_scale;
}				t_material;

typedef struct s_calcs
{
	float			radius; // sp cy
	float			radius2; // sp cy
	float			numerator; // pl
	t_v3			i_axis; // cy
	t_v3			oc_par; // cy
	t_v3			oc_perp; // cy
	t_v3			oc_perp2;
	float			c; // cy
	float			half_height;
	t_cap			upper_cap; // cy
	t_cap			btm_cap; // cy
}	t_calcs;

typedef struct s_obj
{
	int				i;
	int				type;
	uint32_t		color;
	t_v3			pos;
	t_v3			axis;
	t_rgb			rgb;
	t_rgb			a_rgb;
	float			size;
	float			height;
	t_calcs			calcs;
	t_material		material;
	struct s_obj	*next;
}					t_obj;

typedef struct s_data
{
	t_alight		*a_light;
	t_cam			*cam;
	t_slight		*s_light;
	t_obj			*obj;
	int				aa; // antialising (check if is useful)
	int				bl; // blur
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_data;

#endif
