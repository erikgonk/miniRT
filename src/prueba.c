#include "../inc/miniRT.h"

#define WIDTH 2000
#define HEIGHT 2000

static mlx_image_t	*g_img;

int x = 0;
int i = 100;

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	printf("%p\n", param);
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		printf("panquesito\n");
		x -= 100;
		i += 100;
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		printf("panquesito\n");
		x -= 100;
		i -= 100;
	}
}

void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	while (++x < i)
	{
		int y = 0;
		while(++y < 100)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
	}
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 10000, 5000);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_key_hook(mlx, &my_keyhook, mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
