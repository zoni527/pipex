/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:07:08 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 12:32:04 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	combined_len;

	combined_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc((combined_len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	joined_str[0] = '\0';
	ft_strlcat(joined_str, s1, combined_len + 1);
	ft_strlcat(joined_str, s2, combined_len + 1);
	return (joined_str);
}
