/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/11 19:50:16 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	correct_file(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '.' && name[i])
		i++;
	if (name[i + 3] || !name[i - 1])
		exit(er("error: wrong file name -> ", name));
	else if (name[i] == '.' && name[i + 1] == 'r' && name[i + 2] == 't')
		return ;
	exit(er("error: wrong file name -> ", name));
}

t_obj	*createObj(t_data *data, char *str, int type)
{
	char	*tmp;
	char	*tmp2;
	t_obj	*obj;

	tmp2 = NULL;
	obj = newObj(obj);
	obj->type = type;
	tmp = floatsParse(obj, str, 2, 0);
	if (type != 0) // pl & cy
		tmp2 = floatsParse(obj, tmp, 0, 1);
	if (type == 0) // sp
	{
		obj->size = ft_atof(tmp, 0);
		tmp2 = ft_substr(tmp, sumParse(tmp, 0, 2, 0), ft_strlen(tmp));
	}
	else if (type == 2) // cy
	{
		obj->size = ft_atof(tmp2, 0);
		obj->i = sumParse(tmp2, 0, 2, 0);
		obj->height = ft_atof(tmp2, obj->i);
		obj->i = sumParse(tmp2, obj->i, 2, 0);
		free(tmp);
		tmp = ft_substr(tmp2, obj->i, ft_strlen(tmp2));
	}
	if (type != 2) // sp & pl
		obj->rgb = colorsParse(tmp2);
	else // cy
		obj->rgb = colorsParse(tmp);
	free(tmp);
	if (tmp2)
		free(tmp2);
	obj->type = type;
	return (obj);
}

void	checkParamsACL(t_aLight *aL, t_sLight *sL, t_cam *cam)
{
	if ((!aL && !sL) || !cam)
		exit(er("error: ACL left", NULL));
	if (aL)
		if (aL->br < 0)
			exit(er("error: brightness < 0", NULL));
		if (aL->rgb.r < 0 || aL->rgb.r > 255)
			exit(er("error: aL rgb.r <0 / >255", NULL));
		else if (aL->rgb.g < 0 || aL->rgb.g > 255)
			exit(er("error: aL rgb.g <0 / >255", NULL));
		else if (aL->rgb.b < 0 || aL->rgb.b > 255)
			exit(er("error: aL rgb.b <0/>255", NULL));
	while (sL)
	{
		if (sL->br < 0)
			exit(er("error: ACL left", NULL));
		else if (sL->rgb.r < 0 || sL->rgb.r > 255)
			exit(er("error: sL rgb.r <0 / >255", NULL));
		else if (sL->rgb.g < 0 || sL->rgb.g > 255)
			exit(er("error: sL rgb.g <0 / >255", NULL));
		else if (sL->rgb.b < 0 || sL->rgb.b > 255)
			exit(er("error: sL rgb.b <0/>255", NULL));
		sL = sL->next;
	}
	if (cam->axis.x < 0 || cam->axis.x > 1)
		exit(er("error: cam axis.x <0 / <1", NULL));
	else if (cam->axis.y < 0 || cam->axis.y > 1)
		exit(er("error: cam axis.y <0 / <1", NULL));
	else if (cam->axis.z < 0 || cam->axis.z > 1)
		exit(er("error: cam axis.z <0 / <1", NULL));
}

void	checkParams(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	if (!obj)
		exit(er("erro: no obj detected", NULL));
	while (obj)
	{
		if (obj->rgb.r < 0 || obj->rgb.r > 255)
			exit(er("error: rgb.r <0 / >255", NULL));
		else if (obj->rgb.g < 0 || obj->rgb.g > 255)
			exit(er("error: rgb.g <0 / >255", NULL));
		else if (obj->rgb.b < 0 || obj->rgb.b > 255)
			exit(er("error: rgb.b <0/>255", NULL));
		else if (obj->type != PL && obj->size <= 0)
			exit(er("error: sp/cy size <= 0", NULL));
		else if (obj->type != SP)
		{
			if (obj->axis.x < 0 || obj->axis.x > 1)
				exit(er("error: pl/cy axis.x <0 / <1", NULL));
			else if (obj->axis.y < 0 || obj->axis.y > 1)
				exit(er("error: pl/cy axis.y <0 / <1", NULL));
			else if (obj->axis.z < 0 || obj->axis.z > 1)
				exit(er("error: pl/cy axis.z <0 / <1", NULL));
			else if (obj->type == CY && obj->height < 0)
				exit(er("error: cy height < 0", NULL));
		}
		obj = obj->next;
	}
	checkParamsACL(data->aLight, data->sLight, data->cam);
}

void	parse(t_data *data, char **av, int fd)
{
	char	type;
	char	*str;

	str = NULL;
	data->obj = NULL;
	while (true)
	{
		if (str)
			free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		if (str[0] == '#')
			continue ;
		type = checkObj(data, str);
		if (type > 5)
			exit(er("error: wrong map: obj type", str));
		if (type <= 2 && ft_isspace(str[2]))
			objadd_back(&data->obj, createObj(data, str, type));
		createALight(data, str, type);
		createCam(data, str, type);
		createSLight(data, str, type);
	}
	checkParams(data);
	close(fd);
}
