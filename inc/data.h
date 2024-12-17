/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 17:46:19 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "libvct.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

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
	t_v3				pos;
	float				br;
	t_rgb				rgb;
	struct s_light	*next;
}					t_slight;

typedef struct s_obj
{
	uint32_t		color;
	int				i;
	int				type;
	t_v3			pos;
	t_v3			axis;
	t_rgb			rgb;
	float			size;
	float			height;
	struct s_obj	*next;
}					t_obj;

typedef struct s_data
{
	t_alight		*a_light;
	t_cam			*cam;
	t_slight		*s_light;
	t_obj			*obj;
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_data;

#endif
