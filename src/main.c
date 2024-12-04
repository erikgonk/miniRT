/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:12:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/12/04 16:26:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// make && ./miniRT 0.0 0.0 5.0 1 230 232 255 0.0 -3.0 -1.0 1
int	main(int ac, char **av)
{
	t_data			*data;
	mlx_t			*mlx;
    mlx_image_t		*img;
	int				fd;
	int			**img_rgb;

	/*
	data = malloc(sizeof(t_data));
	if (ac != 2)
		exit(er("error: 2 args needed", NULL));
	correct_file(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
	parse(data, av, fd);
	*/
	data = init_example_data();
	print_t_data(data);
	// exit(1);

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", true);
	if (!mlx)
		exit (er("Failed to initialize MLX42", NULL));
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
		exit(er("Failed to create image\n", NULL));
	img_rgb = render(data);
	if (!img_rgb)
		exit(er("Failed to render scene", NULL));

	uint32_t *pixels = (uint32_t *)img->pixels;
	for (int y = 0; y < WINDOW_HEIGHT; y++) 
	{
	    for (int x = 0; x < WINDOW_WIDTH; x++) 
	    {
	        // Obtener el color de img_rgb
	        uint32_t rgb = img_rgb[y][x]; // Supongo que el formato es 0xRRGGBB
	
	        // Convertir de RGB (0xRRGGBB) a BGRA (0xAABBGGRR)
	        uint32_t b = (rgb & 0xFF) << 16;     // Mover azul a la posición correcta
	        uint32_t g = (rgb & 0xFF00);         // Verde queda en su lugar
	        uint32_t r = (rgb & 0xFF0000) >> 16; // Mover rojo a la posición correcta
	        uint32_t a = 0xFF000000;             // Alpha fijo en 0xFF (opaco)
	        uint32_t bgra = a | b | g | r;
	
	        // Asignar al buffer de píxeles de MLX42
	        pixels[y * WINDOW_WIDTH + x] = bgra;
	    }
	}
		img->enabled = true;
	    mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
	exit(0);
}
