/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:27 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/18 19:04:18 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	validate_base(const char *base);

int	ft_putnbr_base(unsigned int nbr, const char *base)
{
	int	base_len;
	int	counter;
	int	mod;

	counter = 0;
	base_len = validate_base(base);
	if (base_len <= 1)
		return (-1);
	if (nbr >= (unsigned int)base_len)
		counter += ft_putnbr_base(nbr / base_len, base);
	mod = nbr % base_len;
	counter += ft_putchar(base[mod]);
	return (counter);
}

static int	validate_base(const char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		j = i;
		while (base[++j])
			if (base[i] == base[j])
				return (-1);
		i++;
	}
	return (i);
}
