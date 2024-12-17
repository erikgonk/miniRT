/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:16 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/17 11:12:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	print_t_rgb(const char *label, t_rgb rgb)
{
	printf("%s -> r: %u, g: %u, b: %u\n", label, rgb.r, rgb.g, rgb.b);
}

void	print_t_v3(const char *label, t_v3 vec)
{
	printf("%s -> x: %.2f, y: %.2f, z: %.2f\n", label, vec.x, vec.y, vec.z);
}
