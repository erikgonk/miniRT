/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/24 14:21:37 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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

int sumParse(char *str, int i, int flag)
{
	int		j;

	j = 0;
	while (flag == 0 && str[i] && ft_isspace(str[i]))
		i++;
	while (flag == 1 && str[i] && str[i++] != ',')
		if (str[i - 1] == '.')
			j++;
		else if (!ft_isdigit(str[i - 1]))
			exit(er("error: 1 parsing:\n", str));
	while (flag == 2 && str[i] && !ft_isspace(str[i++]))
	{
		if (!ft_isdigit(str[i - 1]) && str[i - 1] != '.')
			exit(er("error: 2 parsing:\n", str));
		else if (str[i - 1] == '.')
			j++;
	}
	while (flag == 2 && str[i] && ft_isspace(str[i]))
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
	
	i = sumParse(str, i, 0);
	x = ft_atof(str, i);
	i = sumParse(str, i, 1);
	y = ft_atof(str, i);
	i = sumParse(str, i, 1);
	z = ft_atof(str, i);
	i = sumParse(str, i, 2);
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

	i = 0;
	res = 0;
	sign = 1;
	if (!str)
		exit (er("error: parse colors\n", NULL));
	if (str[i] == ',')
		i++;
	else if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		exit (er("error: parse colors\n", str));
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	res *= sign;
	return (res);
}

t_rgb	colorsParse(t_obj *obj, char *str)
{
	t_rgb		rgb;
	int			i;

	i = 0;
	rgb.r = ft_atoiParse(str, i);
	while (str[i] != ',')
		i++;
	rgb.g = ft_atoiParse(str, i);
	while (str[i] != ',')
		i++;
	rgb.b = ft_atoiParse(str, i);
	return (rgb);
}
