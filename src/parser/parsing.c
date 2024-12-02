/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/02 10:17:34 by shurtado         ###   ########.fr       */
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
	exit (er("error: wrong file name -> ", name));
}

t_obj	*createObj(t_data *data, char *str, int type)
{
	char		*tmp;
	char		*tmp2 = NULL;
	t_obj		*obj;

	obj = newObj(obj);
	tmp = floatsParse(obj, str, 2, 0);
	if (type != 0) // pl & cy
		tmp2 = floatsParse(obj, tmp, 0, 1);
	if (type == 0) // sp
	{
		obj->size = ft_atof(tmp, 0);
		obj->i = sumParse(tmp, 0, 2, 0);
		tmp2 = ft_substr(tmp, obj->i, ft_strlen(tmp));
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
	obj->type = (char)type;
	return (obj);
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
		if (type <= 2 && ft_isspace(str[2]))
			objadd_back(&data->obj, createObj(data, str, type));
		createALight(data, str, type);
		createCam(data, str, type);
		createSLight(data, str, type);
	}
	close(fd);
}
	// data->obj->ray_start = vdefine(0.0, 0.0, 0.0);		// Camera position (where our rays start from)
	// data->obj->sphere_radius = 1.4;						// Radius (size) of the sphere
 //    data->obj->sphere_center = vdefine(
 //        atof(av[1]),
 //        atof(av[2]),
 //        atof(av[3]));

 //    data->obj->sphere_radius = atof(av[4]);  // Sphere radius
 //    data->obj->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));

 //    // Initialize light source
 //    data->sLight->pos = vdefine(
 //        atof(av[8]),  // X
 //        atof(av[9]),  // Y
 //        atof(av[10])  // Z
 //    );
 //    data->sLight->br = atof(av[11]);  // Light brightness ratio
 //    if (data->sLight->br < 0.0f || data->sLight->br > 1.0f)
 //        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
