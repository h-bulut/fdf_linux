
#include "fdf.h"

int	handle_key(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		free_all(mlx);
		exit(0);
	}
	return (0);
}

t_mlx	*init_graphics(void)
{
	t_mlx	*my_mlx;

	my_mlx = malloc(sizeof(t_mlx));
	if (!my_mlx)
		return (NULL);
	my_mlx->init_mlx = mlx_init();
	if (!my_mlx->init_mlx)
	{
		free(my_mlx);
		return (NULL);
	}
	my_mlx->mapper = NULL;
	return (my_mlx);
}

int	create_window_and_image(t_mlx *my_mlx)
{
	my_mlx->win = mlx_new_window(my_mlx->init_mlx, WIDTH, HEIGHT, "wireframe");
	if (!my_mlx->win)
	{
		free(my_mlx);
		return (0);
	}
	my_mlx->img = mlx_new_image(my_mlx->init_mlx, WIDTH, HEIGHT);
	if (!my_mlx->img)
	{
		mlx_destroy_window(my_mlx->init_mlx, my_mlx->win);
		free(my_mlx);
		return (0);
	}
	my_mlx->data_addr = mlx_get_data_addr(my_mlx->img, &my_mlx->bpp,
			&my_mlx->size_line, &my_mlx->endian);
	if (!my_mlx->data_addr)
	{
		mlx_destroy_image(my_mlx->init_mlx, my_mlx->img);
		mlx_destroy_window(my_mlx->init_mlx, my_mlx->win);
		free(my_mlx);
		return (0);
	}
	return (1);
}

t_mlx	*grafic_method(char *filename)
{
	t_mlx *my_mlx;

	my_mlx = init_graphics();
	if (!my_mlx)
		return (NULL);
	if (!create_window_and_image(my_mlx))
		return (NULL);
	return (my_mlx);
}