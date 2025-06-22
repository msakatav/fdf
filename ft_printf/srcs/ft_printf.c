/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:42 by msakata           #+#    #+#             */
/*   Updated: 2025/05/18 15:14:12 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_able_format(va_list args, char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (format == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_puthex_lower(va_arg(args, unsigned int)));
	else if (format == 'X')
		return (ft_puthex_upper(va_arg(args, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}

static int	ft_check_format(va_list args, const char **format)
{
	int	count;

	if (**format == '\0')
		return (-1);
	count = ft_check_able_format(args, **format);
	if (count != -1)
		return (count);
	else
		return (ft_putchar('%') + ft_putchar(**format));
}

static int	ft_str_loop(va_list args, const char *format, int count)
{
	int	tmp;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (-1);
			tmp = ft_check_format(args, &format);
			if (tmp == -1)
				return (-1);
			count += tmp;
		}
		else
		{
			tmp = ft_putchar(*format);
			if (tmp == -1)
				return (-1);
			count += tmp;
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	count = ft_str_loop(args, format, count);
	va_end(args);
	return (count);
}
