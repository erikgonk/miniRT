/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 15:35:30 by shurtado         ###   ########.fr       */
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

void calculate_bounds(t_obj	*obj)
{
	t_v3 half_size;

	// Calcula el vector de la mitad del tamaño
	half_size.x = obj->cube.size.x * 0.5;
	half_size.y = obj->cube.size.y * 0.5;
	half_size.z = obj->cube.size.z * 0.5;

	// Calcula los valores mínimos y máximos
	obj->cube.xmin = obj->pos.x - half_size.x;
	obj->cube.xmax = obj->pos.x + half_size.x;

	obj->cube.ymin = obj->pos.y - half_size.y;
	obj->cube.ymax = obj->pos.y + half_size.y;

	obj->cube.zmin = obj->pos.z - half_size.z;
	obj->cube.zmax = obj->pos.z + half_size.z;
}

void	init_cube(t_data *data)
{
	t_obj	*cube;

	cube = malloc(sizeof(t_obj));
	if (!cube)
		return ;
	cube->type = CU;
	cube->pos = (t_v3) {-75.0,5.0,-50.0};
	cube->axis = (t_v3) {-0.5,0.3,0.7};
	cube->axis = normalize(cube->axis);
	cube->cube.size.x = 50;
	cube->cube.size.y = 60;
	cube->cube.size.z = 20;
	cube->height = 30;
	cube->rgb = (t_rgb) {50,128,200};
	cube->material.m_type = -1;
	calculate_bounds(cube);
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
