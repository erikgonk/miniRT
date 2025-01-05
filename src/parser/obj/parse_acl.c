/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/05 14:49:10 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	floats_acl_parse(char *str, int i)
{
	float		x;
	float		y;
	float		z;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '-')
		exit(er("error: floats_acl_parse: map parsing:\n", str));
	x = ft_atof(str, i);
	i = skip_float(str, i, 0, 1);
	y = ft_atof(str, i);
	i = random_sum_parse(str, i);
	z = ft_atof(str, i);
	return (vdefine(x, y, z));
}

void	create_alight(t_data *data, char *str, int type)
{
	char		*tmp;

	tmp = NULL;
	if (type != 3 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->a_light = malloc(sizeof(t_alight));
	data->a_light->br = ft_atof(str, 1);
	tmp = ft_substr(str, skip_float(str, 1, 0, 0), ft_strlen(str));
	data->a_light->rgb = colors_parse(tmp, 0);
	check_end(tmp, 1);
	free(tmp);
}

void	create_cam(t_data *data, char *str, int type)
{
	char	*tmp;
	char	*str2;
	int		i;

	tmp = NULL;
	if (type != 4 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->cam = malloc(sizeof(t_cam));
	data->cam->pos = floats_acl_parse(str, 1);
	tmp = ft_substr(str, skip_floats(str, 1, 0, 0), ft_strlen(str));
	data->cam->axis = normalize(floats_acl_parse(tmp, 0));
	str2 = ft_substr(tmp, skip_floats(tmp, 0, 0, 0), ft_strlen(tmp));
	data->cam->fov = ft_atoi_parse(str2, 0, 1);
	i = 0;
	while (str2[i] && ft_isspace(str2[i]))
		i++;
	while (str2[i] && ft_isdigit(str2[i]))
		i++;
	while (str2[i] && str2[i] != '\n')
		if (!ft_isspace(str2[i++]))
			exit(er("error: create_cam: cam fov wrong", str2));
	data->cam->focus_dist = 0;
	data->cam->aperture = 0.2;
	free(str2);
	free(tmp);
}

void	create_slight(t_slight **s_light, char *str, int type)
{
	t_slight	*new_light;
	t_slight	*current;
	char		*tmp[2];

	if (type != 5 || (str[1] && !ft_isspace(str[1])))
		return ;
	new_light = malloc(sizeof(t_slight));
	if (!new_light)
		exit(er("error: malloc failed for slight", NULL));
	new_light->pos = floats_acl_parse(str, 1);
	tmp[0] = ft_substr(str, skip_floats(str, 1, 0, 0), ft_strlen(str));
	new_light->br = ft_atof(tmp[0], 0);
	tmp[1] = ft_substr(tmp[0], skip_float(tmp[0], 0, 0, 0), ft_strlen(tmp[0]));
	new_light->rgb = colors_parse(tmp[1], 0);
	check_end(tmp[1], 0);
	new_light->next = NULL;
	if (*s_light == NULL)
		*s_light = new_light;
	else
	{
		current = *s_light;
		while (current->next != NULL)
			current = current->next;
		current->next = new_light;
	}
	return (free(tmp[1]), free(tmp[0]));
}
