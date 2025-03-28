/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasretdenizbulut <hasretdenizbulut@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:51:28 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/28 21:27:37 by hasretdeniz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t	count, size_t	size)
{
	unsigned char	*p ;

	p = (unsigned char *)malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return ((void *)p);
}
