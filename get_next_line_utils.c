/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 04:22:08 by msakata           #+#    #+#             */
/*   Updated: 2025/06/16 20:51:38 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_g(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_g(const char *src)
{
	char	*cpy;
	size_t	i;
	size_t	len;

	len = ft_strlen_g(src);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strappend_g(char *s1, const char *s2, size_t i, size_t j)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen_g(s1);
	len2 = ft_strlen_g(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_strchr_g(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr_g(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s || start >= ft_strlen_g(s))
		return (ft_strdup_g(""));
	if (ft_strlen_g(s) - start < len)
		len = ft_strlen_g(s) - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
