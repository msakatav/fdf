/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:19:19 by root              #+#    #+#             */
/*   Updated: 2025/06/22 13:47:36 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_map.h"
#include "ft_printf.h"

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	parse_decimal(const char *str, int *i)
{
	int	val;

	val = 0;
	while (ft_isdigit(str[*i]))
	{
		val = val * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (val);
}

static int	parse_hex(const char *str, int *i)
{
	int	val;
	int	v;

	val = 0;
	while (str[*i])
	{
		if ('0' <= str[*i] && str[*i] <= '9')
			v = str[*i] - '0';
		else if ('a' <= str[*i] && str[*i] <= 'f')
			v = str[*i] - 'a' + 10;
		else if ('A' <= str[*i] && str[*i] <= 'F')
			v = str[*i] - 'A' + 10;
		else
			break ;
		val = (val << 4) | v;
		(*i)++;
	}
	return (val);
}

int	ft_parse_int_hex(const char *str, int *z, int *color)
{
    int	i;
    int	sign;

    i = 0;
    *z = 0;
    *color = 0xFFFFFF; // デフォルト色は白

    while (ft_isspace(str[i]))
        i++;
    sign = parse_sign(str, &i);
    *z = parse_decimal(str, &i) * sign;
    if (str[i] != ',')
        return (0);
    i++;
    // 0x または 0X をスキップ
    if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
        i += 2;
    *color = parse_hex(str, &i);
    return (2);
}
