/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:51:49 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 11:27:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_ambient_light(t_data *data)
{
	char	br[80];
	mlx_image_t *img[2];

	sprintf(br, "Brightness: %.2f : Press + or - to change.", data->a_light->br);
	img[0] = mlx_put_string(data->mlx, "Ambient Light: Press arrows to move menu.", CON_X, CON_Y);
	img[1] = mlx_put_string(data->mlx, br, CON_X, CON_Y + 25);
	ft_lstadd_back(&data->strlist, ft_lstnew(img[0]));
	ft_lstadd_back(&data->strlist, ft_lstnew(img[1]));

}

void	print_camera(t_data *data)
{
		char		pos[80];
		char		fov[80];
		char		axis[80];
		mlx_image_t *img[4];

	if (data)
	{
		sprintf(pos, "Position: x:%.2f y:%.2f z:%.2f", data->cam->pos.x, data->cam->pos.y, data->cam->pos.z);
		sprintf(axis, "Axis: x:%.2f y:%.2f z:%.2f", data->cam->axis.x, data->cam->axis.y, data->cam->axis.z);
		sprintf(fov, "Fov: %d", data->cam->fov);
		img[0] = mlx_put_string(data->mlx, "Camera: Press arrows to move menu, press enter to move cam.", CON_X, CON_Y);
		img[1] = mlx_put_string(data->mlx, pos, CON_X, CON_Y + 25);
		img[2] = mlx_put_string(data->mlx, axis, CON_X, CON_Y + 50);
		img[3] = mlx_put_string(data->mlx, fov, CON_X, CON_Y + 75);
		ft_lstadd_back(&data->strlist, ft_lstnew(img[0]));
		ft_lstadd_back(&data->strlist, ft_lstnew(img[1]));
		ft_lstadd_back(&data->strlist, ft_lstnew(img[2]));
		ft_lstadd_back(&data->strlist, ft_lstnew(img[3]));
	}
}

void	print_spot_lights(t_data *data)
{
	char		pos[80];
	char		br[80];
	char		color[80];
	char		id[80];
	t_slight	*s_light;
	mlx_image_t	*img[5];
	int			var;
	int			num;

	num = 0;
	var = 0;
	if (data && data->s_light)
	{
		s_light = data->s_light;
		while (s_light)
		{
			sprintf(pos, "Position: x:%.2f y:%.2f z:%.2f", s_light->pos.x, s_light->pos.y, s_light->pos.z);
			sprintf(br, "Brightness: %.2f", s_light->br);
			sprintf(color, "Color: r:%d g:%d b:%d", s_light->rgb.r, s_light->rgb.g, s_light->rgb.b);
			sprintf(id, "Spot number in list: %d press arrows to change spot light", num);

			img[0] = mlx_put_string(data->mlx, "Spot Light: Press enter to select spot light", CON_X, CON_Y + var);
			img[1] = mlx_put_string(data->mlx, pos, CON_X, CON_Y + 25 + var);
			img[2] = mlx_put_string(data->mlx, br, CON_X, CON_Y + 50 + var);
			img[3] = mlx_put_string(data->mlx, color, CON_X, CON_Y + 75) + var;
			img[4] = mlx_put_string(data->mlx, id, CON_X, CON_Y + 100) + var;

			ft_lstadd_back(&data->strlist, ft_lstnew(img[0]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[1]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[2]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[3]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[4]));

			var += 100;
			s_light = s_light->next;
			break ; //rotar aqui entre las luces y quitar break;
		}
	}
}

void	print_objects(t_data *data)
{
	char		pos[80];
	char		axis[80];
	char		color[80];
	char		id[80];
	char		type[80];
	t_obj		*obj;
	mlx_image_t	*img[5];
	int			var;
	int			num;

	num = 0;
	var = 0;
	if (data && data->obj)
	{
		obj = data->obj;
		while (obj)
		{
			sprintf(pos, "Position: x:%.2f y:%.2f z:%.2f", obj->pos.x, obj->pos.y, obj->pos.z);
			sprintf(axis, "Axis: x:%.2f y:%.2f z:%.2f", data->cam->axis.x, data->cam->axis.y, data->cam->axis.z);
			sprintf(color, "Color: r:%d g:%d b:%d", obj->rgb.r, obj->rgb.g, obj->rgb.b);
			if (obj->type == CY)
				sprintf(type, "Object type: Cylinder");
			else if (obj->type == CO)
				sprintf(type, "Object type: Cone");
			else if (obj->type == CU)
				sprintf(type, "Object type: Cube");
			else if (obj->type == SP)
				sprintf(type, "Object type: sphere");
			else if (obj->type == PL)
				sprintf(type, "Object type: plane");
			sprintf(id, "Object number in list: %d, press arrows to change obj", num);

			img[0] = mlx_put_string(data->mlx, "Objects: Press enter to select object.", CON_X, CON_Y + var);
			img[1] = mlx_put_string(data->mlx, pos, CON_X, CON_Y + 25 + var);
			img[2] = mlx_put_string(data->mlx, axis, CON_X, CON_Y + 50 + var);
			img[3] = mlx_put_string(data->mlx, color, CON_X, CON_Y + 75) + var;
			img[4] = mlx_put_string(data->mlx, id, CON_X, CON_Y + 100) + var;
			img[5] = mlx_put_string(data->mlx, type, CON_X, CON_Y + 125) + var;

			ft_lstadd_back(&data->strlist, ft_lstnew(img[0]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[1]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[2]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[3]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[4]));
			ft_lstadd_back(&data->strlist, ft_lstnew(img[5]));


			var += 100;
			obj = obj->next;
			break ; //rotar aqui entre las luces y quitar break;
		}
	}
}

// Función principal que llama a las subfunciones
void	print_t_data(t_data *data)
{
	if (data == NULL)
	{
		printf("t_data is NULL\n");
		return ;
	}
	print_ambient_light(data);
	print_camera(data);
	print_spot_lights(data->s_light);
	print_objects(data->obj);
}
