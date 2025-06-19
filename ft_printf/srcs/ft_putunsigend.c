/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:43:20 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:09:23 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int u)
{
	char	c;
	int		tmp;
	int		count;

	count = 0;
	if (u >= 10)
	{
		tmp = ft_putunsigned(u / 10);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	c = (u % 10) + '0';
	tmp = write(1, &c, 1);
	if (tmp == -1)
		return (-1);
	return (count + 1);
}
