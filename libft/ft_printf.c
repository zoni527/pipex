/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:33:44 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/27 10:12:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	handle_conversion(const char **format_str_ptr, va_list ap, char c);
static char	next_conversion_type(const char *format_str);

// Subfunctions advance the format string and return the amount of characters
// written in the absence of errors or -1 when an error occurs.
int	ft_printf(const char *format_str, ...)
{
	va_list	ap;
	int		counter;
	int		rval;
	char	c;

	if (!format_str)
		return (-1);
	va_start(ap, format_str);
	counter = 0;
	while (*format_str)
	{
		if (*format_str == '%')
		{
			c = next_conversion_type(format_str);
			rval = handle_conversion(&format_str, ap, c);
		}
		else
			rval = ft_putchar(*(format_str++));
		if (rval < 0)
			return (-1);
		counter += rval;
	}
	va_end(ap);
	return (counter);
}

// If no valid conversion is found print the percentage sign, advance the
// format string forward by one and return control back to ft_printf.
static int	handle_conversion(const char **format_str_ptr, va_list ap, char c)
{
	if (c == 'c')
		return (handle_c(format_str_ptr, ap));
	else if (c == 's')
		return (handle_s(format_str_ptr, ap));
	else if (c == 'p')
		return (handle_p(format_str_ptr, ap));
	else if (c == 'd')
		return (handle_d(format_str_ptr, ap));
	else if (c == 'i')
		return (handle_i(format_str_ptr, ap));
	else if (c == 'u')
		return (handle_u(format_str_ptr, ap));
	else if (c == 'x')
		return (handle_hex_lowercase(format_str_ptr, ap));
	else if (c == 'X')
		return (handle_hex_uppercase(format_str_ptr, ap));
	else if (c == '%')
	{
		*format_str_ptr += 2;
		return (ft_putchar('%'));
	}
	else
		return (ft_putchar(*((*format_str_ptr)++)));
}

// The null character is returned if the character after % is not in the set
// of valid conversions.
static char	next_conversion_type(const char *format_str)
{
	if (ft_strchr(CONVERSION_SET, *(++format_str)))
		return (*format_str);
	return ('\0');
}
