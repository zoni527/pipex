/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:27:47 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/27 11:29:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return ((char *)str);
}
