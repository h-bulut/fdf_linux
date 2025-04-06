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

void	free_trash2(char **arr)
{
	int i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	parse(char *value, t_vector *point, int k, int t, t_mlx *mlx, int *flag)
{
	int		z;
	char	**color_z;

	z= 0;
	color_z = ft_split(value, ',');
	if (!ft_atoi_strict(color_z[0], &z))
		mlx->tag = 1;
	point->x = t * mlx->scale + (MARGINE + mlx->map_height * mlx->scale + 20)
		/ 2;
	point->y = k * mlx->scale;
	point->z = z * max(mlx->map_width / mlx->map_height, mlx->map_height
			/ mlx->map_width);
	if (color_z[1])
	{
		point->color = ft_atoi_base(color_z[1], 16);
		*flag = 1;
	}
	else
		point->color = 0xFFFFFF;
	free_trash(color_z);
}

void	process_line(char *line, int k, t_vector **map, t_mlx *mlx, int *flag)
{
	char	**values;
	int		t;

	values = ft_split(line, ' ');
	t = 0;
	while (values[t] && t < mlx->map_width)
	{
		parse(values[t], &map[k][t], k, t, mlx, flag);
		t++;
	}
	free_trash2(values);
}

int	get_map_values(int fd, t_vector **map, t_mlx *mlx)
{
	char	*line;
	char	*p;
	int		k;
	int		flag;

	line = NULL;
	p = get_next_line(fd);
	line = ft_strtrim(p, "\n");
	free(p);
	k = 0;
	flag = 0;
	while (line && k < mlx->map_height)
	{
		process_line(line, k, map, mlx, &flag);
		free(line);
		p = get_next_line(fd);
		line = ft_strtrim(p, "\n");
		free(p);
		k++;
	}
	free(line);
	return (flag);
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
	close(fd);
	return (mlx->mapper);
}
