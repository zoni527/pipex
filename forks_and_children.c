/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_and_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:43:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 09:45:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_forks(t_ppx *data)
{
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		perror_clean_exit(data, "pipex", E_FORK);
	if (data->pid[0] == 0)
		first_child(data);
	data->pid[1] = fork();
	if (data->pid[1] < 0)
		perror_clean_exit(data, "pipex", E_FORK);
	if (data->pid[1] == 0)
		last_child(data);
}

/**
 * Read from the infile in the first process, redirect output to the pipe,
 * attempt to run binary, check for errors, close all extra fds
 */
void	first_child(t_ppx *d)
{
	close_pipe_read_end(d);
	check_infile(d);
	open_infile(d);
	redirect_stdin_and_close_fd(d, d->file_fd);
	redirect_stdout_and_close_fd(d, d->pipe_fds[WRITE]);
	check_bin(d, 0);
	execve(d->bin[0][0], d->bin[0], d->envp);
	clean_exit(d, "command not found: ", d->argv[2], E_NOTFOUND);
}

/**
 * Close write end of pipe (second child writes to outfile), attempt to open
 * outfile, if this fails clean and exit, notify of permission error.
 * Redirection of stdout to outfile, close file descriptor after redirection.
 * Redirect stdin to read end of pipe, close pipe end after redirection.
 * Try to verify if binary exists, if exists check if it has execute
 * permissions.
 */
void	last_child(t_ppx *d)
{
	close_pipe_write_end(d);
	check_outfile(d);
	open_outfile(d);
	redirect_stdout_and_close_fd(d, d->file_fd);
	redirect_stdin_and_close_fd(d, d->pipe_fds[READ]);
	check_bin(d, 1);
	execve(d->bin[1][0], d->bin[1], d->envp);
	clean_exit(d, "command not found: ", d->argv[3], E_NOTFOUND);
}
