/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:43:00 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:09:46 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_upper(unsigned int upper_x)
{
	char		c;
	int			tmp;
	int			count;

	count = 0;
	if (upper_x >= 16)
	{
		tmp = ft_puthex_upper(upper_x / 16);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	c = "0123456789ABCDEF"[upper_x % 16];
	tmp = write(1, &c, 1);
	if (tmp == -1)
		return (-1);
	return (count + 1);
}
