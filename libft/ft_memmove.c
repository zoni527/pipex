/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:58:46 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:34:55 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_char_ptr;
	const char	*src_char_ptr;
	size_t		i;

	if (n == 0)
		return (dest);
	dest_char_ptr = (char *)dest;
	src_char_ptr = (const char *)src;
	i = 0;
	if (src_char_ptr < dest_char_ptr)
		while (n-- > 0)
			dest_char_ptr[n] = src_char_ptr[n];
	else
	{
		while (i < n)
		{
			dest_char_ptr[i] = src_char_ptr[i];
			i++;
		}
	}
	return (dest);
}
