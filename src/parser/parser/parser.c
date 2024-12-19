/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/19 16:03:10 by erigonza         ###   ########.fr       */
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
		exit(er("error: correct_file: wrong file name -> ", name));
	else if (name[i] == '.' && name[i + 1] == 'r' && name[i + 2] == 't')
		return ;
	exit(er("error: correct_file: wrong file name -> ", name));
}

void	validate_args_and_open(int ac, char **av, int *fd)
{
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
		exit(er("error: fd failed", NULL));
}

void	parse(t_data *data, int fd)
{
	char	type;
	char	*str;

	str = NULL;
	data->obj = NULL;
	data->s_light = NULL;
	while (true)
	{
		if (str)
			free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		if (str[0] == '#')
			continue ;
		type = type_obj(str);
		if (type > 5)
			exit(er("error: parse: wrong map: obj type", str));
		if (type <= 2 && ft_isspace(str[2]))
			objadd_back(&data->obj, create_obj(str, type));
		create_alight(data, str, type);
		create_cam(data, str, type);
		create_slight(&data->s_light, str, type);
	}
	check_params(data);
}
