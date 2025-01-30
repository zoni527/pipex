/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:04:49 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/13 15:52:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function uses memmove to combine s1 and s2 and frees both pointers before
// returning the new combined string.
char	*strjoin_and_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	combined_len;
	char	*str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	combined_len = len1 + ft_strlen(s2);
	str = malloc((combined_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, len1);
	ft_memmove(str + len1, s2, combined_len - len1);
	str[combined_len] = '\0';
	free(s1);
	free(s2);
	return (str);
}
