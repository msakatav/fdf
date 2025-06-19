/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 07:43:59 by root              #+#    #+#             */
/*   Updated: 2025/06/20 08:27:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloc(void **old, int old_size, int new_size)
{
	void	**new_arr;
	int		i;

	new_arr = malloc(sizeof(void *) * new_size);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_arr[i] = old[i];
		i++;
	}
	free(old);
	return (new_arr);
}
