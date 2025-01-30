/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:24:24 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 11:15:50 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*char_ptr;
	size_t			i;

	char_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		char_ptr[i++] = 0;
}
