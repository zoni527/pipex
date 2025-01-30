/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:32:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/26 11:00:39 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_s(const char **format_str_ptr, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	*format_str_ptr = ft_strchr(*format_str_ptr, 's') + 1;
	if (!str)
		return (ft_putstr("(null)"));
	return (ft_putstr(str));
}
