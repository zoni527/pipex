/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_and_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:45:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/02/13 10:03:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_infile(t_ppx *d)
{
	if (access(d->infile, F_OK))
		clean_exit(d, M_NOSUCH, d->infile, E_FILEPERM);
	if (access(d->infile, R_OK))
		clean_exit(d, M_PERM, d->infile, E_FILEPERM);
}

void	open_infile(t_ppx *d)
{
	d->file_fd = open(d->infile, O_RDONLY);
	if (d->file_fd == -1)
	{
		if (errno == EISDIR)
			clean_exit(d, M_ISDIR, d->infile, E_FILEPERM);
		else
			clean_exit(d, M_OPEN, d->infile, E_OPEN);
	}
}

void	check_outfile(t_ppx *d)
{
	if (!d->outfile[0])
		clean_exit(d, M_NOSUCH, d->outfile, E_FILEPERM);
	if (access(d->outfile, F_OK) == 0)
	{
		if (access(d->outfile, W_OK))
			clean_exit(d, M_PERM, d->outfile, E_FILEPERM);
	}
}

void	open_outfile(t_ppx *d)
{
	d->file_fd = open(d->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (d->file_fd == -1)
	{
		if (errno == EISDIR)
			clean_exit(d, M_ISDIR, d->outfile, E_FILEPERM);
		else
			clean_exit(d, M_OPEN, d->outfile, E_OPEN);
	}
}
