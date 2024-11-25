/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/25 12:41:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
			exit(er("error: parsing ACL", str));
		if (ft_isspace(str[i]))
			break ;
		if (str[i] == '.')
			j++;
		else if (str[i] == ',')
			k++;
		else if (!ft_isdigit(str[i]))
			exit(er("error: parsing ACL", str));
		i++;
	}
	if (str[i] && str[i] == ',')
		i++;
	return (i);
}

char	*floatsACLParse(t_data *data, char *str, int i, int flag)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;
	
	i = sumParse(str, i, 0, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1, 0);
	y = ft_atof(str, i);
	i = randomSumParse(str, i);
	z = ft_atof(str, i);
	i = sumParse(str, i, 2, 0);
	if (flag == 4)
		data->cam->pos = vDefine(x, y, z);
	else if (flag == 5)
		data->sLight->pos = vDefine(x, y, z);
	tmp = ft_substr(str, i, ft_strlen(str));
	return (tmp);
}

void	createACL(t_data *data, char *str, int type)
{
	int		i;
	char	*tmp = NULL;
	
	i = 0;
	if (type == 3) // A
	{
		data->aLight = malloc(sizeof(t_aLight));
		data->aLight->br = ft_atof(str, 0);
		i = sumParse(str, 0, 4, 0);
		tmp = ft_substr(str, i, ft_strlen(str));
		data->aLight->rgb = colorsParse(tmp);
	}
	else if (type == 4) // C
	{
		data->cam = malloc(sizeof(t_sLight));
		i = sumParse(str, 0, 0, 0);
		tmp = floatsACLParse(data, str, 0, type);
		free(str);
		str = floatsACLParse(data, tmp, 0, type);
		data->cam->fov = ft_atoiParse(str, 0);
	}
	else if (type == 5) // L
	{
		data->sLight = malloc(sizeof(t_cam));
		i = sumParse(str, 0, 0, 0);
		tmp = floatsACLParse(data, str, 0, type);
		data->sLight->br = ft_atof(tmp, 0);
		free(str);
		str = ft_substr(tmp, sumParse(tmp, 0, 2, 0), ft_strlen(tmp));
		data->sLight->rgb = colorsParse(str);
	}
	if (str)
		free(str);
	if (tmp)
		free(tmp);
}
