/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:43:10 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:09:37 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(uintptr_t ptr)
{
	char	c;
	int		count;
	int		tmp;

	count = 0;
	if (ptr >= 16)
	{
		tmp = ft_puthex(ptr / 16);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	c = "0123456789abcdef"[ptr % 16];
	tmp = write(1, &c, 1);
	if (tmp == -1)
		return (-1);
	return (count + 1);
}

int	ft_putptr(void *p)
{
	uintptr_t	ptr;
	int			tmp;

	if (!p)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	ptr = (uintptr_t)p;
	if (write(1, "0x", 2) == -1)
		return (-1);
	tmp = ft_puthex(ptr);
	if (tmp == -1)
		return (-1);
	return (tmp + 2);
}
