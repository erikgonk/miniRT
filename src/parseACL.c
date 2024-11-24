/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/24 15:06:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

char	*floatsACLParse(t_data *data, char *str, int i, int flag)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;
	
	printf("no entiendo\n");
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (str)
		printf("%s\n", str);
	// i = sumParse(str, i, 0, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1, 0);
	y = ft_atof(str, i);
	i = sumParse(str, i, 1, 0);
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
	char	*tmp;
	
	// printf("%d\n", type);
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
		tmp = ft_substr(str, sumParse(str, 0, 4, 0), ft_strlen(str));
		floatsACLParse(data, str, i, type);
	}
	else if (type == 5) // L
	{
		data->sLight = malloc(sizeof(t_cam));
		floatsACLParse(data, str, i, type);
	}
	free(str);
	if (tmp)
		free(tmp);
}
