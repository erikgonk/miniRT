/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/10 14:17:16 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	doubles_acl_parse(char *str, int i)
{
	double		x;
	double		y;
	double		z;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '-')
		exit(er("error: doubles_acl_parse: map parsing:\n", str));
	x = ft_atof(str, i);
	i = skip_double(str, i, 0, 1);
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
	tmp = ft_substr(str, skip_double(str, 1, 0, 0), ft_strlen(str));
	data->a_light->rgb = colors_parse(tmp, 0);
	check_end(tmp, 1);
	free(tmp);
}

void	cam_blur(t_data *data, char *str2, char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i] && ft_isspace(tmp[i]))
		i++;
	if (tmp[i] && ft_isdigit(tmp[i]))
	{
		data->cam->focus_dist = ft_atof(tmp, 0);
		if (data->cam->focus_dist < 0)
			exit(er("error: cam_blur: focus distance negative", NULL));
		free(str2);
		str2 = ft_substr(tmp, skip_double(tmp, 0, 0, 0), ft_strlen(tmp));
		data->cam->aperture = ft_atof(str2, 0);
		if (data->cam->aperture < 0.01 || data->cam->aperture > 0.5)
			exit(er("error: cam_blur: aperture 0.01-0.5", NULL));

	}
	else
	{
		data->cam->focus_dist = -1;
		data->cam->aperture = 0;
	}
}

void	create_cam(t_data *data, char *str, int type)
{
	char	*tmp;
	char	*str2;

	tmp = NULL;
	if (type != 4 || (str[1] && !ft_isspace(str[1])))
		return ;
	if (data->cam)
		exit(er("error: create_cam: more than 1 camera", NULL));
	data->cam = malloc(sizeof(t_cam));
	data->cam->pos = doubles_acl_parse(str, 1);
	tmp = ft_substr(str, skip_doubles(str, 1, 0, 0), ft_strlen(str));
	data->cam->axis = normalize(doubles_acl_parse(tmp, 0));
	str2 = ft_substr(tmp, skip_doubles(tmp, 0, 0, 0), ft_strlen(tmp));
	data->cam->fov = ft_atoi_parse(str2, 0, 1);
	free(tmp);
	tmp = ft_substr(str2, skip_double(str2, 0, 0, 0), ft_strlen(str2));
	cam_blur(data, str2, tmp);
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
	new_light->pos = doubles_acl_parse(str, 1);
	tmp[0] = ft_substr(str, skip_doubles(str, 1, 0, 0), ft_strlen(str));
	new_light->br = ft_atof(tmp[0], 0);
	tmp[1] = ft_substr(tmp[0], skip_double(tmp[0], 0, 0, 0), ft_strlen(tmp[0]));
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
