/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/23 12:22:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	er(t_data *data, char *s, char *argv)
{
	ft_printf(2, "%s", RED);
	if (s)
		ft_printf(2, "%s\n", s);
	ft_printf(2, "%s", BOLD);
	if (argv)
		ft_printf(2, "%s\n", argv);
	ft_printf(2, "%s", RESET);
	free(data->m_trace);
	free(data->m_god);
	free(data->console);
	if (data->args)
		ft_free_willy(data->args);
	free_willy_lst(data);
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

t_obj	*new_obj(t_data *data)
{
	t_obj	*tmp;

	tmp = calloc(sizeof(*tmp), 1);
	if (!tmp)
		exit(er(data, "error: new_obj: malloc", NULL));
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
