/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ptr_return_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:52:18 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/19 14:11:39 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_ptr_return_int(void **ptr_to_ptr, int i)
{
	free(*ptr_to_ptr);
	*ptr_to_ptr = NULL;
	return (i);
}
