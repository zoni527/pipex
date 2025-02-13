/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_setup_cleanup_and_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:34:19 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 09:42:54 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Initialises data values, parses and assigns both the PATH and the binaries
 * to be run, opens the pipes to be used
 */
void	setup_data(t_ppx *data, int argc, char *argv[], char *envp[])
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	prepare_path(data);
	prepare_bins(data);
	if (pipe(data->pipe_fds))
		perror_clean_exit(data, "pipex", E_PIPE);
}

void	cleanup_data(t_ppx *data)
{
	close_fds(data);
	free_split(&data->path_split);
	free_split(&data->bin[0]);
	free_split(&data->bin[1]);
}

/**
 * All file descriptors get initialized to zero initially as the data is
 * a static struct, thus if a descriptor gets assigned a file descriptor
 * it should be over 2 as 0 1 and 2 are reserved for stdin, stdout and
 * stderr respectively
 */
void	close_fds(t_ppx *data)
{
	if (data->file_fd > 2)
		close(data->file_fd);
	if (data->pipe_fds[READ] > 2)
		close(data->pipe_fds[0]);
	if (data->pipe_fds[WRITE] > 2)
		close(data->pipe_fds[1]);
}

/**
 * Important to perror first, unsuccesful attempts at data cleanup or closing
 * file descriptors can corrupt errno
 */
void	perror_clean_exit(t_ppx *data, const char *msg, int exit_code)
{
	perror(msg);
	cleanup_data(data);
	exit(exit_code);
}

/**
 * Alternative to perrno, can log both an error and a specifier what file or
 * executable the error is related to
 */
void	clean_exit(t_ppx *d, const char *msg, const char *file, int exit_code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (file)
		ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	cleanup_data(d);
	exit(exit_code);
}
