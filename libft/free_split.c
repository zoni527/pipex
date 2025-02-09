/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:49:57 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/30 11:52:27 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char ***words_ptr)
{
	char	**words;

	words = *words_ptr;
	while (*words)
		free(*(words++));
	free(*words_ptr);
	*words_ptr = NULL;
}
