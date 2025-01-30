/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:27:46 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/12 12:37:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	const char	*right;
	const char	*left;
	size_t		len;

	if (!*s1)
		return ((char *)ft_calloc(1, sizeof(char)));
	left = s1;
	right = ft_strchr(s1, '\0') - 1;
	while (ft_strchr(set, *left))
		left++;
	while (ft_strrchr(set, *right))
		right--;
	if (left > right)
		return ((char *)ft_calloc(1, sizeof(char)));
	len = ft_strlen(left) - ft_strlen(++right);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, left, len + 1);
	return (str);
}
