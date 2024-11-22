/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/22 13:35:04 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	ft_exit(t_data *data)
{
	printf("pasa0\n");
	free(data->obj);
}

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

int	checkObj(t_data *data, char *str)
{
	static char		*bts[] = {"sp", "pl", "cy", "C", "A", "L", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (50);
}

t_obj	*createObj(t_data *data, t_obj *obj, int type)
{
// do the logic I did to parse obj (paper)
	printf("OBJ\n");
	obj = newObj(obj);
	obj->type = type;
	return (obj);
}

void	parseOthers(t_data *data, int type)
{
	printf("OTHER\n");
	if (type == 3)
		data->cam = malloc(sizeof(t_sLight));
	else if (type == 4)
		data->sLight = malloc(sizeof(t_aLight));
	else if (type == 5)
		data->aLight = malloc(sizeof(t_cam));
}

t_obj	*parse(t_data *data, char **av)
{
	int		fd;
	char	type;
	char	*str = NULL;
	t_obj	*obj;
	t_obj	*tmp = NULL;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
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
			tmp = createObj(data, obj, type);
			if (tmp)
			{
				tmp->next = obj;
				obj = tmp;
			}
		}
		else if (type <= 5 && ft_isspace(str[1]))
			parseOthers(data, type);
		else
			exit (er("error: map not valid\n", str));
	}
	printf("hola\n");
	close(fd);
	exit (er("salio bien", NULL));

	data->obj->ray_start = vDefine(0.0, 0.0, 0.0);		// Camera position (where our rays start from)	
	data->obj->sphere_radius = 1.4;						// Radius (size) of the sphere
    data->obj->sphere_center = vDefine(
        atof(av[1]),
        atof(av[2]),
        atof(av[3]));

    data->obj->sphere_radius = atof(av[4]);  // Sphere radius
    data->obj->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));

    // Initialize light source
    data->sLight->pos = vDefine(
        atof(av[8]),  // X
        atof(av[9]),  // Y
        atof(av[10])  // Z
    );
    data->sLight->br = atof(av[11]);  // Light brightness ratio
    if (data->sLight->br < 0.0f || data->sLight->br > 1.0f)
        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
}
