/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:34:20 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 13:34:22 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(t_data *data)
{
	init_obj(data);
	init_light(data);
	init_mlx(data);
}

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		exit(er("error: failed to allocate memory", NULL));
}
