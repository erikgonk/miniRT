/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 15:58:24 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define ALIGHTPLUS 0.01f
# define ALIGHTMAX	1.0f
# define ALIGHTMIN	0.0f

# define CAMPLUS 5
# define CAMAXISP 0.05f
# define CAMAXISMIN -1.00f
# define CAMAXISMAX 1.00f

# define SPOTPLUS 5
# define SLIGHTPLUS 0.01f
# define SLIGHTMAX	1.0f
# define SLIGHTMIN	0.0f

# define OBJPLUS 5
# define OBJAXISP 0.01f
# define OBJAXISMIN -1.00f
# define OBJAXISMAX 1.00f

# define ALIGHT_M 0
# define CAM_M 1
# define OBJ_M 2
# define SPOT_M 3

# define BG_WITH 300

void		run_console(t_data *data);
void		del_image(void *content);
mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y);
mlx_image_t	*create_menu_background(t_data *data);

#endif
