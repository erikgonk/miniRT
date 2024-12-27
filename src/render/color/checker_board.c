/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:40:12 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/27 10:40:23 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

t_rgb checkerboard_color(t_v3 point, t_rgb color1, t_rgb color2, float scale)
{
    int x, y;

    // Escalar las coordenadas del punto para determinar el tamaño del patrón
    x = (int)floor(point.x * scale);
    y = (int)floor(point.z * scale); // Usamos Z para la otra dimensión en el plano

    // Alternar colores según la posición
    if ((x + y) % 2 == 0)
        return color1; // Color para las celdas "blancas"
    else
        return color2; // Color para las celdas "negras"
}
