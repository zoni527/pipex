/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:58:39 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/20 10:43:08 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *nptr)
{
	long int	num;
	long int	sign;

	if (!*nptr)
		return (0);
	num = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + *(nptr++) - '0';
		if (num < 0 && sign > 0)
			return (LONG_MAX);
		if (num < 0 && sign < 0)
			return (LONG_MIN);
	}
	return (sign * num);
}
