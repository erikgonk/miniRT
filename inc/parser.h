/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:20:14 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 16:04:55 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

//      parser
void				parse(t_data *data, int fd);
void				validate_args_and_open(int ac, char **av, int *fd);
void				correct_file(char *name);

//		parse_obj
void				create_obj_normi(t_obj *obj, char **tmp, char **tmp2);
t_obj				*create_obj(char *str, int type);

//      parse_acl
t_v3				floats_acl_parse(char *str, int i);
void				create_alight(t_data *data, char *str, int type);
void				create_cam(t_data *data, char *str, int type);
void				create_slight(t_slight **s_light, char *str, int type);

//      checker_parse
void				check_end(char *str, int i);
void				check_light(t_alight *aL, t_slight *sL);
void				check_params_acl(t_alight *aL, t_slight *sL, t_cam *cam);
void				check_obj(t_obj *obj);
void				check_params(t_data *data);

//      parse_conversions
t_rgb				colors_parse(char *str, int i);
char				*floats_parse(t_obj *obj, char *str, int i, int flag);
int					ft_atoi_parse(char *str, int i, int flag);
float				ft_atof_normi(char *str, int i);
float				ft_atof(char *str, int i);

//		parse_sum
int					random_sum_parse(char *str, int i);
int					skip_float(char *str, int i, int j, int flag);
int					skip_floats(char *str, int i, int j, int k);
int					skip_color(char *str, int i, int flag);
int					sum_parse(char *str, int i, int j);

//		parse_utils
int					er(char *s, char *av);
int					type_obj(char *str);
t_obj				*new_obj(void);
void				objadd_back(t_obj **lst, t_obj *new);

//      extra_functionalities
void                init_materials(t_obj *obj);
void                skip_colors(char *str, char **res);
int                 type_extra_func(char *str);
void                parse_cb(t_obj *obj, char *str);
void                extra_functionalities(t_obj *obj, char *tmp);

#endif
