/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:15:53 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/25 15:36:35 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		k;

	k = ft_strlen(s);
	if (s[k] == (char)c)
		return ((char *)s + k);
	while (k >= 0)
	{
		if (s[k] == (char)c)
			return ((char *)s + k);
		k--;
	}
	return (NULL);
}
