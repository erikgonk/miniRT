/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/07 16:18:04 by shurtado         ###   ########.fr       */
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

void	calculate_bounds(t_obj *obj)
{
	t_v3	half_size;
	t_v3	u, v, w;
	t_v3	corners[8];
	int		i;

	// Calcula la mitad del tamaño
	half_size.x = obj->cube.size.x * 0.5;
	half_size.y = obj->cube.size.y * 0.5;
	half_size.z = obj->cube.size.z * 0.5;

	// Calcula los ejes locales del cubo basados en su axis
	w = normalize(obj->axis); // Eje principal
	u = normalize(cross((t_v3){0, 1, 0}, w)); // Eje ortogonal
	if (fabs(dot(u, w)) > EPSILON) // Garantiza ortogonalidad
		u = normalize(cross((t_v3){1, 0, 0}, w));
	v = cross(w, u); // Tercer eje ortogonal

	// Calcula las 8 esquinas del cubo en el espacio global
	corners[0] = vadd(obj->pos, vadd(vadd(vmul(half_size.x, u), vmul(half_size.y, v)), vmul(half_size.z, w)));
	corners[1] = vadd(obj->pos, vadd(vadd(vmul(-half_size.x, u), vmul(half_size.y, v)), vmul(half_size.z, w)));
	corners[2] = vadd(obj->pos, vadd(vadd(vmul(half_size.x, u), vmul(-half_size.y, v)), vmul(half_size.z, w)));
	corners[3] = vadd(obj->pos, vadd(vadd(vmul(-half_size.x, u), vmul(-half_size.y, v)), vmul(half_size.z, w)));
	corners[4] = vadd(obj->pos, vadd(vadd(vmul(half_size.x, u), vmul(half_size.y, v)), vmul(-half_size.z, w)));
	corners[5] = vadd(obj->pos, vadd(vadd(vmul(-half_size.x, u), vmul(half_size.y, v)), vmul(-half_size.z, w)));
	corners[6] = vadd(obj->pos, vadd(vadd(vmul(half_size.x, u), vmul(-half_size.y, v)), vmul(-half_size.z, w)));
	corners[7] = vadd(obj->pos, vadd(vadd(vmul(-half_size.x, u), vmul(-half_size.y, v)), vmul(-half_size.z, w)));

	// Inicializa los límites con la primera esquina
	obj->cube.xmin = corners[0].x;
	obj->cube.xmax = corners[0].x;
	obj->cube.ymin = corners[0].y;
	obj->cube.ymax = corners[0].y;
	obj->cube.zmin = corners[0].z;
	obj->cube.zmax = corners[0].z;

	// Ajusta los límites basado en todas las esquinas
	i = 1;
	while (i < 8)
	{
		if (corners[i].x < obj->cube.xmin)
			obj->cube.xmin = corners[i].x;
		if (corners[i].x > obj->cube.xmax)
			obj->cube.xmax = corners[i].x;
		if (corners[i].y < obj->cube.ymin)
			obj->cube.ymin = corners[i].y;
		if (corners[i].y > obj->cube.ymax)
			obj->cube.ymax = corners[i].y;
		if (corners[i].z < obj->cube.zmin)
			obj->cube.zmin = corners[i].z;
		if (corners[i].z > obj->cube.zmax)
			obj->cube.zmax = corners[i].z;
		i++;
	}
}

void	init_cube(t_data *data)
{
	t_obj	*cube;

	cube = malloc(sizeof(t_obj));
	if (!cube)
		return ;
	cube->type = CU;
	cube->pos = (t_v3) {-75.0,5.0,-50.0};
	cube->axis = (t_v3) {-1,0.3,0.7};
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
