#include "fdf.h"

void	free_trash(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_and_free(t_vector **map, int row, int fd)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(map[i]);
		i++;
	}
	free(map);
	close(fd);
}

int	close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	free_all(mlx);
	exit(0);
	return (0);
}

void	free_mapper(t_vector **mapper, int height)
{
	int	i;

	i = 0;
	if (!mapper)
		return ;
	while (i < height)
	{
		free(mapper[i]);
		i++;
	}
	free(mapper);
}

void	free_all(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (!mlx)
		return ;
	if (mlx->img)
	{
		mlx_destroy_image(mlx->init_mlx, mlx->img);
	}
	if (mlx->win)
	{
		mlx_destroy_window(mlx->init_mlx, mlx->win);
	}
	if (mlx->mapper)
	{
		free_mapper(mlx->mapper, mlx->map_height);
	}
	if (mlx->init_mlx)
	{
		// mlx_destroy_display(mlx->init_mlx);
		free(mlx->init_mlx);
		mlx->init_mlx = NULL;
	}
	free(mlx);
}
