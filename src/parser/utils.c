/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:47:50 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/15 17:18:50 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*new_obj(t_obj *obj)
{
	t_obj	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		exit(er("error: new_obj: malloc", NULL));
	tmp->next = NULL;
	return (tmp);
}

int	er(char *s, char *argv)
{
	ft_printf(2, "%s", RED);
	if (s)
		ft_printf(2, "%s", s);
	ft_printf(2, "%s", BOLD);
	if (argv)
		ft_printf(2, "\n%s", argv);
	ft_printf(2, "%s", RESET);
	return (1);
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

void	objadd_back(t_obj **lst, t_obj *new)
{
	t_obj	*current;

	if (lst)
	{
		if (*lst)
		{
			current = *lst;
			while (current->next != NULL)
				current = current->next;
			current->next = new;
		}
		else
			*lst = new;
	}
}
