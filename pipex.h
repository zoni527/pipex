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

# define E_PIPE		1
# define E_FORK		2
# define E_DUP2		3
# define E_OPEN		4
# define E_CLOSE	5
# define E_EXEC		6
# define E_MALLOC	7
# define E_ACCESS	8

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
	int		wait_status[2];
	pid_t	pid[2];
	int		file_fd;
	int		pipe_fds[2];
}	t_ppx;
#endif
