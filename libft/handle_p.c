/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:32:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/26 10:59:53 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ptrtoa(uintptr_t ptr_val);
static int	ptr_len(uintptr_t ptr);

int	handle_p(const char **format_str_ptr, va_list ap)
{
	uintptr_t	ptr_val;
	char		*ptr_str;
	int			rval;
	int			characters_written;

	characters_written = 0;
	ptr_val = (uintptr_t)va_arg(ap, void *);
	*format_str_ptr = ft_strchr(*format_str_ptr, 'p') + 1;
	if (!ptr_val)
		return (ft_putstr("(nil)"));
	ptr_str = ptrtoa(ptr_val);
	if (!ptr_str)
		return (-1);
	rval = ft_putstr("0x");
	if (rval < 0)
		return (free_ptr_return_int((void *)(&ptr_str), -1));
	characters_written += rval;
	rval = ft_putstr(ptr_str);
	if (rval < 0)
		return (free_ptr_return_int((void *)(&ptr_str), -1));
	characters_written += rval;
	free(ptr_str);
	return (characters_written);
}

static char	*ptrtoa(uintptr_t ptr_val)
{
	char		*str;
	char		*lookup;
	int			str_len;
	uintptr_t	mod;

	lookup = HEX_BASE_LOWER_CASE;
	str_len = ptr_len(ptr_val);
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	while (str_len--)
	{
		mod = ptr_val % 16;
		str[str_len] = lookup[mod];
		ptr_val /= 16;
	}
	return (str);
}

static int	ptr_len(uintptr_t ptr_val)
{
	int	len;

	if (ptr_val == 0)
		return (1);
	len = 0;
	while (ptr_val != 0)
	{
		len++;
		ptr_val /= 16;
	}
	return (len);
}
