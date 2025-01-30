/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:10:05 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:14:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*char_ptr;
	size_t			i;

	char_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		char_ptr[i++] = (unsigned char)c;
	return (s);
}
