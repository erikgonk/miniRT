/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSumI.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:40:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/03 19:03:51 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	skipFloat(char *str, int i, int j)
{
	if (!str[i])
		exit(er("error: wrong map: skipFloat", str));
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		else if (str[i] == '.')
			j++;
		else if (!ft_isdigit(str[i]))
			exit(er("error: wrong map: just  nums allowed", str));
		if (j > 1)
			exit(er("error: wrong map: too many .", str));
		else if (str[i + 1] && str[i] == '.' && !ft_isdigit(str[i + 1]))
			exit(er("error: wrong map: wrong char after .", str));
		i++;
	}
	return (i);
}

// skips a row of 3 floats and returns the point where it stops
int	skipFloats(char *str, int i, int j, int k) // str | i (start) | j . (0) | k , (0)
{
	if (!str[i] || !ft_isspace(str[i]))
		exit(er("error: wrong map: skipFloats", str));
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
			exit(er("error: wrong map: too many , or .", str));
		else if (str[i + 1] && ((str[i] == '.' || str[i] == ',') && !ft_isdigit(str[i + 1])))
			exit(er("error: wrong map: wrong char after , or .", str));
		else if (str[i + 1] && (str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
			exit(er("error: wrong map: wrong char after - or +", str));
		i++;
	}
	if (!str[i])
		exit(er("error: wrong map", str));
	return (i);
}

int	skipColor(char *str, int i, int j, int flag)
{
	while (flag == 0 && str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || ft_isspace(str[i]))
		exit(er("error: wrong map", NULL));
	while (str[i])
	{
		if (str[i + 1] && str[i] == ',' && !ft_isdigit(str[i + 1]))
			exit(er("error: wrong map: not a num after ,", str));
		else if (str[i] == ',')
			return (i + 1);
		else if (!ft_isdigit(str[i]))
			exit(er("error: wrong map: not a num", str));
		i++;
	}
	return (i);
}

int	erik(char *str, int i)
{
	int		j;

	j = 0;
	while (str[i] && !ft_isspace(str[i++]))
	{
		if (!ft_isdigit(str[i - 1]) && str[i - 1] != '.')
			exit(er("error: 2 parsing:\n", str));
		else if (str[i - 1] == '.')
			j++;
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}
int sumParse(char *str, int i, int flag, int j)
{
	// 0 skips spaces
	// 1 skips 1 float
	// 2 skips 3 floats
	// 4 skips spaces and 1 float
	while ((flag == 0 || flag == 4) && str[i] && ft_isspace(str[i]))
		i++;
	while ((flag == 1 || flag == 4) && str[i] && str[i++] != ',') {
		if (flag == 4 && ft_isspace(str[i]))
			break ;
		if (str[i - 1] == '.')
			j++;
		else if (!ft_isdigit(str[i - 1]))
			exit(er("error: 1 parsing:\n", str));
	}
	while (flag == 2 && str[i] && !ft_isspace(str[i++]))
	{
		if (!ft_isdigit(str[i - 1]) && str[i - 1] != '.')
			exit(er("error: 2 parsing:\n", str));
		else if (str[i - 1] == '.')
			j++;
	}
	while ((flag == 2 || flag == 4) && str[i] && ft_isspace(str[i]))
		i++;
	printf("i -> %")
	if (flag != 2 && (str[i] && !ft_isdigit(str[i])) || j >= 2)
		exit(er("error: map parsing:\n", str));
	return (i);
}
