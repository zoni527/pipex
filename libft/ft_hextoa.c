/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:19:54 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/28 15:04:38 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hextoa(unsigned long n, unsigned char mode)
{
	char	*str;
	char	*lookup;
	size_t	str_len;
	int		mod;

	if (mode == 'X')
		lookup = "0123456789ABCDEF";
	else
		lookup = "0123456789abcdef";
	str_len = ft_ulong_hex_digits(n);
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	while (str_len--)
	{
		mod = n % 16;
		str[str_len] = lookup[mod];
		n /= 16;
	}
	return (str);
}
