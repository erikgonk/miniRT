/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_init_general.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:51:59 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/16 17:28:39 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_console(t_data *data)
{
	make_arrows(data);
	pos_buttons_min(data);
	pos_buttons_max(data);
	axis_buttons_min(data);
	axis_buttons_max(data);
	init_fov(data);
}
