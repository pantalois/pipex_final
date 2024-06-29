/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:50:34 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/29 18:10:45 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

void	ft_execute(char *env[], char *argv[], char **cmd, char *path)
{
	int	i;

	i = 0;
	if (argv[i + 2] == NULL && cmd != NULL)
	{
		if (execve(path, cmd, env) == -1)
		{
			write(2, "hola", 4);
			free_paths(cmd);
			print_fail("command not found: ", 0, 127, argv[i]);
		}
	}
	else if (cmd != NULL)
	{
		if (execve(path, cmd, env) == -1)
		{
			free_paths(cmd);
			print_fail("command not found: ", 0, 0, argv[i]);
		}
	}
}

void	ft_output(char *argv[])
{
	int	fd_o;
	int	i;

	i = 0;
	fd_o = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_o < 0)
		print_fail("Error opening output file\n", 0, 1, NULL);
	if (dup2(fd_o, STDOUT_FILENO) == -1)
		perror("failed redirecting strdout");
}
