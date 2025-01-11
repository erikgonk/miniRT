/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:40:17 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/11 12:03:50 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "miniRT.h"

// debug_info
void		print_t_rgb(const char *label, t_rgb rgb);
void		print_t_v3(const char *label, t_v3 vec);

// print_items
void		print_ambient_light(t_alight *a_light);
void		print_camera(t_cam *cam);
void		print_spot_lights(t_slight *s_light);
void		print_objects(t_obj *obj);
void		print_t_data(t_data *data);
uint32_t	**render_without_threads(t_data *data, t_ray **rays,
				uint32_t **image);

// time
long long	current_timestamp(void);

#endif
