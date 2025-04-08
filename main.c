#include "fdf.h"

int	main(int argc, char **argv)
{
	t_mlx	*my_mlx;

	check_file(argc, argv);
	rec_map_control(argv[1]);
	my_mlx = grafic_method(argv[1]);
	my_mlx->map_height = count_lines(argv[1]);
	my_mlx->map_width = count_column(argv[1]);
	my_mlx->scale = (int)sqrt((WIDTH - MARGINE) * (HEIGHT - MARGINE)
			/ (my_mlx->map_height * my_mlx->map_width));
	my_mlx->mapper = read_map(argv[1], my_mlx);
	
	if (!my_mlx->mapper)
	{
		free_all(my_mlx);
		return (1);
	}
	handle_projection(my_mlx->map_height, my_mlx->map_width, my_mlx);
	handle_bresenham(my_mlx->map_height, my_mlx->map_width, my_mlx);
	mlx_put_image_to_window(my_mlx->init_mlx, my_mlx->win, my_mlx->img, 0, 0);
	mlx_key_hook(my_mlx->win, handle_key, my_mlx);
	mlx_hook(my_mlx->win, 17, 0, close_window, my_mlx);
	mlx_loop(my_mlx->init_mlx);
	return (0);
}
