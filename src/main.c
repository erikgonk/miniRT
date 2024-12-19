/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 12:06:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	validate_args_and_open(int ac, char **av, int *fd)
{
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
		exit(er("error: fd failed", NULL));
}

void	init_obj(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		obj->a_rgb = apply_ambient_light(obj->rgb, data->a_light);
		if (obj->type == PL)
		{
			obj->numerator = dot(vsub(obj->pos, data->cam->pos), obj->axis);
			obj->i_axis = vmul(-1.0f, obj->axis);
		}
		else
		{
			obj->radius = obj->size * 0.5f;
			obj->radius2 = obj->radius * obj->radius;
			obj->axis = normalize(obj->axis);
			obj->oc_par = vmul(dot(vsub(data->cam->pos, obj->pos), obj->axis), obj->axis);
			obj->oc_perp = vsub(vsub(data->cam->pos, obj->pos), obj->oc_par);
			obj->c = dot(obj->oc_perp, obj->oc_perp) - obj->radius2;
			obj->half_height = obj->height * 0.5f;
			obj->upper_cap.cap_center = vadd(obj->pos, vmul(obj->half_height, obj->axis));
			obj->btm_cap.cap_center = vsub(obj->pos, vmul(obj->half_height, obj->axis));
			obj->upper_cap.radius = obj->size * 0.5f;
			obj->btm_cap.radius = obj->size * 0.5f;
			obj->upper_cap.cap_normal = obj->axis;
			obj->btm_cap.cap_normal = vmul(-1.0f, obj->axis);
		}
		obj = obj->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	init_data(&data);
	validate_args_and_open(ac, av, &fd);
	parse(data, av, fd);
	close(fd);
	init_all(data);
	render_to_mlx(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}
