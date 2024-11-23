/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/23 16:53:07 by erigonza         ###   ########.fr       */
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

int	cylindreParse(t_obj *obj)
{
	printf("cylindre\n");
	return 0;
}

int	planeParse(t_obj *obj)
{
	printf("Plane\n");
	return 0;
}

int	sphereParse(t_obj *obj)
{
	printf("sphere\n");
	return 0;
}

int	redirObjs(t_obj *obj, int type)
{
	static char		*bts[] = {"pwd", "echo", "cd", "export",
		"unset", "env", "exit", NULL};
	static int		(*objects[])(t_obj *) = {sphereParse, planeParse, cylindreParse};

	if (bts[type])
		objects[type](obj);
	else
		return (-1);
	return (0);
}

int sumParse(char *str, int i, int flag)
{
	int		j;

	j = i;
	while (flag == 0 && str[i] && ft_isspace(str[i]))
		i++;
	while (flag == 1 && str[i] && str[i] != ',')
		i++;
	while (flag == 2 && str[i] && (str[i] != ',' || ft_isspace(str[i])))
		i++;
	if (flag == 1)
		i++;
	if (j == i)
		exit(er("error: parsing:\n", str));
	// printf("\n%c\n%d\n%s\n", str[i], i, str);
	if (flag != 2 && !(str[i] >= '0' && str[i] <= '9'))
		exit(er("error: parsing:\n", str));
	return (i);
}

t_obj	*createObj(t_data *data, t_obj *obj, char *str, int type)
{
	float		x;
	float		y;
	float		z;
	int			i;
	
	i = sumParse(str, 2, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1);
	y = ft_atof(str, i);
	i = sumParse(str, i, 1);
	z = ft_atof(str, i);
	i = sumParse(str, i, 2);
	obj = newObj(obj);
	obj->pos = vDefine(x, y, z);
	// redirObjs(obj, type);
	// obj->type = type;
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
				printf("aqui peta\n");
				tmp->next = obj;
				obj = tmp;
			}
		}
		else if (type <= 5 && ft_isspace(str[1]))
			parseOthers(data, type);
		else
			exit (er("error: map not valid\n", str));
	}
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
