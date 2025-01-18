/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:03 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/18 18:18:18 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"

//		mlx
void	fill_image(t_data *data, uint32_t *pixels, uint32_t **img_rgb);
bool	press_keyhook_normi(t_data *data, mlx_key_data_t keydata, bool mode);
void	press_keyhook(t_data *data, mlx_key_data_t keydata);
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	resise_w(int32_t width, int32_t height, void *param);

//		mlx_utils
void	swap_mgod(t_data *data);
void	set_last(t_data *data);
void	swap_flag_mlx(t_data *data);

#endif
