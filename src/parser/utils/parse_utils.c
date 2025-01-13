/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:09 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/13 11:19:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_willy_lst(t_data *data)
{
	t_obj		*obj;
	t_slight	*s_light;

	obj = data->obj;
	s_light = data->s_light;
	if (!data)
		return ;
	if (data->a_light)
		free(data->a_light);
	if (data->cam)
		free(data->cam);
	while (data->obj)
	{
		data->obj = data->obj->next;
		free(obj);
		obj = data->obj;
	}
	while (data->s_light)
	{
		data->s_light = data->s_light->next;
		free(s_light);
		s_light = data->s_light;
	}
}

int	er(t_data *data, char *s, char *argv)
{
	ft_printf(2, "%s", RED);
	if (s)
		ft_printf(2, "%s", s);
	ft_printf(2, "%s", BOLD);
	if (argv)
		ft_printf(2, "\n%s", argv);
	ft_printf(2, "%s", RESET);
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

char	**ft_free_willy(char **cmd)
{
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[i])
		free(cmd[++i]);
	free(cmd);
	cmd = NULL;
	return (NULL);
}
