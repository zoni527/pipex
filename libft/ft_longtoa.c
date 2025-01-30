/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:48:20 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/28 16:08:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_longtoa(long int n)
{
	char	*str;
	int		str_len;
	int		sign;

	sign = 1;
	str_len = ft_long_digits(n);
	if (n < 0)
	{
		str_len++;
		sign = -1;
	}
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	while (--str_len)
	{
		str[str_len] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	else
		str[0] = (n % 10) * sign + '0';
	return (str);
}
