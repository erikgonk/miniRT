/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:40:23 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 13:41:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//		utils
int					er(char *s, char *av);
t_obj				*new_obj(t_obj *obj);
float				ft_atof(char *str, int i);
float				ft_atof_normi(char *str, int i);
void				objadd_back(t_obj **lst, t_obj *new);

//		parse_obj
void				create_obj_normi(t_obj *obj, char **tmp, char **tmp2);
t_obj				*create_obj(t_data *data, char *str, int type);

// parse_acl
t_v3				floats_acl_parse(char *str, int i);
void				create_alight(t_data *data, char *str, int type);
void				create_cam(t_data *data, char *str, int type);
void				create_slight(t_slight **s_light, char *str, int type);

// parser
void				parse(t_data *data, char **av, int fd);
void				validate_args_and_open(int ac, char **av, int *fd);
void				correct_file(char *name);

//		parsing
void				parse(t_data *data, char **av, int fd);
void				correct_file(char *name);

//		checker
void				check_end(t_obj *obj, char *str);
void				check_obj(t_obj *obj);
void				check_light(t_alight *aL, t_slight *sL);
void				check_params_acl(t_alight *aL, t_slight *sL, t_cam *cam);
void				check_params(t_data *data);

//		parseACLUtils
int					random_sum_parse(char *str, int i);
void				create_cam(t_data *data, char *str, int type);
void				create_alight(t_data *data, char *str, int type);
void				create_slight(t_slight **s_light, char *str, int type);

//		parse sum to i
int					skip_color(char *str, int i, int j, int flag);
int					skip_floats(char *str, int i, int j, int k);
int					skip_float(char *str, int i, int j, int flag);
int					sum_parse(char *str, int i, int flag, int j);
//		parseUtils
int					type_obj(t_data *data, char *str);
char				*floats_parse(t_obj *obj, char *str, int i, int flag);
int					ft_atoi_parse(char *str, int i, int flag);
t_rgb				colors_parse(char *str);

#endif

