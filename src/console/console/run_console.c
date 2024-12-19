/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_console.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:43:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_alight_menu(t_data *data)
{
	printf("\033[2J\033[H");
	print_ambient_light(data->a_light);
	printf("\n");
	printf("\033[30m\033[47mAmbient Light\033[0m");
}

void	print_cam_menu(t_data *data)
{
	printf("\033[2J\033[H");
	print_camera(data->cam);
	printf("\n");
	printf("\033[30m\033[47mCamera\033[0m");
}

void	print_spot_menu(t_data *data)
{
	printf("\033[2J\033[H");
	print_spot_lights(data->s_light);
	printf("\n");
	printf("\033[30m\033[47mSpot Lights\033[0m");
}

void	print_obj_menu(t_data *data)
{
	printf("\033[2J\033[H");
	print_objects(data->obj);
	printf("\n");
	printf("\033[30m\033[47mObjects\033[0m");
}

void	run_console(t_data *data, keys_t key)
{
	static unsigned int	option;
	int					mode;

	if (key == MLX_KEY_0)
	{
		print_alight_menu(data);
		return ;
	}
	else if (key == MLX_KEY_Q && option)
		option--;
	else if (key == MLX_KEY_W && option < 3)
		option++;
	mode = key == MLX_KEY_W || key == MLX_KEY_Q;
	if (option == 0 && mode)
		print_alight_menu(data);
	else if (mode && option == 1)
		print_cam_menu(data);
	else if (mode && option == 2)
		print_spot_menu(data);
	else if (mode && option == 3)
		print_obj_menu(data);
	else if (!mode)
		manage_submenu(key, option, data);
}
