/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:14 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/09 19:50:59 by shurtado         ###   ########.fr       */
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

typedef struct s_aLight
{
	float			br; // brightness
	t_rgb			rgb;
}					t_aLight;

typedef struct s_sLight
{
	t_v3			pos;
	float			br; // brightness
	t_rgb			rgb;
	struct s_sLight	*next;
}					t_sLight;

typedef struct s_obj
{
	uint32_t		color;
	int				i;			// just to use it on the parser
	int				type;		// in case I want to separate the parser and the exec
	t_v3			pos;		// sp pl cy
	t_v3			axis;		// pl cy | orientation
	t_rgb			rgb;		// sp pl cy
	float			size;		// sp radius | cy diameter
	float			height;		// cy
	struct s_obj	*next;
}					t_obj;

typedef struct s_data
{
	t_aLight		*aLight;
	t_cam			*cam;
	t_sLight		*sLight;
	t_obj			*obj;
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_data;

#endif
