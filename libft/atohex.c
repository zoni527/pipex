/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atohex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:45:40 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:59:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	atohex(const char *str)
{
	unsigned int	hex;
	unsigned int	i;
	unsigned int	prev;

	if (!valid_hex_string(str))
		return (UINT_MAX);
	str = skip_whitespace(str) + 2;
	prev = 0;
	hex = 0;
	while (*str && (ft_strchr(HEX_BASE_UPPER_CASE, *str)
			|| ft_strchr(HEX_BASE_LOWER_CASE, *str)))
	{
		if (ft_islower(*str))
			i = char_index(HEX_BASE_LOWER_CASE, *str);
		else
			i = char_index(HEX_BASE_UPPER_CASE, *str);
		hex = hex * 16 + i;
		if (hex < prev)
			return (UINT_MAX);
		prev = hex;
		str++;
	}
	return (hex);
}
