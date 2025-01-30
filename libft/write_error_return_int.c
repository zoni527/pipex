/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error_return_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:23:40 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/19 11:25:31 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_error_return_int(char *error_message, int return_value)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putchar('\n');
	return (return_value);
}
