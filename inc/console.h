/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:12:24 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/17 19:50:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

# include "miniRT.h"

# define ALIGHTPLUS 0.01f
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
	left,
	right,
	pos_xmin,
	pos_xmax,
	pos_ymin,
	pos_ymax,
	pos_zmin,
	pos_zmax,
	axis_xmin,
	axis_xmax,
	axis_ymin,
	axis_ymax,
	axis_zmin,
	axis_zmax,
	rgb_rmin,
	rgb_rmax,
	rgb_gmin,
	rgb_gmax,
	rgb_bmin,
	rgb_bmax,
	fov_min,
	fov_max,
	size,
	height
}	t_btn_name;

typedef struct s_btn
{
	t_btn_name	name;
	int			x;
	int 		y;
	int 		w;
	int 		h;
}				t_btn;

typedef struct s_img_btn
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
}	t_img_btn;

mlx_image_t *put_str(mlx_t *mlx, const char *str, int width, int height);
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

//		util
void		del_image(void *content);
mlx_image_t	*create_button(mlx_t *mlx, const char *label, int x, int y);
mlx_image_t	*create_menu_background(t_data *data);
void		set_background(t_data *data);
mlx_image_t	*put_str(mlx_t *mlx, const char *str, int x, int y);

#endif
