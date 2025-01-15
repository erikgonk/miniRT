/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_console.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 17:55:21 by shurtado         ###   ########.fr       */
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
		image = NULL;
	}
}

mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y)
{
	mlx_image_t	*button;

	button = NULL;
	if (!mlx || !label)
		return (NULL);
	button = mlx_put_string(mlx, label, x, y);
	if (!button)
	{
		fprintf(stderr, "Failed to create button with label: %s\n", label);
		return (NULL);
	}
	return (button);
}

mlx_image_t	*create_menu_background(t_data *data)
{
	mlx_image_t	*background;
	int			x;
	int			y;
	uint32_t	*pixels;

	background = NULL;
	if (!data || !data->mlx)
	{
		fprintf(stderr, "Invalid data or mlx instance\n");
		return (NULL);
	}
	background = mlx_new_image(data->mlx, BG_WITH, data->mlx->height);
	if (!background)
	{
		fprintf(stderr, "Failed to create menu background\n");
		return (NULL);
	}
	pixels = (uint32_t *)background->pixels;
	y = 0;
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < BG_WITH)
		{
			pixels[y * BG_WITH + x] = 0x80000000;
			x++;
		}
		y++;
	}
	return (background);
}

void	set_background(t_data * data)
{
	if (data->console.background)
	{
		mlx_delete_image(data->mlx, data->console.background);
		data->console.background = NULL;
	}
	if (!data->console.background)
		data->console.background = create_menu_background(data);
	if (!data->console.background)
	{
		fprintf(stderr, "Failed to create menu background\n");
		return ;
	}
	mlx_image_to_window(data->mlx, data->console.background, data->mlx->width - BG_WITH, 0);
	mlx_set_instance_depth(&data->console.background->instances[0], 2);
}

typedef struct s_cam_btn
{
	char		pos[200];
	char		axis[200];
	char		fov[200];
	mlx_image_t	*labels[4];
	mlx_texture_t *iconst[4];
	mlx_image_t *icons[4];

}	t_cam_btn;

void	set_cam_btn(t_data *data)
{
	t_cam_btn	*cambtn;
	int 		top;
	int			left;
	int			i;

	i = -1;
	top = 25;
	left = 20;
	cambtn = calloc(1, sizeof(t_cam_btn));
	snprintf(cambtn->pos,sizeof(cambtn->pos), "x:%.2f y:%.2f z:%.2f", data->cam->pos.x, data->cam->pos.y, data->cam->pos.z);
	snprintf(cambtn->axis,sizeof(cambtn->axis), "x:%.2f y:%.2f z:%.2f", data->cam->axis.x, data->cam->axis.y, data->cam->axis.z);
	snprintf(cambtn->fov,sizeof(cambtn->fov), "Fov: %d", data->cam->fov);
	cambtn->labels[0] = mlx_put_string(data->mlx, "Camera", data->x - BG_WITH + left + 100, top);
	cambtn->labels[1] = mlx_put_string(data->mlx, cambtn->pos, data->x - BG_WITH + left, top + 50);
	cambtn->labels[2] = mlx_put_string(data->mlx, cambtn->axis, data->x - BG_WITH + left, top + 100);
	cambtn->labels[3] = mlx_put_string(data->mlx, cambtn->fov, data->x - BG_WITH + left, top + 150);
	cambtn->iconst[0] = mlx_load_png("/home/shurtado/42/cursus/minirt-main/assets/icons/arrow_left.png");
	cambtn->iconst[1] = mlx_load_png("/home/shurtado/42/cursus/minirt-main/assets/icons/arrow_right.png");
	cambtn->icons[0] = mlx_texture_to_image(data->mlx, cambtn->iconst[0]);
	cambtn->icons[1] = mlx_texture_to_image(data->mlx, cambtn->iconst[1]);
	mlx_resize_image(cambtn->icons[0], cambtn->icons[0]->width / 12, cambtn->icons[0]->height / 12);
	mlx_resize_image(cambtn->icons[1], cambtn->icons[1]->width / 12, cambtn->icons[1]->height / 12);
	mlx_image_to_window(data->mlx, cambtn->icons[0], data->x - BG_WITH + 50, 20);
	mlx_image_to_window(data->mlx, cambtn->icons[1], data->x - 50, 20);
	while (++i < 4)
	{
		mlx_set_instance_depth(&cambtn->labels[i]->instances[0], 3);
		ft_lstadd_back(&data->console.btn_list, ft_lstnew(cambtn->labels[i]));
	}
	//mlx_set_instance_depth(&cambtn->icons[0]->instances[0], 4);
	ft_lstadd_back(&data->console.btn_list, ft_lstnew(cambtn->icons[0]));
	ft_lstadd_back(&data->console.btn_list, ft_lstnew(cambtn->icons[1]));
}
void	set_alight_btn(t_data *data)
{
	return ;
}
void	set_slight_btn(t_data *data)
{
	return ;
}
void	set_obj_btn(t_data *data)
{
	return ;
}
void	set_main_buttons(t_data *data)
{
	set_cam_btn(data);
	if (data->a_light)
		set_alight_btn(data);
	if (data->s_light)
		set_slight_btn(data);
	if (data->obj)
		set_obj_btn(data);
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
	set_main_buttons(data);
}
