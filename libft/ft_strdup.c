/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:10:01 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/25 15:22:39 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		j;

	j = ft_strlen(s1);
	p = malloc((j + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, j + 1);
	return (p);
}
