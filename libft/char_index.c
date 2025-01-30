/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:15:21 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:19:31 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_index(const char *str, int c)
{
	int	i;

	if (!str)
		return (-1);
	if (c == '\0')
		return (ft_strlen(str));
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}
