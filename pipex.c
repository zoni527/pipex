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

void	close_fds(t_ppx *data);
void	cleanup_data(t_ppx *data);
void	perror_clean_exit(t_ppx *data, const char *msg, int exit_code);
void	assign_bin(t_ppx *data, int index, const char *bin_name);

void	append_slash_to_paths(t_ppx *d);

void	cleanup_data(t_ppx *data)
{
	free_split(&data->path_split);
	free_split(&data->bin[0]);
	free_split(&data->bin[1]);
	close_fds(data);
}

void	close_fds(t_ppx *data)
{
	if (data->file_fd > 2)
		close(data->file_fd);
	if (data->pipe_fds[0] > 2)
		close(data->pipe_fds[0]);
	if (data->pipe_fds[1] > 2)
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
 * Splits binary into binary name and arguments, attempts to look for binary
 * in PATH, if not found leaves binary name as is.
 * If binary exists in the current directory or name already contains the path
 * to a valid binary don't search PATH.
 */
void	assign_bin(t_ppx *data, int index, const char *bin_name)
{
	char	*bin;
	int		i;

	data->bin[index] = ft_split(bin_name, ' ');
	if (!data->bin[index])
		clean_exit(data, "couldn't malloc in split", NULL, E_MALLOC);
	if (access(data->bin[index][0], F_OK | X_OK) == 0)
		return ;
	i = -1;
	while (data->path_split[++i])
	{
		bin = ft_strjoin(data->path_split[i], data->bin[index][0]);
		if (!bin)
			clean_exit(data, "couldn't malloc in ft_strjoin", NULL, E_MALLOC);
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
 * Look for path variable, split path into parts and append '/' when necessary
 * to make joining with binary names easier later
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
		clean_exit(d, "couldn't malloc in ft_split", NULL, E_MALLOC);
	append_slash_to_paths(d);
}

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
				clean_exit(d, "couldn't malloc in ft_strjoin", NULL, E_MALLOC);
			free(temp);
		}
	}
}

/**
 * Read from the infile in the first process, redirect output to the pipe,
 * attempt to run binary, check for errors, close all extra fds
 */
void	first_child(t_ppx *d)
{
	if (close(d->pipe_fds[0]))
		perror_clean_exit(d, "pipex", E_CLOSE);
	if (access(d->argv[1], F_OK))
		clean_exit(d, "no such file or directory: ", d->argv[1], E_PERMISSION);
	if (access(d->argv[1], R_OK))
		clean_exit(d, "permission_denied: ", d->argv[1], E_PERMISSION);
	d->file_fd = open(d->argv[1], O_RDONLY);
	if (d->file_fd == -1)
		perror_clean_exit(d, "pipex", E_OPEN);
	if (dup2(d->file_fd, STDIN_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(d->file_fd))
		perror_clean_exit(d, "pipex", E_CLOSE);
	if (dup2(d->pipe_fds[1], STDOUT_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(d->pipe_fds[1]))
		perror_clean_exit(d, "pipex", E_CLOSE);
	if (access(d->bin[0][0], F_OK))
		clean_exit(d, "command not found: ", d->argv[2], E_NOTFOUND);
	if (access(d->bin[0][0], X_OK))
		clean_exit(d, "permission denied: ", d->argv[2], E_PERMISSION);
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
	if (close(d->pipe_fds[1]))
		perror_clean_exit(d, "pipex", E_CLOSE);
	d->file_fd = open(d->argv[4], O_CREAT | O_WRONLY, 0777);
	if (d->file_fd == -1)
		clean_exit(d, "permission denied: ", d->argv[4], E_PERMISSION);
	if (dup2(d->file_fd, STDOUT_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(d->file_fd))
		perror_clean_exit(d, "pipex", E_CLOSE);
	if (dup2(d->pipe_fds[0], STDIN_FILENO) < 0)
		perror_clean_exit(d, "pipex", E_DUP2);
	if (close(d->pipe_fds[0]))
		perror_clean_exit(d, "pipex", E_CLOSE);
	if (access(d->bin[1][0], F_OK))
		clean_exit(d, "command not found: ", d->argv[3], E_NOTFOUND);
	if (access(d->bin[1][0], X_OK))
		clean_exit(d, "permission denied: ", d->argv[3], E_PERMISSION);
	execve(d->bin[1][0], d->bin[1], d->envp);
	clean_exit(d, "command not found: ", d->argv[3], E_NOTFOUND);
}

void	setup_data(t_ppx *data, int argc, char *argv[], char *envp[])
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	prepare_path(data);
	assign_bin(data, 0, argv[2]);
	assign_bin(data, 1, argv[3]);
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

int	main(int argc, char *argv[], char *envp[])
{
	static t_ppx	data;

	if (argc != 5)
		return (write_error_return_int(
				"Example use: ./pipex <file1> <cmd1> <cmd2> <file2>", 0));
	setup_data(&data, argc, argv, envp);
	handle_forks(&data);
	close_fds(&data);
	cleanup_data(&data);
	waitpid(data.pid[0], &data.wait_status[0], 0);
	waitpid(data.pid[1], &data.wait_status[1], 0);
	return (0);
}
