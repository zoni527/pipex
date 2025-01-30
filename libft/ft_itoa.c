/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:48:20 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 12:41:23 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Use the calculated amount of digits and a possible minus sign to create the
// string memory with malloc, store the sign, write backwards and insert digits
// from the right end of the number using modulo times sign, shrink the number
// by dividing by ten. If the number is negative the last element will be the
// minus sign, the last remaining digit otherwise. Return string and enjoy!

char	*ft_itoa(int n)
{
	char	*str;
	int		str_len;
	int		sign;

	str_len = ft_int_digits(n);
	sign = 1;
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
