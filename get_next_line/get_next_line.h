/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuonen <zuonen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:01:03 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/06 21:17:26 by zuonen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlenG(const char *s);
int		ft_strchrG(const char *s);
char	*ft_read(int fd, char *s1);
char	*ft_remainder(char *s1);
char	*ft_line(char *s1);
char	*get_next_line(int fd);
char	*ft_strjoinG(char *s1, char *s2);

#endif
