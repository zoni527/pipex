/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:30 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/11 14:28:46 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_char(const char *str, int c)
{
	int	count;

	if (!str)
		return (-1);
	count = 0;
	while (*str)
		if (*(str++) == c)
			count++;
	return (count);
}
