#include "../inc/miniRT.h"

#define WIDTH 200
#define HEIGHT 200

static mlx_image_t	*g_img;

int x = 0;

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_RIGHT)
	{
		mlx_close_window(mlx);
	}
}
void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	x = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	while (++x < 25)
	{
		int y = 0;
		while(++y < 25)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
	}
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 100, 50);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
