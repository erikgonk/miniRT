/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/17 11:43:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	random_sum_parse(char *str, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (str[i] && str[i] != ',')
	{
		if (ft_isdigit(str[i]))
			j = 0;
		if (k >= 2 || j >= 2)
			exit(er("error: random_sum_parse", str));
		if (ft_isspace(str[i]))
			break ;
		if (str[i] == '.')
			j++;
		else if (str[i] == ',')
			k++;
		else if (!ft_isdigit(str[i]) && str[i] != '-')
			exit(er("error: random_sum_parse", str));
		i++;
	}
	if (str[i] && str[i] == ',')
		i++;
	return (i);
}

t_v3	floats_acl_parse(char *str, int i)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;

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
	data->a_light->rgb = colors_parse(tmp);
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
	free(str2);
	free(tmp);
}

void	create_slight(t_data *data, char *str, int type)
{
	t_slight	*slight;
	int			i;
	char		*tmp;
	char		*str2;

	tmp = NULL;
	i = 0;
	if (type != 5 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->s_light = malloc(sizeof(t_slight));
	data->s_light->next = NULL;
	slight = data->s_light;
	slight->pos = floats_acl_parse(str, 1);
	tmp = ft_substr(str, skip_floats(str, 1, 0, 0), ft_strlen(str));
	slight->br = ft_atof(tmp, 0);
	str2 = ft_substr(tmp, skip_float(tmp, 0, 0, 0), ft_strlen(tmp));
	slight->rgb = colors_parse(str2);
	free(str2);
	free(tmp);
}
