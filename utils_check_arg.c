/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:25 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 22:37:27 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putstr_fd("no argument\n", 2);
		exit(1);
	}
	else if (check_arg(argv[1]) == 0)
	{
		ft_putstr_fd("false file\n", 2);
		exit(1);
	}
	else if (check_arg(argv[1]) == 2)
	{
		ft_putstr_fd("ignore file\n", 2);
		exit(1);
	}
	return (0);
}

int	check_map_consistency(int fd)
{
	char	*line;
	char	*trimmed;
	int		expected;
	int		current;

	line = get_next_line(fd);
	if (!line)
		return (1);
	trimmed = ft_strtrim(line, "\n");
	expected = ft_wordcount(trimmed, ' ');
	free(line);
	free(trimmed);
	while ((line = get_next_line(fd)))
	{
		trimmed = ft_strtrim(line, "\n");
		current = ft_wordcount(trimmed, ' ');
		free(line);
		free(trimmed);
		if (current != expected)
			return (1);
	}
	return (0);
}

void	rec_map_control(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		exit(1);
	}
	if (check_map_consistency(fd))
	{
		ft_putstr_fd("map problem\n", 2);
		close(fd);
		exit(1);
	}
	close(fd);
}
