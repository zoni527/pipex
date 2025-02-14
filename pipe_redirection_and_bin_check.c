/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection_and_bin_check.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:48:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 10:21:43 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_write_end(t_ppx *d)
{
	if (close(d->pipe_fds[WRITE]))
		perror_clean_exit(d, "pipex", E_CLOSE);
}

void	close_pipe_read_end(t_ppx *d)
{
	if (close(d->pipe_fds[READ]))
		perror_clean_exit(d, "pipex", E_CLOSE);
}

void	redirect_stdout_and_close_fd(t_ppx *d, int fd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(fd))
		perror_clean_exit(d, "pipex", E_CLOSE);
}

void	redirect_stdin_and_close_fd(t_ppx *d, int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(fd))
		perror_clean_exit(d, "pipex", E_CLOSE);
}

void	check_bin(t_ppx *d, int index)
{
	int	fd;

	if (!ft_strchr(d->bin[index][0], '/'))
		clean_exit(d, "command not found: ", d->argv[index + 2], E_NOTFOUND);
	if (access(d->bin[index][0], F_OK))
		clean_exit(d, "no such file or directory: ",
			d->bin[index][0], E_NOTFOUND);
	if (access(d->bin[index][0], X_OK))
		clean_exit(d, "permission denied: ", d->argv[index + 2], E_PERMISSION);
	fd = open(d->bin[index][0], O_DIRECTORY);
	if (fd != -1)
	{
		if (close(fd))
			clean_exit(d, "close failed in check_bin", NULL, E_CLOSE);
		clean_exit(d, "permission denied: ", d->argv[index + 2], E_PERMISSION);
	}
}
