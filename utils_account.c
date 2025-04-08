
#include "fdf.h"

int	count_column(char *file_name)
{
	int		fd;
	int		count;
	char	*one_line;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	line = get_next_line(fd);
	one_line = ft_strtrim(line, "\n");
	free(line);
	if (!one_line)
	{
		close(fd);
		return (0);
	}
	count = ft_wordcount(one_line, ' ');
	free(one_line);
	close(fd);
	return (count);
}

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

void	find_min_max(t_mlx *mlx)
{
	int 	y;
	int 	x;

	mlx->min_z = INT_MAX;
	mlx->max_z = INT_MIN;
	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			if (mlx->mapper[y][x].z < mlx->min_z)
				mlx->min_z = mlx->mapper[y][x].z;
			if (mlx->mapper[y][x].z > mlx->max_z)
				mlx->max_z = mlx->mapper[y][x].z;
			x++;
		}
		y++;
	}
}
