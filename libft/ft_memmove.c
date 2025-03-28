/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:08:24 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/25 11:04:45 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	*k;

	if (!dst && !src)
		return (dst);
	if (dst <= src)
	{
		k = ft_memcpy(dst, src, len);
		return (k);
	}
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (len--)
		d[len] = s[len];
	return (d);
}
