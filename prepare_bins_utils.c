/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:01:12 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 10:01:55 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * This function is needed to stop split from splitting within single quoted
 * blocks of text which will be split into their own variables and then trimmed
 */
void	replace_space_within_single_quotes_with_del(char *str)
{
	if (!str)
		return ;
	str = ft_strchr(str, '\'');
	while (str)
	{
		str++;
		while (*str && *str != '\'')
		{
			if (*str == ' ')
				*str = 127;
			str++;
		}
		if (*str == '\'')
			str++;
		if (*str == '\0')
			return ;
		str = ft_strchr(str, '\'');
	}
}

/**
 * Trim away single quotes from all strings within arr
 */
void	trim_single_quotes(t_ppx *d, char *arr[], char *str)
{
	char	*temp;
	int		i;

	if (!arr || !arr[0])
		return ;
	i = -1;
	while (arr[++i])
	{
		if (ft_strchr(arr[i], '\''))
		{
			temp = arr[i];
			arr[i] = ft_strtrim(arr[i], "'");
			if (!arr[i])
			{
				free(str);
				free(temp);
				clean_exit(d, "couldn't alloc in ft_strtrim", NULL, E_ALLOC);
			}
			free(temp);
		}
	}
}

void	replace_del_with_space(char *arr[])
{
	if (!arr)
		return ;
	while (*arr)
		replace_char(*(arr++), 127, ' ');
}
