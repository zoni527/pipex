/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_lowercase.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:32:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/26 10:57:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_hex_lowercase(const char **format_str_ptr, va_list ap)
{
	unsigned int	hex;
	char			*hex_str;
	int				characters_written;

	hex = va_arg(ap, unsigned int);
	*format_str_ptr = ft_strchr(*format_str_ptr, 'x') + 1;
	hex_str = ft_hextoa(hex, 'x');
	if (!hex_str)
		return (-1);
	characters_written = ft_putstr(hex_str);
	free(hex_str);
	return (characters_written);
}
