#include "fdf.h"

t_vector	**initialize_map(int row, int col)
{
	int			i;
	t_vector	**map;

	map = malloc(row * sizeof(t_vector *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < row)
	{
		map[i] = malloc(col * sizeof(t_vector));
		if (!map[i])
		{
			while (i--)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

// int	digit(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] == '-' || str[0] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int 	parse(char *value, t_vector *point, int k, int t, t_mlx *mlx)
{
	int		z;
	char	**color_z;

	z = 0;
	mlx->cod_error == -1;
	color_z = ft_split(value, ',');
	point->x = t * mlx->scale + (MARGINE + mlx->map_height * mlx->scale + 20) / 2;
	point->y = k * mlx->scale;
	point->z = ft_atoi(color_z[0]) * max(mlx->map_width / mlx->map_height, mlx->map_height / mlx->map_width);
	if (color_z[1])
	{
		point->color = ft_atoi_base(color_z[1], 16);
		mlx->flag = 1;
	}
	else
		point->color = 0xFFFFFF;
	free_trash(color_z);
}

void	process_line(char *line, int k, t_vector **map, t_mlx *mlx)
{
	char	**values;
	int		t;

	values = ft_split(line, ' ');
	t = 0;
	while (values[t] && t < mlx->map_width)
	{
		parse(values[t], &map[k][t], k, t, mlx);
		t++;
	}
	free_trash(values);
}

int	get_map_values(int fd, t_vector **map, t_mlx *mlx)
{
	char	*line;
	char	*p;
	int		k;

	line = NULL;
	p = get_next_line(fd);
	line = ft_strtrim(p, "\n");
	free(p);
	k = 0;
	mlx->flag = 0;
	while (line && k < mlx->map_height)
	{
		process_line(line, k, map, mlx);
		free(line);
		p = get_next_line(fd);
		line = ft_strtrim(p, "\n");
		free(p);
		k++;
	}
	free(line);
	return (mlx->flag);
}

t_vector	**read_map(char *filename, t_mlx *mlx)
{
	int	fd;
	int	flag;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	mlx->mapper = initialize_map(mlx->map_height, mlx->map_width);
	if (!mlx->mapper)
	{
		close_and_free(mlx->mapper, mlx->map_height, fd);
		return (NULL);
	}
	flag = get_map_values(fd, mlx->mapper, mlx);
	if (flag == 0)
		assign_colors(mlx);
	get_next_line(-42);
	close(fd);
	return (mlx->mapper);
}


