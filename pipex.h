/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:04:45 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/08 17:19:16 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define E_FILEPERM		1
# define E_BINPERM		126
# define E_NOTFOUND		127

# define E_PIPE			2
# define E_FORK			3
# define E_DUP2			4
# define E_OPEN			5
# define E_CLOSE		6
# define E_EXEC			7
# define E_ALLOC		8
# define E_ACCESS		9
# define E_NOPATH		10
# define E_INPUT		11
# define E_UNLINK		12

# define M_ARGS			"Example use: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define M_QUOTES		"pipex: invalid amount of quotes in input"
# define M_NOPATH		"couldn't find PATH"

# define M_ALLOC_SPLIT	"couldn't alloc in ft_split"
# define M_ALLOC_JOIN	"couldn't alloc in ft_strjoin"
# define M_ALLOC_TRIM	"couldn't alloc in ft_strtrim"
# define M_ALLOC_DUP	"couldn't alloc in ft_strdup"
# define M_ALLOC_ABIN	"couldn't alloc in assign_bin"

# define M_NOSUCH		"no such file or directory: "
# define M_PERM			"permission denied: "
# define M_ISDIR		"is a directory: "
# define M_OPEN			"failed to open file: "
# define M_NOTFOUND		"command not found: "

# define M_PIPEX		"pipex"

# define READ	0
# define WRITE	1

# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_ppx
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*path;
	char	**path_split;
	char	**bin[2];
	char	*args[2];
	int		wait_status;
	pid_t	pid[2];
	int		file_fd;
	int		pipe_fds[2];
}	t_ppx;

// pipex.c ---------------------------------------------------------------------
int		main(int argc, char *argv[], char *envp[]);
void	validate_input(char *argv[]);
void	prepare_path(t_ppx *d);
void	append_slash_to_paths(t_ppx *d);
// data_setup_cleanup_and_errors.c ---------------------------------------------
void	setup_data(t_ppx *data, int argc, char *argv[], char *envp[]);
void	cleanup_data(t_ppx *data);
void	close_fds(t_ppx *data);
void	perror_clean_exit(t_ppx *data, const char *msg, int exit_code);
void	clean_exit(t_ppx *d, const char *msg, const char *file, int exit_code);
// prepare_bins.c --------------------------------------------------------------
void	prepare_bins(t_ppx *data);
void	assign_bin(t_ppx *data, int index, char *bin_name);
void	search_for_bin(t_ppx *data, int index, char *bin_name);
// prepare_bins_utils.c --------------------------------------------------------
void	replace_space_within_single_quotes_with_del(char *str);
void	trim_single_quotes(t_ppx *data, char *arr[], char *str);
void	replace_del_with_space(char *arr[]);
// forks_and_children.c --------------------------------------------------------
void	handle_forks(t_ppx *data);
void	first_child(t_ppx *d);
void	last_child(t_ppx *d);
// infile_and_outfile.c --------------------------------------------------------
void	check_infile(t_ppx *d);
void	open_infile(t_ppx *d);
void	check_outfile(t_ppx *d);
void	open_outfile(t_ppx *d);
// pipe_redirection_and_bin_check.c --------------------------------------------
void	close_pipe_write_end(t_ppx *d);
void	close_pipe_read_end(t_ppx *d);
void	redirect_stdout_and_close_fd(t_ppx *d, int fd);
void	redirect_stdin_and_close_fd(t_ppx *d, int fd);
void	check_bin(t_ppx *d, int index);
//------------------------------------------------------------------------------
#endif
