/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_icons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:43:07 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 18:07:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	count_arrows(t_data *data)
{
	t_obj	*obj;

	if (data->console.last_type == CAM)
		return (9);
	else if (data->console.last_type == ALIGHT)
		return (1);
	else if (data->console.last_type == SLIGHT)
		return (5);
	else if (data->console.last_type == OBJ)
	{
		obj = data->console.last_item;
		if (obj->type == PL)
			return (8);
		else if (obj->type == SP)
			return (5);
		else if (obj->type == CY || obj->type == CO)
			return (10);
		else if (obj->type == CU)
			return (11);
	}
	return (0);
}

int	count_labels(t_data *data)
{
	t_obj	*obj;

	obj = data->console.last_item;
	if (data->console.last_type == CAM)
		return (11);
	else if (data->console.last_type == ALIGHT)
		return (3);
	else if (data->console.last_type == SLIGHT)
		return (7);
	else if (data->console.last_type == OBJ)
	{
		if (obj->type == PL)
			return (9);
		else if (obj->type == SP)
			return (7);
		else if (obj->type == CY || obj->type == CO)
			return (12);
		else if (obj->type == CU)
			return (13);
	}
	return (0);
}

void	put_imgarrows(t_data *data)
{
	mlx_image_t	**icons;
	int			margin;
	int			i;
	int			count;

	margin = BG_WITH - 100;
	icons = data->console.icons;
	i = -1;
	count = count_arrows(data);
	while (++i < count)
	{
		if (i % 4 == 3)
			continue ;
		mlx_image_to_window(data->mlx, icons[2], data->x - \
							margin, 98 + (30 * i));
	}
	i = -1;
	while (++i < count)
	{
		if (i % 4 == 3)
			continue ;
		mlx_image_to_window(data->mlx, icons[3], data->x - \
							icons[1]->width - 25, 98 + (30 * i));
	}
}

void	set_resize_buton_images(t_data *data, t_img_btn *img_btn)
{
	mlx_image_t	**icons;
	int			i;

	icons = data->console.icons;
	img_btn->iconst[0] = mlx_load_png("./assets/consol/arrow_b_left.png");
	img_btn->iconst[1] = mlx_load_png("./assets/consol/arrow_b_right.png");
	img_btn->iconst[2] = mlx_load_png("./assets/consol/arrow_s_left_blue.png");
	img_btn->iconst[3] = mlx_load_png("./assets/consol/arrow_s_right_blue.png");
	i = -1;
	while (++i < 4)
		icons[i] = mlx_texture_to_image(data->mlx, img_btn->iconst[i]);
	mlx_resize_image(icons[0], icons[0]->width / 1.5, icons[0]->height / 1.5);
	mlx_resize_image(icons[1], icons[1]->width / 1.5, icons[1]->height / 1.5);
	mlx_image_to_window(data->mlx, icons[0], data->x - BG_WITH + 30, 0);
	mlx_image_to_window(data->mlx, icons[1], data->x - icons[1]->width - 30, 0);
	mlx_resize_image(icons[2], icons[2]->width / 3, icons[2]->height / 3);
	mlx_resize_image(icons[3], icons[3]->width / 3, icons[3]->height / 3);
}

void	fill_image_list(t_data *data, t_img_btn *img_btn)
{
	int	i;
	int	count;

	count = count_labels(data);
	i = -1;
	while (++i < count)
	{
		mlx_set_instance_depth(&img_btn->labels[i]->instances[0], 4);
		ft_lstadd_back(&data->console.btn_list, ft_lstnew(img_btn->labels[i]));
	}
	i = -1;
	while (++i < 4)
	{
		ft_lstadd_back(&data->console.btn_list, \
				ft_lstnew(data->console.icons[i]));
		mlx_set_instance_depth(&data->console.icons[i]->instances[0], 3);
	}
}
