/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/09 18:35:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define ALIGHTPLUS 0.01f
# define ALIGHTMAX	1.0f
# define ALIGHTMIN	0.0f

# define CAMPLUS 5
# define SPOTPLUS 5
# define OBJPLUS 5

void	run_console(t_data *data, keys_t key);
void	manage_submenu(keys_t key, int option, t_data *data);

void	print_alight_menu(t_data *data);
void	print_cam_menu(t_data *data);
void	print_spot_menu(t_data *data);
void	print_obj_menu(t_data *data);

#endif