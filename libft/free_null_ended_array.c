/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_null_ended_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:02:38 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/20 10:54:18 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_null_ended_array(void ***ptr_to_array)
{
	void	**null_ended_array;

	null_ended_array = *ptr_to_array;
	while (*null_ended_array != NULL)
		free(*(null_ended_array++));
	free(*(null_ended_array));
	free(*ptr_to_array);
	*ptr_to_array = NULL;
}
