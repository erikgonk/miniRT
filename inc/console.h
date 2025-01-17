/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 21:59:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define ALIGHTPLUS 0.02f
# define ALIGHTMAX	1.0f
# define ALIGHTMIN	0.0f

# define CAMPLUS 5
# define CAMAXISP 0.05f
# define CAMAXISMIN -1.00f
# define CAMAXISMAX 1.00f

# define SPOTPLUS 5
# define SLIGHTPLUS 0.01f
# define SLIGHTMAX	1.0f
# define SLIGHTMIN	0.0f

# define OBJPLUS 5
# define OBJAXISP 0.01f
# define OBJAXISMIN -1.00f
# define OBJAXISMAX 1.00f

# define ALIGHT_M 0
# define CAM_M 1
# define OBJ_M 2
# define SPOT_M 3

# define BG_WITH 300

typedef enum btn_name
{
	none = 0,
	left = 1,
	right = 2,
	pos_xmin = 3,
	pos_xmax = 4,
	pos_ymin = 5,
	pos_ymax = 6,
	pos_zmin = 8,
	pos_zmax = 9,
	axis_xmin = 10,
	axis_xmax = 11,
	axis_ymin = 12,
	axis_ymax = 13,
	axis_zmin = 14,
	axis_zmax = 15,
	rgb_rmin = 16,
	rgb_rmax = 17,
	rgb_gmin = 18,
	rgb_gmax = 19,
	rgb_bmin = 20,
	rgb_bmax = 21,
	fov_min = 22,
	fov_max = 23,
	size_max = 0,
	size_min = 0,
	height_max = 0,
	height_min = 0,
	br_min = 3,
	br_max = 4
}	t_btn_name;

typedef struct s_btn
{
	t_btn_name	name;
	int			x;
	int			y;
	int			w;
	int			h;
}				t_btn;

typedef struct s_img_btn
{
	char			posx[200];
	char			posy[200];
	char			posz[200];
	char			axisx[200];
	char			axisy[200];
	char			axisz[200];
	char			fov[200];
	mlx_image_t		*labels[50];
	mlx_texture_t	*iconst[4];
}	t_img_btn;

mlx_image_t	*put_str(mlx_t *mlx, const char *str, int width, int height);
void		run_console(t_data *data);
void		del_image(void *content);
mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y);
mlx_image_t	*create_menu_background(t_data *data);
void		console_click(t_data *data, int x, int y);

//		init_general
void		init_console(t_data *data);

//		init_pos_axis
void		make_arrows(t_data *data);
void		pos_buttons_min(t_data *data);
void		pos_buttons_max(t_data *data);
void		axis_buttons_min(t_data *data);
void		axis_buttons_max(t_data *data);

//		init_extra
void		init_fov(t_data *data);

//		helpers
void		del_image(void *content);
mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y);
mlx_image_t	*create_menu_background(t_data *data);
void		set_background(t_data *data);
mlx_image_t	*put_str(mlx_t *mlx, const char *str, int x, int y);

//		labels
void		set_cam_labels(t_data *data, t_img_btn *img_btn, int top);
void		set_alight_labels(t_data *data, t_img_btn *img_btn, int top);

//		write_labels
void		write_cam_labels(t_data *data, t_img_btn *img_btn);
void		write_alight_labels(t_data *data, t_img_btn *img_btn);

//		icons
void		put_imgarrows(t_data *data, int top);
void		set_resize_buton_images(t_data *data, t_img_btn *img_btn);
void		fill_image_list(t_data *data, t_img_btn *img_btn);
int			count_labels(t_data *data);
int			count_arrows(t_data *data);

//		click_utils
int			ft_objremove(t_obj **lst, t_obj *node);
void		free_after_click(t_data *data);
t_btn_name	get_clicked_btn(t_data *data, int x, int y);

#endif
