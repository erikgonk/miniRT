/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/18 17:56:51 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define CAMPLUS 5
# define CAMAXISP 0.05f
# define CAMAXISMIN -1.00f
# define CAMAXISMAX 1.00f

# define LIGHTPLUS 0.02f
# define LIGHTMIN	0.0f
# define LIGHTMAX	1.0f

# define SPOTPLUS 5

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
	row1l = 3,
	row1r = 4,
	row2l = 5,
	row2r = 6,
	row3l = 8,
	row3r = 9,
	row4l = 10,
	row4r = 11,
	row5l = 12,
	row5r = 13,
	row6l = 14,
	row6r = 15,
	row7l = 16,
	row7r = 17,
	row8l = 18,
	row8r = 19,
	row9l = 20,
	row9r = 21,
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
	fov_min = row7l,
	fov_max = row7r,
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
	char			row1[200];
	char			row2[200];
	char			row3[200];
	char			row4[200];
	char			row5[200];
	char			row6[200];
	char			row7[200];
	char			row8[200];
	char			row9[200];
	mlx_image_t		*labels[50];
	mlx_texture_t	*iconst[4];
}	t_img_btn;

//		console_run
void		run_console(t_data *data);
void		set_all_buttons(t_data *data);
void		set_labels(t_data *data, t_img_btn *img_btn, int top);
void		set_obj_labels(t_data *data, t_img_btn *img_btn, int top);

//		init_general
void		init_console(t_data *data);

//		init_pos_axis
void		make_arrows(t_data *data);
void		rows_1to3_left(t_data *data);
void		rows_1to3_right(t_data *data);
void		rows_4to6_left(t_data *data);
void		rows_4to6_right(t_data *data);

//		init_extra
void		rows_7(t_data *data);
void		rows_8(t_data *data);
void		rows_9(t_data *data);


//		helpers
void		del_image(void *content);
mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y);
mlx_image_t	*create_menu_background(t_data *data);
void		set_background(t_data *data);
mlx_image_t	*put_str(mlx_t *mlx, const char *str, int x, int y);

//		labels
void		set_cam_labels(t_data *data, t_img_btn *img_btn, int top);
void		set_alight_labels(t_data *data, t_img_btn *img_btn, int top);
void		set_slight_labels(t_data *data, t_img_btn *img_btn, int top);

//		console_labels_object
void		plane_labels(t_data *data, t_img_btn *img_btn);
void		sphere_labels(t_data *data, t_img_btn *img_btn);
void		cylinder_labels(t_data *data, t_img_btn *img_btn);
void		cube_labels(t_data *data, t_img_btn *img_btn);
void		cone_labels(t_data *data, t_img_btn *img_btn);

//		console_labels_obj
void		plane_set_labels(t_data *data, t_img_btn *img_btn, int top);
void		sphere_set_labels(t_data *data, t_img_btn *img_btn, int top);
void		cylinder_set_labels(t_data *data, t_img_btn *img_btn, int top);
void		cube_set_labels(t_data *data, t_img_btn *img_btn, int top);
void		cone_set_labels(t_data *data, t_img_btn *img_btn, int top);

//		write_labels_set
void		write_cam_labels(t_data *data, t_img_btn *img_btn);
void		write_alight_labels(t_data *data, t_img_btn *img_btn);
void		write_slight_labels(t_data *data, t_img_btn *img_btn);
void		write_obj_labels(t_data *data, t_img_btn *img_btn);

//		icons
void		put_imgarrows(t_data *data, int top);
void		set_resize_buton_images(t_data *data, t_img_btn *img_btn);
void		fill_image_list(t_data *data, t_img_btn *img_btn);
int			count_labels(t_data *data);
int			count_arrows(t_data *data);

//		click
void		console_click(t_data *data, int x, int y);
void		click_obj_console(t_data *data, t_btn_name clicked);

//		click_obj
void		click_type(t_data *data, t_obj *obj, t_btn_name clicked, int type);
void		click_cube(t_data *data, t_obj *obj, t_btn_name clicked);
void		click_cy_co(t_data *data, t_obj *obj, t_btn_name clicked);
void		click_sphere(t_data *data, t_obj *obj, t_btn_name clicked);
bool		obj_click_move(t_data *data, t_obj *obj, t_btn_name clicked);

//		click_obj_utils
bool		obj_click_move_normi(t_data *data, t_obj *obj, t_slight *slight);

//		click_cam
void		console_click_axis(t_data *data, t_btn_name clicked);
void		console_click_pos(t_data *data, t_btn_name clicked);
void		click_cam_console(t_data *data, t_btn_name clicked);

//		click_alight
bool		alight_click_move(t_data *data, t_btn_name clicked);
void		click_alight_console(t_data *data, t_btn_name clicked);

//		click_slight
bool		slight_click_move(t_data *data, t_slight *slight, \
											t_btn_name clicked);
void	click_slight_console(t_data *data, t_slight *slight, \
										t_btn_name clicked);

//		click_utils
int			ft_objremove(t_obj **lst, t_obj *node);
void		free_after_click(t_data *data);
t_btn_name	get_clicked_btn(t_data *data, int x, int y);
t_slight	*get_prev(t_data *data, t_slight *slight);

#endif
