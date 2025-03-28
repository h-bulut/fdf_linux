
#include "fdf.h"

int	check_arg(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (ft_strncmp(argv + len - 5, "/.fdf", 5) == 0)
	{
		return (2);
	}
	else if (ft_strncmp(argv + len - 4, ".fdf", 4) == 0)
	{
		return (1);
	}
	return (0);
}

int	check_file(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("no argument\n"); // write
		exit(1);
	}
	else if (check_arg(argv[1]) == 0)
	{
		printf("false file\n"); // write
		exit(1);
	}
	else if (check_arg(argv[1]) == 2)
	{
		printf("ignore file\n"); // write
		exit(1);
	}
	printf("okey_file %s\n", argv[1]); // write
	return (0);
}

int	ft_wordcount(char const *s, char c)
		// get_next_line okuduğu değerler sonda boşluk kalıyor
{
	int count;
	int i;

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

int	count_column(char *file_name)
{
	int		fd;
	int		count;
	char	*one_line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	one_line = get_next_line(fd);
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
	while ((line = get_next_line(fd)) != NULL)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

void	rec_map_control(char *file_name)
{
	int		fd;
	char	*one_line;
	int		k;
	int		j;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		exit(1);
	}
	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		exit(1);
	}
	k = ft_wordcount(one_line, ' ');
	while (one_line)
	{
		j = ft_wordcount(one_line, ' ');
		if (j != k)
		{
			printf("map problem\n");
			free(one_line);
			close(fd);
			exit(1);
		}
		free(one_line);
		one_line = get_next_line(fd);
	}
	close(fd);
	printf("rectanguler and square map\n");
}

t_vector	**read_map(char *filename, int row, int col, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		k;
	char	**values;
	int		t;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	k = 0;
	t_vector **map = malloc(row * sizeof(t_vector *));// Yükseklik kadar satır tahsis et
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	char *p = get_next_line(fd);
	line = ft_strtrim(p, "\n ");
	free(p);
	while (line && k < row)
	{
		// `map[k]` için genişlik kadar bellek ayırıyoruz
		map[k] = malloc(col * sizeof(t_vector));
		if (!map[k])
		{
			// Bellek tahsisi başarısızsa önceki belleği serbest bırak
			while (--k >= 0)
				free(map[k]);
			free(map);
			close(fd);
			return (NULL);
		}
		values = ft_split(line, ' ');
		t = 0;
		while (values[t])
		{
			if (t < col)
			{
				map[k][t].x = k;// 20px aralıklarla yerleştir (örnek)
				map[k][t].y = t;// Her satır için y değeri
				map[k][t].z = ft_atoi(values[t]); // Haritadan okunan yükseklik
			}
			t++;
		}
		// `values` ve `line` belleğini serbest bırak
		for (int i = 0; values[i]; i++)
			free(values[i]);
		free(values);
		free(line);
		char *p = get_next_line(fd);
		line = ft_strtrim(p, "\n ");
		k++;
	}
	printf("(%d, %d, %d)\n", map[0][0].x, map[0][0].y, map[0][0].z);
	printf("(%d, %d, %d)\n", map[0][1].x, map[0][1].y, map[0][1].z);
	printf("(%d, %d, %d)\n", map[0][2].x, map[0][2].y, map[0][2].z);
	printf("(%d, %d, %d)\n", map[1][0].x, map[1][0].y, map[1][0].z);
	printf("(%d, %d, %d)\n", map[1][1].x, map[1][1].y, map[1][1].z);
	printf("(%d, %d, %d)\n", map[1][2].x, map[1][2].y, map[1][2].z);
	mlx->mapper = map;
	close(fd);
	return (map);
}

int	main(int argc, char **argv)
{
	t_mlx	*my_mlx;
	int		row;
	int		col;

	my_mlx = malloc(sizeof(t_mlx));
	if (!my_mlx)
		return (1);
	my_mlx->init_mlx = mlx_init();
	check_file(argc, argv);
	rec_map_control(argv[1]);
	row = count_lines(argv[1]);
	col = count_column(argv[1]);
	printf("lines : %d\n", row);
	printf("column : %d\n", col);
	read_map(argv[1], row, col, my_mlx);
}
