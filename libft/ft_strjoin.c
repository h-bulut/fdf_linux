/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasretdenizbulut <hasretdenizbulut@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:41:00 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/28 16:38:20 by hasretdeniz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	m;
	size_t	j;

	j = 0;
	m = 0;
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[j] != '\0')
	{
		p[j] = s1[j];
		j++;
	}
	while (s2[m] != '\0')
	{
		p[j] = s2[m];
		m++;
		j++;
	}
	p[j] = '\0';
	return (p);
}
