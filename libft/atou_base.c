/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atou_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:27:45 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:15:51 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	atou_base(const char *str, const char *base)
{
	unsigned int	num;
	unsigned int	prev;
	unsigned int	base_len;

	if (!str || !base || !*str || !*base)
		return (UINT_MAX);
	if (contains_duplicate_char(base))
		return (UINT_MAX);
	str = skip_whitespace(str);
	base_len = ft_strlen(base);
	prev = 0;
	num = 0;
	while (ft_strchr(base, *str))
	{
		num = num * base_len + char_index(base, *(str++));
		if (num < prev)
			return (UINT_MAX);
		prev = num;
	}
	return (num);
}
