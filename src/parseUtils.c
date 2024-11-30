/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/30 13:02:18 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	checkObj(t_data *data, char *str)
{
	static char		*bts[] = {"sp", "pl", "cy", "A", "C", "L", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (50);
}

int	skipFloat(char *str, int i, int j)
{
	if (!str[i] || !ft_isspace(str[i]))
		exit(er("error: wrong map", NULL));
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
		exit(er("error: wrong map", NULL));
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

int sumParse(char *str, int i, int flag, int j)
{
	// 0 skips spaces
	// 1 skips 1 float
	// 2 skips 3 floats
	// 4 skips spaces and 1 float
	// printf("%s%c - %d\n", str, str[i], i);
	while ((flag == 0 || flag == 4) && str[i] && ft_isspace(str[i]))
		i++;
	while ((flag == 1 || flag == 4) && str[i] && str[i++] != ',')
	{
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
	// printf("%s%c - i -> %d\n", str, str[i], i);
	if (flag != 2 && (str[i] && !ft_isdigit(str[i])) || j >= 2)
		exit(er("error: map parsing:\n", str));
	return (i);
}

char	*floatsParse(t_obj *obj, char *str, int i, int flag)
{
	float		x;
	float		y;
	float		z;
	char		*tmp;
	
	i = sumParse(str, i, 0, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1, 0);
	y = ft_atof(str, i);
	i = sumParse(str, i, 1, 0);
	z = ft_atof(str, i);
	i = sumParse(str, i, 2, 0);
	if (flag == 0)
		obj->pos = vDefine(x, y, z);
	else if (flag == 1)
		obj->axis = vDefine(x, y, z);
	tmp = ft_substr(str, i, ft_strlen(str));
	return (tmp);
}

int	ft_atoiParse(char *str, int i, int flag)
{
	int				res;
	int				sign;

	res = 0;
	sign = 1;
	while  (flag == 1 && str[i] && ft_isspace(str[i]))
		i++;
	if (!str)
		exit (er("error: parse atoi: str doesn't exist\n", NULL));
	if (str[i] == ',')
		i++;
	else if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		exit (er("error: parse atoi: not a digit\n", str));
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	res *= sign;
	return (res);
}

t_rgb	colorsParse(char *str)
{
	t_rgb		rgb;
	int			i;

	i = 0;
	rgb.r = ft_atoiParse(str, i, 1);
	while (str[i] && str[i] != ',')
		i++;
	rgb.g = ft_atoiParse(str, i, 0);
	while (str[i] && str[i] != ',')
		i++;
	rgb.b = ft_atoiParse(str, i, 0);
	return (rgb);
}
