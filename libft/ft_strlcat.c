/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasretdenizbulut <hasretdenizbulut@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:10:47 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/28 16:38:26 by hasretdeniz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	p;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	p = 0;
	if (dstsize < i)
		return (dstsize + j);
	while (p < j && dstsize > (i + p + 1))
	{
		dst[i + p] = src[p];
		p++;
	}
	if (i + p < dstsize)
		dst[i + p] = '\0';
	return (i + j);
}
