/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSumI.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:40:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 17:21:52 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// skips 1 float | stops when ' '
int	skip_float(char *str, int i, int j, int flag)
{
	if (!str[i])
		exit(er("error: skip_float: wrong map: skipFloat", str));
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (flag == 0 && ft_isspace(str[i]))
			return (i);
		else if (flag == 1 && str[i] == ',')
			return (++i);
		else if (str[i] == '.')
			j++;
		else if (!(ft_isdigit(str[i]) || str[i] == '-'))
			exit(er("error: skip_float: wrong map: just  nums allowed", str));
		if (j > 1)
			exit(er("error: skip_float: wrong map: too many .", str));
		else if (str[i + 1] && str[i] == '.' && !ft_isdigit(str[i + 1]))
			exit(er("error: skip_float: wrong map: wrong char after .", str));
		i++;
	}
	return (i);
}

// skips 3 floats | 1.2,4.1,0.0
// str | i (start) | j . (0) | k , (0)
int	skip_floats(char *str, int i, int j, int k)
{
	if (!str[i] || !ft_isspace(str[i]))
		exit(er("error: skip_floats: wrong map: NULL || not space", str));
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (k == 2 && ft_isspace(str[i]))
			break ;
		if (str[i] == '.')
			j++;
		else if (str[i] == ',')
			k++;
		if ((j > 3 || k > 2) || (ft_isspace(str[i]) && k != 2))
			exit(er("error: skip_floats: too many , or .", str));
		else if (str[i + 1] && ((str[i] == '.' || str[i] == ',')
				&& (!ft_isdigit(str[i + 1]) && str[i + 1] != '-')))
			exit(er("error: skip_floats: wrong char after , or .", str));
		else if (str[i + 1] && (str[i] == '-' || str[i] == '+')
			&& !ft_isdigit(str[i + 1]))
			exit(er("error: skip_floats: wrong char after - or +", str));
		i++;
	}
	if (!str[i])
		exit(er("error: skip_floats: wrong map: NULL end", str));
	return (i);
}

// skips 3 colors | 255,23,0
int	skip_color(char *str, int i, int j, int flag)
{
	while (flag == 0 && str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || ft_isspace(str[i]))
		exit(er("error: skip_color: wrong map", NULL));
	while (str[i])
	{
		if (str[i + 1] && str[i] == ',' && !ft_isdigit(str[i + 1]))
			exit(er("error: skip_color: wrong map: not a num after ,", str));
		else if (str[i] == ',')
			return (i + 1);
		else if (!ft_isdigit(str[i]))
			exit(er("error: skip_color: wrong map: not a num", str));
		i++;
	}
	return (i);
}

// skips 3 floats | 1.2,4.1,0.0
int	sum_parse(char *str, int i, int flag, int j)
{
	while (str[i] && !ft_isspace(str[i++]))
	{
		if (!ft_isdigit(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != '-')
			exit(er("error: sum_parse: 2 parsing:hola \n", str));
		else if (str[i - 1] == '.')
			j++;
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}
