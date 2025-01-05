/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:03 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/05 11:53:51 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"

void			render_to_mlx(t_data *data);
void			fill_image(t_data *data, uint32_t *pixels, uint32_t **img_rgb);
void			my_keyhook(mlx_key_data_t keydata, void *param);
void			resise_w(int32_t width, int32_t height, void *param);

#endif
