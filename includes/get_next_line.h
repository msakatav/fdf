/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 04:05:24 by msakata           #+#    #+#             */
/*   Updated: 2025/06/16 20:52:36 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strappend_g(char *s1, const char *s2, size_t i, size_t j);
char	*ft_strchr_g(const char *s, int c);
char	*ft_substr_g(char *s, unsigned int start, size_t len);
char	*ft_strdup_g(const char *src);
size_t	ft_strlen_g(const char *s);

#endif
