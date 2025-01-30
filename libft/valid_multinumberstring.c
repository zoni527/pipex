/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_multinumberstring.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:58:28 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/15 08:58:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	valid_multinumberstring(char *str)
{
	int	sign;

	if (*str == '\0')
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		sign = 1;
		if ((*str == '-' || *str == '+') && *(str + 1))
			if (*(str++) == '-')
				sign = -1;
		if (!ft_isdigit(*str))
			return (0);
		if ((sign > 0 && ft_atol(str) > INT_MAX)
			|| (sign < 0 && ft_atol(str) > -(long)INT_MIN))
			return (0);
		while (ft_isdigit(*str))
			str++;
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
	}
	return (1);
}
