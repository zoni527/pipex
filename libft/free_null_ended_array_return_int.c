/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_null_ended_array_return_int.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:02:38 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/20 10:56:03 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_null_ended_array_return_int(void ***ptr_to_array, int num)
{
	free_null_ended_array(ptr_to_array);
	return (num);
}
