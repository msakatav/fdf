/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:14 by msakata           #+#    #+#             */
/*   Updated: 2025/05/15 00:10:19 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include "stdarg.h"

int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putptr(void *p);
int	ft_putnbr(int n);
int	ft_putunsigned(unsigned int u);
int	ft_puthex_lower(unsigned int lower_x);
int	ft_puthex_upper(unsigned int upper_x);
int	ft_printf(const char *format, ...);

#endif