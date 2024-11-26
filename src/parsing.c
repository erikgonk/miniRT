/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/26 09:46:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
	exit (er("error: wrong file name -> ", name));
}

t_obj	*createObj(t_data *data, t_obj *obj, char *str, int type)
{
	char		*newStr;
	char		*plCyStr = NULL;

	obj = newObj(obj);
	newStr = floatsParse(obj, str, 2, 0);
	if (type != 0)
		plCyStr = floatsParse(obj, newStr, 0, 1);
	if (type == 0)
	{
		obj->size = ft_atof(newStr, 0);
		obj->i = sumParse(newStr, 0, 2, 0);
		plCyStr = ft_substr(newStr, obj->i, ft_strlen(newStr));
	}
	else if (type == 2)
	{
		obj->size = ft_atof(newStr, 0);
		obj->i = sumParse(plCyStr, 0, 2, 0);
		obj->height = ft_atof(newStr, obj->i);
		obj->i = sumParse(plCyStr, obj->i, 2, 0);
		free(newStr);
		newStr = ft_substr(plCyStr, obj->i, ft_strlen(plCyStr));
	}
	if (type != 2)
		obj->rgb = colorsParse(plCyStr);
	else
		obj->rgb = colorsParse(newStr);
	free(newStr);
	if (plCyStr)
		free(plCyStr);
	return (obj);
}

t_obj	*parse(t_data *data, t_obj *obj, char **av, int fd)
{
	char	type;
	char	*str = NULL;
	t_obj	*tmp = NULL;

	while (true)
	{
		if (str)
			free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		if (str[0] == '#')
			continue ;
		type  = checkObj(data, str);
		if (type <= 2 && ft_isspace(str[2]))
		{
			tmp = createObj(data, tmp, str, type);
			if (tmp)
			{
				tmp->next = obj;
				obj = tmp;
			}
		}
		else if (type <= 5 && ft_isspace(str[1]))
		{
			// aLight
			// cam
			// sLight
			createACL(data, ft_substr(str, 1, ft_strlen(str)), type);
		}
		else
			exit (er("error: map not valid\n", str));
		if (type == 0)
			printf("%s%f, %f, %f\n%f\n%hhu, %hhu, %hhu\n", str, obj->pos.x, obj->pos.y, obj->pos.z, obj->size, obj->rgb.r, obj->rgb.g, obj->rgb.b);
		else if (type == 1)
			printf("%s%f, %f, %f\n%f, %f, %f\n%hhu, %hhu, %hhu\n", str, obj->pos.x, obj->pos.y, obj->pos.z, obj->axis.x, obj->axis.y, obj->axis.z, obj->rgb.r, obj->rgb.g, obj->rgb.b);
		else if (type == 2)
			printf("%s%f, %f, %f\n%f, %f, %f\n%f, %f\n%hhu, %hhu, %hhu\n", str, obj->pos.x, obj->pos.y, obj->pos.z, obj->axis.x, obj->axis.y, obj->axis.z, obj->size, obj->height, obj->rgb.r, obj->rgb.g, obj->rgb.b);
		// else if (type == 3)
		// 	printf("%s%f\n%hhu, %hhu, %hhu\n", data->aLight->br, data->aLight->rgb.r, data->aLight->rgb.g, data->aLight->rgb.b);
		// else if (type == 4)
			// printf("%s%f\n%hhu, %hhu, %hhu\n", data->aLight->br, data->aLight->rgb.r, data->aLight->rgb.g, data->aLight->rgb.b);
		// else if (type == 5)
	}
	close(fd);
	exit (er("salio bien", NULL));
}
	// data->obj->ray_start = vDefine(0.0, 0.0, 0.0);		// Camera position (where our rays start from)	
	// data->obj->sphere_radius = 1.4;						// Radius (size) of the sphere
 //    data->obj->sphere_center = vDefine(
 //        atof(av[1]),
 //        atof(av[2]),
 //        atof(av[3]));

 //    data->obj->sphere_radius = atof(av[4]);  // Sphere radius
 //    data->obj->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));

 //    // Initialize light source
 //    data->sLight->pos = vDefine(
 //        atof(av[8]),  // X
 //        atof(av[9]),  // Y
 //        atof(av[10])  // Z
 //    );
 //    data->sLight->br = atof(av[11]);  // Light brightness ratio
 //    if (data->sLight->br < 0.0f || data->sLight->br > 1.0f)
 //        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
