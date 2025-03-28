/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <bulutmatematik>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:40:29 by hbulut            #+#    #+#             */
/*   Updated: 2024/10/29 10:18:48 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10 ;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	l;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	l = ft_len(n);
	p = (char *)malloc((l + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[l] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		p[--l] = (n % 10) + '0';
		n = n / 10;
	}
	return (p);
}
