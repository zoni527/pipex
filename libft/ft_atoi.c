/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:58:39 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:52:31 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	num;
	int		sign;

	if (!*nptr)
		return (0);
	num = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + *(nptr++) - '0';
		if (num < 0 && sign > 0)
			return ((int)LONG_MAX);
		if (num < 0 && sign < 0)
			return ((int)LONG_MIN);
	}
	return (sign * (int)num);
}
