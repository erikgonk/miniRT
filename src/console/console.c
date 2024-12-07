/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:19:26 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/07 12:26:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "miniRT.h"
 #include "console.h"

 void	set_conole()
 {
	static t_menu	menu;
	menu = camera;
	printf(RED);
	printf("Camera");
	printf(RESET);
 }
