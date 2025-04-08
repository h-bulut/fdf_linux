/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:20:29 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 20:18:04 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_remainder(char *s1)
{
	char	*s5;
	int		i;
	int		j;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
	{
		free(s1);
		return (NULL);
	}
	s5 = malloc((ft_strlenG(s1) - i + 1) * sizeof(char));
	if (!s5)
		return (NULL);
	i++;
	j = 0;
	while (s1[i])
		s5[j++] = s1[i++];
	s5[j] = '\0';
	free(s1);
	return (s5);
}

char	*ft_line(char *s1)
{
	char	*s4;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	s4 = malloc((i + 2) * sizeof(char));
	if (!s4)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		s4[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
		s4[i++] = '\n';
	s4[i] = '\0';
	return (s4);
}

char	*ft_read(int fd, char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 1;
	while (!ft_strchrG(s1) && i > 0)
	{
		i = read(fd, s2, BUFFER_SIZE);
		if (i == -1)
		{
			free(s1);
			free(s2);
			return (NULL);
		}
		s2[i] = '\0';
		s1 = ft_strjoinG(s1, s2);
	}
	free(s2);
	return (s1);
}

char	*get_next_line(int fd)
{
	static char	*s1;
	char		*line;

	if (fd == -42)
	{
		free(s1);
		return(NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s1 = ft_read(fd, s1);
	if (!s1 || !*s1)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	line = ft_line(s1);
	s1 = ft_remainder(s1);
	return (line);
}
