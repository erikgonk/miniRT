/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 15:56:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	init_data(&data);
	validate_args_and_open(ac, av, &fd);
	parse(data, fd);
	close(fd);
	init_all(data);
	render_to_mlx(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}
