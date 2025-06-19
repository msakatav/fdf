/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:55 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:09:51 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_lower(unsigned int lower_x)
{
	char		c;
	int			tmp;
	int			count;

	count = 0;
	if (lower_x >= 16)
	{
		tmp = ft_puthex_lower(lower_x / 16);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	c = "0123456789abcdef"[lower_x % 16];
	tmp = write(1, &c, 1);
	if (tmp == -1)
		return (-1);
	return (count + 1);
}
