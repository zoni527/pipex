/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:30:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 10:06:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define INPUT_MSG	"Example use: ./pipex <file1> <cmd1> <cmd2> <file2>"

int	main(int argc, char *argv[], char *envp[])
{
	static t_ppx	data;

	if (argc != 5)
		return (write_error_return_int(INPUT_MSG, 0));
	validate_input(argv);
	setup_data(&data, argc, argv, envp);
	handle_forks(&data);
	cleanup_data(&data);
	waitpid(data.pid[0], NULL, 0);
	waitpid(data.pid[1], &data.wait_status, 0);
	if (WIFEXITED(data.wait_status))
		return (WEXITSTATUS(data.wait_status));
	return (EXIT_SUCCESS);
}

/**
 * Checks whether input has an incorrect amount of quotes as open quotes
 * are not supported
 */
void	validate_input(char *argv[])
{
	while (*argv)
	{
		if (count_char(*argv, '\'') % 2 != 0
			|| count_char(*argv, '\"') % 2 != 0)
		{
			ft_putendl_fd("pipex: invalid amount of quotes in input",
				STDERR_FILENO);
			exit (E_INPUT);
		}
		argv++;
	}
}

/**
 * Looks for path variable, splits path into parts and appends '/' when 
 * necessary to make joining with binary names easier later
 */
void	prepare_path(t_ppx *d)
{
	int		i;

	i = -1;
	while (d->envp[++i])
	{
		if (ft_strnstr(d->envp[i], "PATH=", ft_strlen("PATH=")) == d->envp[i])
		{
			d->path = ft_strchr(d->envp[i], '=') + 1;
			break ;
		}
	}
	if (!d->path)
		clean_exit(d, "couldn't find PATH", NULL, E_NOPATH);
	d->path_split = ft_split(d->path, ':');
	if (!d->path_split)
		clean_exit(d, "couldn't malloc in ft_split", NULL, E_ALLOC);
	append_slash_to_paths(d);
}

/**
 * Goes through all words in path_split and appends '/' to words that lack it
 */
void	append_slash_to_paths(t_ppx *d)
{
	char	*temp;
	int		i;

	i = -1;
	while (d->path_split[++i])
	{
		if (d->path_split[i][ft_strlen(d->path_split[i]) - 1] != '/')
		{
			temp = d->path_split[i];
			d->path_split[i] = ft_strjoin(d->path_split[i], "/");
			if (!d->path_split[i])
			{
				free(temp);
				while (d->path_split[++i])
					free(d->path_split[i]);
				clean_exit(d, "couldn't malloc in ft_strjoin", NULL, E_ALLOC);
			}
			free(temp);
		}
	}
}
