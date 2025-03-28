/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:40:02 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/29 16:50:25 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)

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

static char	*ft_wordalloc(char const *s, char c, int *i)
{
	char	*word;
	int		len;
	int		j;

	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
		word[j++] = s[(*i)++];
	word[j] = '\0';
	return (word);
}

static void	ft_freeall(char **arrays, int j)
{
	while (j >= 0)
		free(arrays[j--]);
	free(arrays);
}

char	**ft_split(char const *s, char c)
{
	char	**arrays;
	int		i;
	int		j;

	arrays = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!s || !arrays)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			arrays[j] = ft_wordalloc(s, c, &i);
			if (!arrays[j++])
				return (ft_freeall(arrays, j - 1), NULL);
		}
		else
			i++;
	}
	arrays[j] = NULL;
	return (arrays);
}
