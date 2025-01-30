/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:25:28 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:49:40 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*char_ptr;
	size_t		i;

	char_ptr = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (char_ptr[i] == c)
			return ((void *)(char_ptr + i));
		i++;
	}
	return (NULL);
}
