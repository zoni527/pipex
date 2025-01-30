/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:19:54 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/28 16:01:25 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int n)
{
	char	*str;
	size_t	str_len;
	int		mod;

	str_len = ft_uint_digits(n);
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	while (str_len--)
	{
		mod = n % 10;
		str[str_len] = mod + '0';
		n /= 10;
	}
	return (str);
}
