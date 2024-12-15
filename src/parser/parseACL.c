/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 15:36:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	randomSumParse(char *str, int i)
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
			exit(er("error: parsing", str));
		if (ft_isspace(str[i]))
			break ;
		if (str[i] == '.')
			j++;
		else if (str[i] == ',')
			k++;
		else if (!ft_isdigit(str[i]) && str[i] != '-')
			exit(er("error: parsing", str));
		i++;
	}
	if (str[i] && str[i] == ',')
		i++;
	return (i);
}

t_v3	floatsACLParse(char *str, int i)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '-')
		exit(er("error: map parsing:\n", str));
	x = ft_atof(str, i);
	i = skipFloat(str, i, 0, 1);
	y = ft_atof(str, i);
	i = randomSumParse(str, i);
	z = ft_atof(str, i);
	return (vdefine(x, y, z));
}

void	createALight(t_data *data, char *str, int type)
{
	char		*tmp = NULL;

	if (type != 3 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->aLight = malloc(sizeof(t_aLight));
	data->aLight->br = ft_atof(str, 1);
	tmp = ft_substr(str, skipFloat(str, 1, 0, 0), ft_strlen(str));
	data->aLight->rgb = colorsParse(tmp);
	free(tmp);
}

void	createCam(t_data *data, char *str, int type)
{
	char	*tmp = NULL;
	char	*str2;
	int		i;

	if (type != 4 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->cam = malloc(sizeof(t_cam));
	data->cam->pos = floatsACLParse(str, 1);
	tmp = ft_substr(str, skipFloats(str, 1, 0, 0), ft_strlen(str));
	data->cam->axis = normalize(floatsACLParse(tmp, 0));
	str2 = ft_substr(tmp, skipFloats(tmp, 0, 0, 0), ft_strlen(tmp));
	data->cam->fov = ft_atoiParse(str2, 0, 1);
	i = 0;
	while (str2[i] && ft_isspace(str2[i]))
		i++;
	while (str2[i] && ft_isdigit(str2[i]))
		i++;
	while (str2[i] && str2[i] != '\n')
		if (!ft_isspace(str2[i++]))
			exit(er("error: cam fov wrong", str2));
	free(str2);
	free(tmp);
}

void	createSLight(t_data *data, char *str, int type)
{
	t_sLight	*sLight;
	int			i;
	char		*tmp = NULL;
	char		*str2;

	i = 0;
	if (type != 5 || (str[1] && !ft_isspace(str[1])))
		return ;
	data->sLight = malloc(sizeof(t_sLight));
	data->sLight->next = NULL;
	sLight = data->sLight;
	sLight->pos = floatsACLParse(str, 1);
	tmp = ft_substr(str, skipFloats(str, 1, 0, 0), ft_strlen(str));
	sLight->br = ft_atof(tmp, 0);
	str2 = ft_substr(tmp, skipFloat(tmp, 0, 0, 0), ft_strlen(tmp));
	sLight->rgb = colorsParse(str2);
	free(str2);
	free(tmp);
}
