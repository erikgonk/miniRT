/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/02 10:17:12 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		obj->pos = vdefine(x, y, z);
	else if (flag == 1)
		obj->axis = normalize(vdefine(x, y, z));
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
	while (str[i] && ft_isspace(str[i]))
		i++;
	rgb.r = ft_atoiParse(str, i, 1);
	i = skipColor(str, i, 0, 0);
	rgb.g = ft_atoiParse(str, i, 0);
	i = skipColor(str, i, 0, 0);
	rgb.b = ft_atoiParse(str, i, 0);
	return (rgb);
}
