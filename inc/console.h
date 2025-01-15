/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 05:26:02 by shurtado         ###   ########.fr       */
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

# define CON_X 145
# define CON_Y 32
# define LINE 25

// run_console
void	print_alight_menu(t_data *data);
void	print_cam_menu(t_data *data);
void	print_spot_menu(t_data *data);
void	print_obj_menu(t_data *data);
void	run_console(t_data *data);

// camera_menu
void	adjust_camera_pos(keys_t key, t_data *data, double *posq);
void	adjust_camera_axis(keys_t key, t_data *data, double *axisq);
void	manage_cam(keys_t key, t_data *data);

// obj_menu
void	adjust_obj_position(keys_t key, t_obj *obj, double *posq);
void	adjust_obj_axis(keys_t key, t_obj *obj, double *axisq);
void	manage_obj(keys_t key, t_data *data);

// slihgt_menu
void	adjust_spot_brightness(keys_t key, t_data *data);
void	adjust_spot_position(keys_t key, t_data *data);
void	manage_spot(keys_t key, t_data *data);

// submenu
void	manage_alight(keys_t key, t_data *data);
void	manage_submenu(keys_t key, int option, t_data *data);

#endif
