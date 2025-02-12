/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:30:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/29 13:31:55 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	static t_ppx	data;

	if (argc != 5)
		return (write_error_return_int(
				"Example use: ./pipex <file1> <cmd1> <cmd2> <file2>", 0));
	validate_input(argv);
	setup_data(&data, argc, argv, envp);
	handle_forks(&data);
	cleanup_data(&data);
	waitpid(data.pid[0], &data.wait_status[0], 0);
	waitpid(data.pid[1], &data.wait_status[1], 0);
	if (data.wait_status[1] == 32512)
		return (E_NOTFOUND);
	if (data.wait_status[1] == 256)
		return (E_PERMISSION);
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
 * Initialises data values, parses and assigns both the PATH and the binaries
 * to be run, opens the pipes to be used
 */
void	setup_data(t_ppx *data, int argc, char *argv[], char *envp[])
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	prepare_path(data);
	prepare_bins(data);
	if (pipe(data->pipe_fds))
		perror_clean_exit(data, "pipex", E_PIPE);
}

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

void	cleanup_data(t_ppx *data)
{
	close_fds(data);
	free_split(&data->path_split);
	free_split(&data->bin[0]);
	free_split(&data->bin[1]);
}

void	close_fds(t_ppx *data)
{
	if (data->file_fd > 2)
		close(data->file_fd);
	if (data->pipe_fds[READ] > 2)
		close(data->pipe_fds[0]);
	if (data->pipe_fds[WRITE] > 2)
		close(data->pipe_fds[1]);
}

void	perror_clean_exit(t_ppx *data, const char *msg, int exit_code)
{
	perror(msg);
	cleanup_data(data);
	exit(exit_code);
}

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

/**
 * Looks for path variable, splits path into parts and appends '/' when 
 * necessary to make joining with binary names easier later
 */
void	prepare_path(t_ppx *d)
{
	int		i;

	i = -1;
	while (d->envp[++i])
		if (ft_strnstr(d->envp[i], "PATH=", ft_strlen("PATH=")) == d->envp[i])
		{
			d->path = ft_strchr(d->envp[i], '=') + 1;
			break ;
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
				clean_exit(d, "couldn't malloc in ft_strjoin", NULL, E_ALLOC);
			free(temp);
		}
	}
}

void	check_infile(t_ppx *d)
{
	if (access(d->argv[1], F_OK))
		clean_exit(d, "no such file or directory: ", d->argv[1], E_PERMISSION);
	if (access(d->argv[1], R_OK))
		clean_exit(d, "permission_denied: ", d->argv[1], E_PERMISSION);
}

void	open_infile(t_ppx *d)
{
	d->file_fd = open(d->argv[1], O_RDONLY);
	if (d->file_fd == -1)
	{
		if (errno == EISDIR)
			clean_exit(d, "is a directory: ", d->argv[1], E_PERMISSION);
		else
			clean_exit(d, "failed to open file: ", d->argv[1], E_OPEN);
	}
}

void	check_bin(t_ppx *d, int index)
{
	if (access(d->bin[index][0], F_OK))
		clean_exit(d, "command not found: ", d->argv[index + 2], E_NOTFOUND);
	if (access(d->bin[index][0], X_OK))
		clean_exit(d, "permission denied: ", d->argv[index + 2], E_PERMISSION);
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

void	check_outfile(t_ppx *d)
{
	if (!d->argv[4][0])
			clean_exit(d, "no such file or directory: ", d->argv[4], E_PERMISSION);
	if (access(d->argv[4], F_OK) == 0)
	{
		if (access(d->argv[4], W_OK))
			clean_exit(d, "permission denied: ", d->argv[4], E_PERMISSION);
	}
}

void	open_outfile(t_ppx *d)
{
	d->file_fd = open(d->argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (d->file_fd == -1)
	{
		if (errno == EISDIR)
			clean_exit(d, "is a directory: ", d->argv[4], E_PERMISSION);
		else
			clean_exit(d, "failed to open file: ", d->argv[4], E_OPEN);
	}
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
