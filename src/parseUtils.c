/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/25 12:40:06 by erigonza         ###   ########.fr       */
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

int sumParse(char *str, int i, int flag, int j)
{
	// 0 skips spaces
	// 1 skips 1 float
	// 2 skips a 3 floats
	// 4 skips spaces and 1 float
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
	if (flag != 2 && str[i] && !ft_isdigit(str[i]) || j >= 2)
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

int	ft_atoiParse(char *str, int i)
{
	int				res;
	int				sign;

	res = 0;
	sign = 1;
	if (!str)
		exit (er("error: parse atoi\n", NULL));
	if (str[i] == ',')
		i++;
	else if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		exit (er("error: parse atoi\n", str));
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
	rgb.r = ft_atoiParse(str, i);
	while (str[i] && str[i] != ',')
		i++;
	rgb.g = ft_atoiParse(str, i);
	while (str[i] && str[i] != ',')
		i++;
	rgb.b = ft_atoiParse(str, i);
	return (rgb);
}
