/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_duplicate_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:30 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:13:50 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains_duplicate_char(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_strchr(str + 1, *str))
			return (1);
		str++;
	}
	return (0);
}
