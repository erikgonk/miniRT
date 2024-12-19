/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 15:36:37 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"

void			render_to_mlx(t_data *data);
void			fill_image(uint32_t *pixels, uint32_t **img_rgb);
void			my_keyhook(mlx_key_data_t keydata, void *param);

#endif