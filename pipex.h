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

# define E_PERMISSION	1
# define E_PIPE			2
# define E_FORK			3
# define E_DUP2			4
# define E_OPEN			5
# define E_CLOSE		6
# define E_EXEC			7
# define E_MALLOC		8
# define E_ACCESS		9
# define E_NOPATH		10
# define E_NOTFOUND		127

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
