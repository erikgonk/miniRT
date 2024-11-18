/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/18 16:50:48 by erigonza         ###   ########.fr       */
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
        atof(av[8]),  // Light X position
        atof(av[9]),  // Light Y position
        atof(av[10])  // Light Z position
    );
    data->light->br = atof(av[11]);  // Light brightness ratio
    if (data->light->br < 0.0f || data->light->br > 1.0f)
        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
}

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	if (ac != 12)
		exit(er("error: 12 args needed", NULL));
	(void)ac;
	t_data			data;
	mlx_t			*mlx;
    mlx_image_t		*img;

	data.sp = malloc(sizeof(t_sphere));
	data.light = malloc(sizeof(t_sphere));
	if (!data.sp || !data.light)
		exit(er("error: sp malloc", NULL));

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit ((ft_printf(2, "Failed to initialize MLX42\n")) * 0);

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(ft_printf(2, "Failed to create image\n") * 0);

	ft_init(&data, av);
	ft_sphere(data.sp, data.light, img);
    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}
