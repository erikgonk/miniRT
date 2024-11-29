/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/29 12:51:07 by erigonza         ###   ########.fr       */
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

t_v3	floatsACLParse(char *str, int i)
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
	return (vDefine(x, y, z));
}

void	createCam(t_cam *cam, char *str, int type)
{
	int		i;
	char	*tmp = NULL;
	
	i = 0;
	if (type != 4)
		return ;
	cam = malloc(sizeof(t_cam));
	i = sumParse(str, 0, 0, 0);
	cam->pos = floatsACLParse(str, 0);
	tmp = ft_substr(str, sumParse(str, 0, 2, 0), ft_strlen(str));
	printf("%s", tmp);
	free(str);
	str = NULL;
	cam->axis = floatsACLParse(tmp, 0);
	str = ft_substr(tmp, sumParse(tmp, 0, 0, 0), ft_strlen(tmp));
	cam->fov = ft_atoiParse(str, 0);
	free(str);
	free(tmp);
	printf("%f, %f, %f\n%f. %f, %f\n%d\n", cam->pos.x, cam->pos.y, cam->pos.z, cam->axis.x, cam->axis.y, cam->axis.z, cam->fov);
}

void	createALight(t_aLight *light, char *str, int type)
{
	// int		i;
	// char	*tmp = NULL;
	// 
	// i = 0;
	// if (type != 3)
	// 	return ;
	// light = malloc(sizeof(t_aLight));
	// light->br = ft_atof(str, 0);
	// i = sumParse(str, 0, 4, 0);
	// tmp = ft_substr(str, i, ft_strlen(str));
	// light->rgb = colorsParse(tmp);
	// if (str)
	// 	free(str);
	// if (tmp)
	// 	free(tmp);

	// printf("%f, %f, %f\n%f\n%hhu, %hhu, %hhu\n", data->sLight->pos.x, data->sLight->pos.y, data->sLight->pos.z, data->sLight->br, data->sLight->rgb.r, data->sLight->rgb.g, data->sLight->rgb.b);
	// printf("%f\n%hhu, %hhu, %hhu\n", data->aLight->br, data->aLight->rgb.r, data->aLight->rgb.g, data->aLight->rgb.b);
}

void	createSLight(t_sLight *light, char *str, int type)
{
	// int		i;
	// char	*tmp = NULL;
	// 
	// i = 0;
	// if (type != 5)
	// 	return ;
	// light = malloc(sizeof(t_sLight));
	// i = sumParse(str, 0, 0, 0);
	// tmp = floatsACLParse(data, str, 0, 5);
	// light->br = ft_atof(tmp, 0);
	// free(str);
	// str = ft_substr(tmp, sumParse(tmp, 0, 2, 0), ft_strlen(tmp));
	// light->rgb = colorsParse(str);
	// if (str)
	// 	free(str);
	// if (tmp)
	// 	free(tmp);
	// // printf("%f, %f, %f\n%f\n%hhu, %hhu, %hhu\n", data->sLight->pos.x, data->sLight->pos.y, data->sLight->pos.z, data->sLight->br, data->sLight->rgb.r, data->sLight->rgb.g, data->sLight->rgb.b);
}
