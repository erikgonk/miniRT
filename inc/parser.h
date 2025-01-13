/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:20:14 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/13 12:04:56 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

//      parser
void	parse(t_data *data, int fd);
void	validate_args_and_open(t_data *data, int ac, char **av, int *fd);
void	correct_file(t_data *data, char *name);

//		parse_obj
void	create_obj_normi(t_obj *obj, char **tmp, char **tmp2);
t_obj	*create_obj(t_data *data, char *str, int type);

//      parse_acl
t_v3	doubles_acl_parse(t_data *data, char *str, int i);
void	create_alight(t_data *data, char *str, int type);
void	cam_blur(t_data *data, char *str2, char *tmp);
void	create_cam(t_data *data, char *str, int type);
void	create_slight(t_data *data, t_slight **s_light, char *str, int type);

//      parse_checker
void	check_end(t_data *data, char *str, int i);
void	check_light(t_data *data, t_alight *aL, t_slight *sL);
void	check_params_acl(t_data *data, t_alight *aL, t_slight *sL, t_cam *cam);
void	check_obj_normi(t_obj *obj);
void	check_obj(t_obj *obj);

//		parse_main_checker
void	check_params(t_data *data);

//      parse_conversions
t_rgb	colors_parse(t_data *data, char *str, int i);
char	*doubles_parse(t_obj *obj, char *str, int i, int flag);
int		ft_atoi_parse(t_data *data, char *str, int i, int flag);
double	ft_atof_normi(t_data *data, char *str, int i);
double	ft_atof(t_data *data, char *str, int i);

//		parse_sum
int		random_sum_parse(t_obj *obj, char *str, int i);
int		skip_double(t_data *data, char *str, int i, int flag);
int		skip_doubles(t_data *data, char *str, int i, int k);
int		skip_color(t_data *data, char *str, int i, int flag);
int		sum_parse(t_data *data, char *str, int i, int j);

//		parse_utils
int		er(t_data *data, char *s, char *av);
int		type_obj(char *str);
t_obj	*new_obj(t_data *data);
void	objadd_back(t_obj **lst, t_obj *new);

//		parse_free willies
char	**ft_free_willy(char **cmd);
void	free_willy_lst(t_data *data);

//      extra_functionalities
void	init_materials(t_obj *obj);
void	skip_colors(t_data *data, char *str, char **res);
int		type_extra_func(char *str);

//      extra_functionalities_utils
void	parse_cb_em(t_obj *obj, char *str, int i);
void	extra_functionalities(t_obj *obj, char *tmp);

#endif
