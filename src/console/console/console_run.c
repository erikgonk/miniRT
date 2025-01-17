/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:00:06 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 08:57:31 by shurtado         ###   ########.fr       */
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

mlx_image_t	*create_menu_background2(t_data *data)
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
	background = mlx_new_image(data->mlx, BG_WITH, 65);
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
			pixels[y * BG_WITH + x] = 0xFF000000;
			x++;
		}
		y++;
	}
	return (background);
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
			if (y >= 65)
				pixels[y * BG_WITH + x] = 0x80000000;
			else
				pixels[y * BG_WITH + x] = 0xFF000000;
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
	char		posx[200];
	char		posy[200];
	char		posz[200];
	char		axisx[200];
	char		axisy[200];
	char		axisz[200];
	char		fov[200];
	mlx_image_t	*labels[11];
	mlx_texture_t *iconst[4];
}	t_cam_btn;

void	set_labels(t_data *data, t_cam_btn *cambtn)
{
	snprintf(cambtn->posx,sizeof(cambtn->posx), "x          %.2f", data->cam->pos.x);
	snprintf(cambtn->posy,sizeof(cambtn->posy), "y          %.2f", data->cam->pos.y);
	snprintf(cambtn->posz,sizeof(cambtn->posz), "z          %.2f", data->cam->pos.z);
	snprintf(cambtn->axisx,sizeof(cambtn->axisx), "x           %.2f", data->cam->axis.x);
	snprintf(cambtn->axisy,sizeof(cambtn->axisy), "y           %.2f", data->cam->axis.y);
	snprintf(cambtn->axisz,sizeof(cambtn->axisz), "z           %.2f", data->cam->axis.z);
	snprintf(cambtn->fov,sizeof(cambtn->fov), "              %d", data->cam->fov);
}

void	set_cam_btn(t_data *data)
{
	t_cam_btn	*cambtn;
	int 		top;
	int			left;
	int			i;
	int			yspace;

	yspace = 0;
	top = 25;
	left = 100;
	cambtn = calloc(1, sizeof(t_cam_btn));
	set_labels(data, cambtn);
	cambtn->labels[0] = mlx_put_string(data->mlx, "Camera", data->x - BG_WITH + left + 20, top - 2);
	cambtn->labels[1] = mlx_put_string(data->mlx, "Pos", data->x - BG_WITH + left + 55, top +  50);
	cambtn->labels[2] = mlx_put_string(data->mlx, cambtn->posx, data->x - BG_WITH + 35, top +  80);
	cambtn->labels[3] = mlx_put_string(data->mlx, cambtn->posy, data->x - BG_WITH + 35, top +  110);
	cambtn->labels[4] = mlx_put_string(data->mlx, cambtn->posz, data->x - BG_WITH + 35, top +  140);
	cambtn->labels[5] = mlx_put_string(data->mlx, "Axis", data->x - BG_WITH + left + 55, top + 170);
	cambtn->labels[6] = mlx_put_string(data->mlx, cambtn->axisx, data->x - BG_WITH + 35, top + 200);
	cambtn->labels[7] = mlx_put_string(data->mlx, cambtn->axisy, data->x - BG_WITH + 35, top + 230);
	cambtn->labels[8] = mlx_put_string(data->mlx, cambtn->axisz, data->x - BG_WITH + 35, top + 260);
	cambtn->labels[9] = mlx_put_string(data->mlx, "FOV", data->x - BG_WITH + left + 58, top +  290);
	cambtn->labels[10] = mlx_put_string(data->mlx, cambtn->fov, data->x - BG_WITH + 25, top +  320);
	cambtn->iconst[0] = mlx_load_png("./assets/consol/arrow_b_left.png");
	cambtn->iconst[1] = mlx_load_png("./assets/consol/arrow_b_right.png");
	cambtn->iconst[2] = mlx_load_png("./assets/consol/arrow_s_left_blue.png");
	cambtn->iconst[3] = mlx_load_png("./assets/consol/arrow_s_right_blue.png");

	i = -1;
	while (++i < 4)
		data->console.icons[i] = mlx_texture_to_image(data->mlx, cambtn->iconst[i]);
	mlx_resize_image(data->console.icons[0], data->console.icons[0]->width / 1.5, data->console.icons[0]->height / 1.5);
	mlx_resize_image(data->console.icons[1], data->console.icons[1]->width / 1.5, data->console.icons[1]->height / 1.5);
	mlx_image_to_window(data->mlx, data->console.icons[0], data->x - BG_WITH + 30, 0);
	mlx_image_to_window(data->mlx, data->console.icons[1], data->x - data->console.icons[1]->width - 30, 0);

	mlx_resize_image(data->console.icons[2], data->console.icons[2]->width / 3, data->console.icons[2]->height / 3);
	mlx_resize_image(data->console.icons[3], data->console.icons[3]->width / 3, data->console.icons[3]->height / 3);
// pos
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 73);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 73);
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 103);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 103);
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 133);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 133);
// axis
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 193);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 193);
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 223);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 223);
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 253);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 253);
// FOV
	mlx_image_to_window(data->mlx, data->console.icons[2], data->x - BG_WITH + 100, top + 313);
	mlx_image_to_window(data->mlx, data->console.icons[3], data->x - data->console.icons[1]->width - 25, top + 313);

	i = -1;
	while (++i < 11)
	{
		mlx_set_instance_depth(&cambtn->labels[i]->instances[0], 3);
		ft_lstadd_back(&data->console.btn_list, ft_lstnew(cambtn->labels[i]));
	}
	i = -1;
	while (++i < 4)
		ft_lstadd_back(&data->console.btn_list, ft_lstnew(data->console.icons[i]));
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
	init_console(data);
	data->last_render = FAST;
	// data->render_sel = render_fast;
}
