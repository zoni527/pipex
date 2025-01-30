/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:37:25 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:51:03 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*char_ptr1;
	const unsigned char	*char_ptr2;
	size_t				i;

	if (n == 0)
		return (0);
	char_ptr1 = (const unsigned char *)s1;
	char_ptr2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (char_ptr1[i] != char_ptr2[i])
			return ((int)(char_ptr1[i] - char_ptr2[i]));
		i++;
	}
	return (0);
}
