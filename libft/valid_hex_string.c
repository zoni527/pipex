/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_hex_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:20:25 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:52:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	valid_hex_string(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	str = skip_whitespace(str);
	if (*str != '0' || !(*(str + 1) == 'x' || *(str + 1) == 'X')
		|| *(str + 2) == '\0')
		return (0);
	str += 2;
	i = 0;
	while (str[i] && (ft_strchr(HEX_BASE_UPPER_CASE, str[i])
			|| ft_strchr(HEX_BASE_LOWER_CASE, str[i])))
		i++;
	str = skip_whitespace(&str[i]);
	if (!*str)
		return (1);
	return (0);
}
