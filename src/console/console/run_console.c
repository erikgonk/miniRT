/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_console.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 11:34:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static mlx_t *g_mlx = NULL;

void	del_image(void *content)
{
	mlx_image_t	*image;

	if (content && g_mlx)
	{
		image = (mlx_image_t *)content;
		mlx_delete_image(g_mlx, image);
	}
}

void	run_console(t_data *data)
{
	static unsigned int	option;
	int					mode;
	mlx_image_t			*console;

	if (!g_mlx)
		g_mlx = data->mlx;
	if (data->strlist)
		ft_lstclear(&data->strlist, del_image);
	data->strlist = NULL;
	console = mlx_put_string(data->mlx, "Console: ", 50, 30);
	ft_lstadd_back(&data->strlist, ft_lstnew(console));
	if (data->last_key == MLX_KEY_C)
	{
		print_ambient_light(data);
		return ;
	}
	else if (data->last_key == MLX_KEY_LEFT && option)
		option--;
	else if (data->last_key == MLX_KEY_RIGHT && option < 3)
		option++;
	mode = data->last_key == MLX_KEY_LEFT || data->last_key == MLX_KEY_RIGHT;
	if (mode && option == 0)
		print_ambient_light(data);
	else if (mode && option == 1)
		print_camera(data);
	else if (mode && option == 2)
		print_spot_lights(data);
	else if (mode && option == 3)
		print_objects(data);
	else if (!mode)
		manage_submenu(data->last_key, option, data);
}
