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
#include <fcntl.h>
#include <unistd.h>

void	close_fds(t_ppx *data);
void	cleanup_data(t_ppx *data);
void	clean_perror_exit(t_ppx *data, const char *msg, int exit_code);
void	assign_bin(t_ppx *data, int index, const char *bin_name);

void	cleanup_data(t_ppx *data)
{
	free_split(&data->path_split);
	free_split(&data->bin[0]);
	free_split(&data->bin[1]);
	close_fds(data);
}

void	close_fds(t_ppx *data)
{
	close(data->file_fd);
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);
}

void	clean_perror_exit(t_ppx *data, const char *msg, int exit_code)
{
	cleanup_data(data);
	perror(msg);
	exit(exit_code);
}

/**
 * Attempts to find correct binary path and assign it
 */ 
void	assign_bin(t_ppx *data, int index, const char *bin_name)
{
	char	*bin;
	int		i;

	data->bin[index] = ft_split(bin_name, ' ');
	if (!data->bin[index])
		clean_perror_exit(data, "pipex: assign_bin: ft_split", E_MALLOC);
	i = -1;
	while (data->path_split[++i])
	{
		bin = ft_strjoin(data->path_split[i], data->bin[index][0]);
		if (!bin)
			clean_perror_exit(data, "pipex: assign_bin: ft_strjoin", E_MALLOC);
		if (access(bin, F_OK) == 0)
		{
			free(data->bin[index][0]);
			data->bin[index][0] = bin;
			return ;
		}
		free(bin);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	static t_ppx	data;
	char			*temp;
	int				i;

	// Correct amount of args
	if (argc != 5)
		return(write_error_return_int(
			"Example use: ./pipex <file1> <cmd1> <cmd2> <file2>", 0));

	// Initialization
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;

	// Look for PATH in envp and assign to data
	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", ft_strlen("PATH=")) == envp[i])
			data.path = ft_strchr(envp[i], '=') + 1;

	// Split PATH into parts
	data.path_split = ft_split(data.path, ':');
	if (!data.path_split)
		clean_perror_exit(&data, "ft_split: ", E_MALLOC);

	// Append '/' to paths when necessary to make it easier to join for
	// searching if a binary exists
	i = -1;
	while (data.path_split[++i])
	{
		if (data.path_split[i][ft_strlen(data.path_split[i]) - 1] != '/')
		{
			temp = data.path_split[i];
			data.path_split[i] = ft_strjoin(data.path_split[i], "/");
			if (!data.path_split[i])
				clean_perror_exit(&data, "ft_strjoin: ", E_MALLOC);
			free(temp);
		}
	}

	assign_bin(&data, 0, argv[2]);
	assign_bin(&data, 1, argv[3]);
	ft_putendl(data.bin[0][0]);
	ft_putendl(data.bin[1][0]);

	// Create pipe
	if (pipe(data.pipe_fds))
		clean_perror_exit(&data, "pipex: main", E_PIPE);

	// Fork two processes, one for each binary
	data.pid[0] = fork();
	if (data.pid[0] < 0)
		clean_perror_exit(&data, "pipex: main", E_FORK);

	// Read from the infile in the first process, redirect output to the pipe,
	// attempt to run binary, check for errors, close all extra fds
	if (data.pid[0] == 0)
	{
		if (close(data.pipe_fds[0]))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		data.file_fd = open(argv[1], O_RDONLY);
		if (data.file_fd == -1)
			clean_perror_exit(&data, "pipex", E_OPEN);
		if (dup2(data.file_fd, STDIN_FILENO) < 0)
			clean_perror_exit(&data, "pipex", E_DUP2);
		if (close(data.file_fd))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		if (dup2(data.pipe_fds[1], STDOUT_FILENO) < 0)
			clean_perror_exit(&data, "pipex", E_DUP2);
		if (close(data.pipe_fds[1]))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		execve(data.bin[0][0], data.bin[0], data.envp);
		clean_perror_exit(&data, "pipex", E_EXEC);
	}
	data.pid[1] = fork();
	if (data.pid[0] < 0)
		write_error_return_int("pipex: error forking", E_FORK);

	// Read from pipe in second process, redirect standard output to outfile,
	// attempt to run binary, check for errors, close all extra fds
	if (data.pid[1] == 0)
	{
		if (close(data.pipe_fds[1]))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		data.file_fd = open(argv[4], O_WRONLY);
		if (data.file_fd == -1)
			clean_perror_exit(&data, "pipex", E_OPEN);
		if (dup2(data.pipe_fds[0], STDIN_FILENO) < 0)
			write_error_return_int("pipex", E_DUP2);
		if (dup2(data.file_fd, STDOUT_FILENO) < 0)
			write_error_return_int("pipex", E_DUP2);
		if (close(data.file_fd))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		if (close(data.pipe_fds[0]))
			clean_perror_exit(&data, "pipex", E_CLOSE);
		execve(data.bin[1][0], data.bin[1], data.envp);
		clean_perror_exit(&data, "pipex", E_EXEC);
	}
	close_fds(&data);
	cleanup_data(&data);
	waitpid(data.pid[0], &data.wait_status[0], 0);
	waitpid(data.pid[1], &data.wait_status[1], 0);
	return (0);
}
