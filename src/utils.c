/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:47:50 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/19 09:48:24 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	er(char *s, char *argv)
{
	ft_printf(2, "%s", RED);
	if (s)
		ft_printf(2, "%s", s);

	ft_printf(2, "%s", BOLD);
	if (argv)
		ft_printf(2, " %s", argv);
	ft_printf(2, "%s\n", RESET);
	return (1);
}

void	ft_init(t_data *data, char **av)
{
	data->sp->ray_start = vDefine(0.0, 0.0, 0.0);		// Camera position (where our rays start from)	
 	data->sp->sphere_radius = 1.4;						// Radius (size) of the sphere
    data->sp->sphere_center = vDefine(
        atof(av[1]),
        atof(av[2]),
        atof(av[3]));

    data->sp->sphere_radius = atof(av[4]);  // Sphere radius
    data->sp->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));

    // Initialize light source
    data->light->pos = vDefine(
        atof(av[8]),  // X
        atof(av[9]),  // Y
        atof(av[10])  // Z
    );
    data->light->br = atof(av[11]);  // Light brightness ratio
    if (data->light->br < 0.0f || data->light->br > 1.0f)
        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
}

