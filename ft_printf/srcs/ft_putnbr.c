/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:43:05 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:09:42 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_re(int n)
{
	char	c;
	int		count;
	int		tmp;

	count = 0;
	if (n >= 10)
	{
		tmp = ft_putnbr_re(n / 10);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	c = (n % 10) + '0';
	tmp = write(1, &c, 1);
	if (tmp == -1)
		return (-1);
	return (count + 1);
}

int	ft_putnbr(int n)
{
	int	count;
	int	tmp;

	count = 0;
	if (n == -2147483648)
		return (write (1, "-2147483648", 11));
	if (n < 0)
	{
		n = -n;
		if (write(1, "-", 1) == -1)
			return (-1);
		count++;
	}
	tmp = ft_putnbr_re(n);
	if (tmp == -1)
		return (-1);
	return (count + tmp);
}
