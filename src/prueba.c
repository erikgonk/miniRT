#include "../inc/miniRT.h"

#define WIDTH 2128
#define HEIGHT 1024

static mlx_image_t	*g_img;

int x = 0;

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
		x += 0;
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	{
		printf("Hola\n");
		x -= 0;
	}
}
void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	while (++x < 500)
	{
		int y = 0;
		while(++y < 500)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
	}
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 500, 500);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
