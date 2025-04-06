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
		write(1, "no argument\n", 13);
		exit(1);
	}
	else if (check_arg(argv[1]) == 0)
	{
		write(1, "false file\n", 12);
		exit(1);
	}
	else if (check_arg(argv[1]) == 2)
	{
		write(1, "ignore file\n", 13);
		exit(1);
	}
	write(1, "okey_file\n", 12);
	return (0);
}

void	check_line_integrity(int fd, int k)
{
	char	*one_line;
	int		j;

	one_line = get_next_line(fd);
	while (one_line)
	{
		j = ft_wordcount(one_line, ' ');
		if (j != k)
		{
			write(1, "map problem\n", 13);
			free(one_line);
			close(fd);
			exit(1);
		}
		free(one_line);
		one_line = get_next_line(fd);
	}
}

void	check_map_integrity(int fd, int k)
{
	char	*one_line;
	int		j;

	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		exit(1);
	}
	j = ft_wordcount(one_line, ' ');
	if (j != k)
	{
		write(1, "map problem\n", 13);
		free(one_line);
		close(fd);
		exit(1);
	}
	free(one_line);
	check_line_integrity(fd, k);
}

void	rec_map_control(char *file_name)
{
	int		fd;
	char	*one_line;
	int		k;

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
	free(one_line);
	check_map_integrity(fd, k);
	close(fd);
	write(1, "rectangular and square map\n", 29);
}
