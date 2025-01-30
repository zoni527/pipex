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

#include "libft/libft.h"
#include <stdio.h>

extern char	**environ;

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	*pids;
	char	**str_arr;

	if (argc != 5)
	{
		ft_putstr("Example use: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (0);
	}
	str_arr = envp;
	while (*str_arr)
		ft_printf("%s\n", *(str_arr++));
	ft_putstr("\n");
	str_arr = environ;
	while (*str_arr)
		ft_printf("%s\n", *(str_arr++));
	if (access(argv[1], F_OK))
		perror("ERROR");
	if (access(argv[4], F_OK))
		perror("ERROR");
	if (access(argv[1], R_OK))
		perror("ERROR");
	if (access(argv[4], R_OK))
		perror("ERROR");
	if (access(argv[1], W_OK))
		perror("ERROR");
	if (access(argv[4], W_OK))
		perror("ERROR");
	exit(EXIT_SUCCESS);
	return (0);
}
