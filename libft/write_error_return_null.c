/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error_return_null.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:49:28 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/19 13:50:56 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*write_error_return_null(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	return (NULL);
}
