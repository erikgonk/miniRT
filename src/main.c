/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/08 14:07:42 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	last_exit(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	update_render(void *param)
{
	t_data				*data;
	uint32_t			**new_img;
	uint32_t			**avrg;
	t_ll				time;

	time = current_timestamp();
	data = (t_data *)param;
	data->x = data->mlx->width;
	data->y = data->mlx->height;
	data->god = true;
	mlx_resize_image(data->img, data->x, data->y);
	if (!data->img_last)
		data->img_last = render(data, data->x, data->y);
	if (!data->img->enabled)
		data->img->enabled = true;
	new_img = render(data, data->x, data->y);
	avrg = average_samples(data, (uint32_t **)data->img_last, new_img);
	fill_image(data, (uint32_t *)data->img->pixels, avrg);
	free_image_all(data, avrg);
	mlx_image_to_window(data->mlx, data->img, 0 ,0);
	time = current_timestamp() - time;
	printf("%lld\n", time /= 100);
}


void	init_cube(t_data *data)
{
	t_obj	*cube;

	cube = malloc(sizeof(t_obj));
	if (!cube)
		return ;
	cube->type = CU;
	cube->pos = (t_v3) {-100.0,5.0,-50.0};
	cube->axis = (t_v3) {0.2,0.3,0.1};
	cube->axis = normalize(cube->axis);
	cube->cube_size = (t_v3) {20, 20, 20};
	cube->height = 30;
	cube->rgb = (t_rgb) {50,128,200};
	cube->material.m_type = MR;
	cube->next = NULL;
	objadd_back(&data->obj, cube);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	srand((unsigned int) mlx_get_time());
	init_data(&data);
	validate_args_and_open(ac, av, &fd);
	parse(data, fd);
	close(fd);
	init_cube(data); // delete
	init_all(data);
	data->img_last = NULL;
	// render_to_mlx(data);
	mlx_loop_hook(data->mlx, update_render, data);
	mlx_resize_hook(data->mlx, &resise_w, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
}
