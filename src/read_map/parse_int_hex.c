/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:19:19 by root              #+#    #+#             */
/*   Updated: 2025/06/20 08:21:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_parse_int_hex(const char *str, int *z, int *color)
{
	int i = 0;
	int sign = 1;
	*z = 0;
	*color = 0;

	while (ft_isspace(str[i])) i++;

	if (str[i] == '-') { sign = -1; i++; }

	while (ft_isdigit(str[i]))
	{
		*z = *z * 10 + (str[i] - '0');
		i++;
	}
	*z *= sign;

	if (str[i] != ',')
		return 0;
	i++;

	*color = 0;
	while (str[i]) {
		char c = str[i];
		int v;
		if ('0' <= c && c <= '9') v = c - '0';
		else if ('a' <= c && c <= 'f') v = c - 'a' + 10;
		else if ('A' <= c && c <= 'F') v = c - 'A' + 10;
		else break;
		*color = (*color << 4) | v;
		i++;
	}
	return 2;
}