/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:51:40 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 12:48:52 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*num_string;
	int		characters_written;

	num_string = ft_itoa(n);
	if (!num_string)
		return (-1);
	characters_written = ft_putstr_fd(num_string, fd);
	free(num_string);
	return (characters_written);
}
