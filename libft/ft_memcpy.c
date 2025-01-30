/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:43:45 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:32:50 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_char_ptr;
	const char	*src_char_ptr;
	size_t		i;

	if (n == 0 || src == dest)
		return (dest);
	dest_char_ptr = (char *)dest;
	src_char_ptr = (const char *)src;
	i = 0;
	while (i < n)
	{
		dest_char_ptr[i] = src_char_ptr[i];
		i++;
	}
	return (dest);
}
