/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:20:33 by hbulut            #+#    #+#             */
/*   Updated: 2025/03/21 16:41:53 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenG(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchrG(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoinG(char *s1, char *s2)
{
	char	*p;
	size_t	m;
	size_t	j;

	j = -1;
	m = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	p = malloc((ft_strlenG(s1) + ft_strlenG(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[++j] != '\0')
		p[j] = s1[j];
	while (s2[m] != '\0')
		p[j++] = s2[m++];
	p[j] = '\0';
	free(s1);
	return (p);
}
