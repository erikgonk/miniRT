/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 19:58:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	write_cam_labels(t_data *data, t_img_btn *img_btn)
{
	int		size;
	t_v3	pos;
	t_v3	axis;

	pos = data->cam->pos;
	axis = data->cam->axis;
	size = sizeof(img_btn->posx);
	snprintf(img_btn->posx, size, "x          %.2f", pos.x);
	snprintf(img_btn->posy, size, "y          %.2f", pos.y);
	snprintf(img_btn->posz, size, "z          %.2f", pos.z);
	snprintf(img_btn->axisx, size, "x           %.2f", axis.x);
	snprintf(img_btn->axisy, size, "y           %.2f", axis.y);
	snprintf(img_btn->axisz, size, "z           %.2f", axis.z);
	snprintf(img_btn->fov, size, "              %d", data->cam->fov);
}

void	set_cam_labels(t_data *data,t_img_btn *img_btn, int top)
{
	int			mleft;
	mlx_image_t	**labels;
	mlx_t		*mlx;

	mlx = data->mlx;
	labels = img_btn->labels;
	mleft = data->x - BG_WITH;
	write_cam_labels(data, img_btn);
	img_btn->labels[0] = put_str(mlx, "Camera", mleft + 120, top - 2);
	img_btn->labels[1] = put_str(mlx, "Pos", mleft + 155, top + 50);
	img_btn->labels[2] = put_str(mlx, img_btn->posx, mleft + 35, top + 80);
	img_btn->labels[3] = put_str(mlx, img_btn->posy, mleft + 35, top + 110);
	img_btn->labels[4] = put_str(mlx, img_btn->posz, mleft + 35, top + 140);
	img_btn->labels[5] = put_str(mlx, "Axis", mleft + 155, top + 170);
	img_btn->labels[6] = put_str(mlx, img_btn->axisx, mleft + 35, top + 200);
	img_btn->labels[7] = put_str(mlx, img_btn->axisy, mleft + 35, top + 230);
	img_btn->labels[8] = put_str(mlx, img_btn->axisz, mleft + 35, top + 260);
	img_btn->labels[9] = put_str(mlx, "FOV", mleft + 158, top + 290);
	img_btn->labels[10] = put_str(mlx, img_btn->fov, mleft + 25, top + 320);
}

void	set_labels(t_data *data, t_img_btn *img_btn, int top)
{
	if (data->console.last_type == CAM)
		set_cam_labels(data, img_btn, top);
//	else if (data->console.last_type == ALIGHT)
//		set_alight_labels(data, img_btn, top);
//	else if (data->console.last_type == SLIGHT)
//		set_slight_labels(data, img_btn, top);
//	else if (data->console.last_type == OBJ)
//		set_obj_labels(data, img_btn, top);

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

int	count_arrows(t_data *data)
{
	if (data->console.last_type == CAM)
		return (9);
	else if (data->console.last_type == ALIGHT)
		return (1);
	else if (data->console.last_type == SLIGHT)
		return (12);
	else if (data->console.last_type == OBJ)
		return (12);
}

void	put_imgarrows(t_data *data, int top)
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

int	count_labels(t_data *data)
{
	if (data->console.last_type == CAM)
		return (11);
	else if (data->console.last_type == ALIGHT)
		return (0);
	else if (data->console.last_type == SLIGHT)
		return (0);
	else if (data->console.last_type == OBJ)
		return (0);
}

void	fill_image_list(t_data *data, t_img_btn *img_btn)
{
	int	i;
	int	count;

	count = count_labels(data);
	i = -1;
	while (++i < count)
	{
		mlx_set_instance_depth(&img_btn->labels[i]->instances[0], 3);
		ft_lstadd_back(&data->console.btn_list, ft_lstnew(img_btn->labels[i]));
	}
	i = -1;
	while (++i < 4)
		ft_lstadd_back(&data->console.btn_list, \
				ft_lstnew(data->console.icons[i]));
}

void	set_all_buttons(t_data *data)
{
	t_img_btn	*img_btn;
	int			top;

	top = 25;
	img_btn = calloc(1, sizeof(t_img_btn));
	set_resize_buton_images(data, img_btn);
	put_imgarrows(data, top);
	set_labels(data, img_btn, top);
	fill_image_list(data, img_btn);
}

void	run_console(t_data *data)
{
	if (!g_mlx)
		g_mlx = data->mlx;
	if (data->console.btn_list)
	{
		ft_lstclear(&data->console.btn_list, del_image);
		data->console.btn_list = NULL;
	}
	set_background(data);
	set_all_buttons(data);
	init_console(data);
	data->last_render = FAST;
}
