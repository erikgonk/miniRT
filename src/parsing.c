/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/21 09:47:41 by erigonza         ###   ########.fr       */
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

void	createObj(t_data *data, t_obj *obj)
{
// do the logic I did to parse obj (paper)
	newObj(obj);
}

void	parseOthers(t_data *data)
{
	// data->cam = malloc(sizeof(t_sLight));
	// data->sLight = malloc(sizeof(t_aLight));
	// data->aLight = malloc(sizeof(t_cam));
}

void	parse(t_data *data, char **av)
{
	int		fd;
	char	*str = NULL;
	t_obj	*obj;

	data->obj = malloc(sizeof(t_obj));
	if (!data->obj)
		exit(er("error: malloc", NULL));
	obj = data->obj;
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
		obj->type  = checkObj(data, str);
		printf("%d\n", obj->type);
		if (obj->type <= 2)
			createObj(data, obj); // va crea un nuevo nodo cada vez que entra
		else if (obj->type <= 5)
			parseOthers(data);
		else
			exit (er("error: map not valid", str));

	}
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
