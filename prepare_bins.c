/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:03:24 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/12 18:13:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prepare_bins(t_ppx *data)
{
	char	*str;

	str = ft_strdup(data->argv[2]);
	if (!str)
		clean_exit(data, "couldn't malloc in ft_strdup", NULL, E_ALLOC);
	replace_space_within_single_quotes_with_del(str);
	assign_bin(data, 0, str);
	trim_single_quotes(data, data->bin[0]);
	replace_del_with_space(data->bin[0]);
	free(str);
	str = ft_strdup(data->argv[3]);
	if (!str)
		clean_exit(data, "couldn't malloc in ft_strdup", NULL, E_ALLOC);
	replace_space_within_single_quotes_with_del(str);
	assign_bin(data, 1, str);
	trim_single_quotes(data, data->bin[1]);
	replace_del_with_space(data->bin[1]);
	free(str);
}

/**
 * Splits binary into binary name and arguments, attempts to look for binary
 * in PATH, if not found leaves binary name as is.
 * If binary exists in the current directory or name already contains the path
 * to a valid binary don't search PATH.
 */
void	assign_bin(t_ppx *data, int index, const char *bin_name)
{
	if (!*bin_name)
	{
		data->bin[index] = ft_calloc(2, sizeof(char *));
		if (!data->bin[index])
			clean_exit(data, "couldn't calloc in assign_bin", NULL, E_ALLOC);
		data->bin[index][0] = ft_strdup(bin_name);
		if (!data->bin[index][0])
			clean_exit(data, "couldn't alloc in ft_strdup", NULL, E_ALLOC);
		return ;
	}
	data->bin[index] = ft_split(bin_name, ' ');
	if (!data->bin[index])
		clean_exit(data, "couldn't alloc in split", NULL, E_ALLOC);
	if (access(data->bin[index][0], F_OK | X_OK) == 0)
		return ;
	search_for_bin(data, index);
}

void	search_for_bin(t_ppx *data, int index)
{
	char	*bin;
	int		i;

	i = -1;
	while (data->path_split[++i])
	{
		bin = ft_strjoin(data->path_split[i], data->bin[index][0]);
		if (!bin)
			clean_exit(data, "couldn't alloc in ft_strjoin", NULL, E_ALLOC);
		if (access(bin, F_OK) == 0)
		{
			free(data->bin[index][0]);
			data->bin[index][0] = bin;
			return ;
		}
		free(bin);
	}
}
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
void	trim_single_quotes(t_ppx *data, char *arr[])
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
			arr[i] = ft_strtrim(arr[i],"'");
			if (!arr[i])
			{
				free(temp);
				perror_clean_exit(data, "pipex", E_ALLOC);
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
