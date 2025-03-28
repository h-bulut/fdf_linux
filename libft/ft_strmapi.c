/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasretdenizbulut <hasretdenizbulut@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:41:07 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/28 22:17:02 by hasretdeniz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	k;
	size_t	i;

	k = ft_strlen(s);
	p = (char *)malloc((k + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < k)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[k] = '\0';
	return (p);
}
