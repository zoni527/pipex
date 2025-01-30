/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:32:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/26 11:03:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_c(const char **format_str_ptr, va_list ap)
{
	unsigned char	c;

	c = (unsigned char)va_arg(ap, int);
	*format_str_ptr = ft_strchr(*format_str_ptr, 'c') + 1;
	return (ft_putchar(c));
}
