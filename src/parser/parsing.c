/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 17:18:20 by erigonza         ###   ########.fr       */
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
		type = type_obj(data, str);
		if (type > 5)
			exit(er("error: parse: wrong map: obj type", str));
		if (type <= 2 && ft_isspace(str[2]))
			objadd_back(&data->obj, create_obj(data, str, type));
		create_alight(data, str, type);
		create_cam(data, str, type);
		create_slight(data, str, type);
	}
	check_params(data);
	close(fd);
}
