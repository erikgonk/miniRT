/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/11 12:29:36 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	type_obj(char *str)
{
	static char		*bts[] = {"sp", "pl", "cy", "A", "C", "L", "co", "cu", \
		NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], str))
		i++;
	if (bts[i])
		return (i);
	return (50);
}

t_obj	*new_obj(void)
{
	t_obj	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		exit(er("error: new_obj: malloc", NULL));
	tmp->next = NULL;
	return (tmp);
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
