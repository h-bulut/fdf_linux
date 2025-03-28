/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:06:52 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/29 16:49:38 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*k;

	i = 0;
	p = (unsigned char *)s1;
	k = (unsigned char *)s2;
	if (!n)
		return (0);
	while (i < n && p[i] == k[i])
		i++;
	if (i == n)
		return (0);
	return (p[i] - k[i]);
}
