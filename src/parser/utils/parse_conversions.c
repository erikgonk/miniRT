/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:47:50 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/20 11:37:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	colors_parse(char *str, int i)
{
	t_rgb	rgb;

	while (str[i] && ft_isspace(str[i]))
		i++;
	rgb.r = ft_atoi_parse(str, i, 1);
	i = skip_color(str, i, 0);
	rgb.g = ft_atoi_parse(str, i, 0);
	i = skip_color(str, i, 0);
	rgb.b = ft_atoi_parse(str, i, 0);
	return (rgb);
}

char	*floats_parse(t_obj *obj, char *str, int i, int flag)
{
	float	x;
	float	y;
	float	z;
	char	*tmp;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (!ft_isdigit(str[i]) && str[i] != '-'))
		exit(er("error: floats_parse: map parsing:\n", str));
	x = ft_atof(str, i);
	i = skip_float(str, i, 0, 1);
	y = ft_atof(str, i);
	i = random_sum_parse(str, i);
	z = ft_atof(str, i);
	i = sum_parse(str, i, 0);
	if (flag == 0)
		obj->pos = vdefine(x, y, z);
	else if (flag == 1)
		obj->axis = normalize(vdefine(x, y, z));
	tmp = ft_substr(str, i, ft_strlen(str));
	return (tmp);
}

int	ft_atoi_parse(char *str, int i, int flag)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((flag == 1 || flag == 2) && str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == ',' && flag != 2)
		i++;
	else if (str[i] == '-')
		sign = -sign;
	if (flag == 2 && (!ft_isdigit(str[i]) || (str[i + 1] && str[i + 2])))
		exit(er("error: atoi: str invalid\n", NULL));
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		exit(er("error: atoi: not a digit\n", str));
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	res *= sign;
	return (res);
}

float	ft_atof_normi(char *str, int i)
{
	float	fraction;
	float	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (str[i] >= '0' && str[i] <= '9' && (str[i] != ','
			|| ft_isspace(str[i]) != 1))
	{
		fraction += (str[i] - '0') / divisor;
		divisor *= 10.0f;
		i++;
		if (str[i] && !(str[i] == ',' || str[i] == '.' || ft_isspace(str[i])
				|| ft_isdigit(str[i])))
			exit(er("wrong char between nums", str));
	}
	return (fraction);
}

float	ft_atof(char *str, int i) // i = start
{
	float		res;
	int			sign;

	res = 0.0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && (str[i] != ','
			|| ft_isspace(str[i]) != 1))
	{
		res = (res * 10.0f) + (str[i] - '0');
		i++;
		if (str[i] && !(str[i] == ',' || str[i] == '.' || ft_isspace(str[i])
				|| ft_isdigit(str[i])))
			exit(er("wrong char between nums", str));
	}
	if (str[i] == '.' && (str[i] != ',' || ft_isspace(str[i]) != 1))
		return ((res + ft_atof_normi(str, ++i)) * sign);
	return (res * sign);
}
