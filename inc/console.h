/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/09 18:56:57 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define ALIGHTPLUS 0.01f
# define ALIGHTMAX	1.0f
# define ALIGHTMIN	0.0f

# define CAMPLUS 5
# define CAMAXISP 0.01f
# define CAMAXISMIN -1.00f
# define CAMAXISMAX 1.00f

# define SPOTPLUS 5
# define SPOTAXISPLUS 0.01f
# define SPOTAXISMIN -1.00f
# define SPOTAXISMAX 1.00f

# define OBJPLUS 5
# define OBJAXISPLUS 0.01f
# define OBJAXISMIN -1.00f
# define OBJAXISMAX 1.00f

void	run_console(t_data *data, keys_t key);
void	manage_submenu(keys_t key, int option, t_data *data);

void	print_alight_menu(t_data *data);
void	print_cam_menu(t_data *data);
void	print_spot_menu(t_data *data);
void	print_obj_menu(t_data *data);

#endif