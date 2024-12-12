/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/12 17:31:54 by erigonza         ###   ########.fr       */
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

void	parse(t_data *data, char **av, int fd)
{
	char	type;
	char	*str = NULL;

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
	exit (1);
}
