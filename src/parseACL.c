/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseACL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:27:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/01 14:35:09 by erigonza         ###   ########.fr       */
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

t_aLight	*createALight(t_data *data, char *str, int type)
{
	t_aLight	*aLight;
	char		*tmp = NULL;

	aLight = data->aLight;
	if (type != 3 || (str[1] && !ft_isspace(str[1])))
		return (NULL);
	aLight = malloc(sizeof(t_aLight));
	aLight->br = ft_atof(str, 1);
	tmp = ft_substr(str, skipFloat(str, 1, 0), ft_strlen(str));
	aLight->rgb = colorsParse(tmp);
	free(tmp);
	return (aLight);
	// printf("%s		%f %hhu, %hhu, %hhu\n\n", str, aLight->br, aLight->rgb.r, aLight->rgb.g, aLight->rgb.b);
}

t_cam	*createCam(t_data *data, char *str, int type)
{
	t_cam	*cam;
	char	*tmp = NULL;
	char	*str2;
	
	cam = data->cam;
	if (type != 4 || (str[1] && !ft_isspace(str[1])))
		return NULL;
	cam = malloc(sizeof(t_cam));
	cam->pos = floatsACLParse(str, 1);
	tmp = ft_substr(str, skipFloats(str, 1, 0, 0), ft_strlen(str));
	cam->axis = floatsACLParse(tmp, 0);
	str2 = ft_substr(tmp, skipFloats(tmp, 0, 0, 0), ft_strlen(tmp));
	cam->fov = ft_atoiParse(str2, 0, 1);
	free(str2);
	free(tmp);
	return (cam);
	// printf("		%f, %f, %f %f. %f, %f %d\n\n", cam->pos.x, cam->pos.y, cam->pos.z, cam->axis.x, cam->axis.y, cam->axis.z, cam->fov);
}

t_sLight	*createSLight(t_data *data, char *str, int type)
{
	t_sLight	*sLight;
	int			i;
	char		*tmp = NULL;
	char		*str2;

	sLight = data->sLight;
	i = 0;
	if (type != 5 || (str[1] && !ft_isspace(str[1])))
		return (NULL);
	sLight = malloc(sizeof(t_sLight));
	sLight->pos = floatsACLParse(str, 1);
	tmp = ft_substr(str, skipFloats(str, 1, 0, 0), ft_strlen(str));
	sLight->br = ft_atof(tmp, 0);
	str2 = ft_substr(tmp, skipFloat(tmp, 0, 0), ft_strlen(tmp));
	sLight->rgb = colorsParse(str2);
	free(str2);
	free(tmp);
	// printf("		%f, %f, %f %f %hhu, %hhu, %hhu\n\n", sLight->pos.x, sLight->pos.y, sLight->pos.z, sLight->br, sLight->rgb.r, sLight->rgb.g, sLight->rgb.b);
	return (sLight);
}
