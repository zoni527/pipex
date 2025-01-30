/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:32:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/26 10:50:23 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_u(const char **format_str_ptr, va_list ap)
{
	unsigned int	u;
	char			*u_str;
	int				characters_written;

	u = va_arg(ap, unsigned int);
	*format_str_ptr = ft_strchr(*format_str_ptr, 'u') + 1;
	u_str = ft_utoa(u);
	if (!u_str)
		return (-1);
	characters_written = ft_putstr(u_str);
	free(u_str);
	return (characters_written);
}
