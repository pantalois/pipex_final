/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:50:34 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/30 17:27:02 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

void	ft_execute(char *env[], char *argv[], char **cmd, char *path, char **split_res)
{
	int	i;

	fprintf(stderr, "%s\n", cmd[0]);
	i = 0;
	//(void)split_res;
	if (argv[i + 2] == NULL && cmd != NULL)
	{
		fprintf(stderr, "%s\n", path);
		if (execve(path, cmd, env) == -1)
		{
			//write(2, "aqui\n", 5);
			free_paths(cmd);
			free_paths(split_res);
			//free(split_res);
			print_fail("command not found: ", 0, 127, argv[i]);
		}
	}
	else if (cmd != NULL)
	{
		fprintf(stderr, "%s\n", path);
		if (execve(path, cmd, env) == -1)
		{
			free_paths(cmd);
			free_paths(split_res);
			print_fail("command not found: ", 0, 0, argv[i]);
		}
	}
}

void	ft_output(char *argv[], char *cmd[], char **split_res, char *path)
{
	int	fd_o;
	int	i;

	i = 0;
	(void)path;
	fd_o = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_o < 0)
	{
		free_paths(cmd);
		/*if (path)
		{
			free(path);
			path = NULL;
		}*/
		if (split_res)
		{
			free_paths(split_res);
			split_res = NULL;
		}
		print_fail("Error opening output file", 0, 1, NULL);
	}
	if (dup2(fd_o, STDOUT_FILENO) == -1)
		perror("failed redirecting strdout");
}

int	check_status(char *argv[], int argc, int status)
{
	int	k;

	k = 0;
	while (k < argc - 2)
	{
		//write (2, "hola\n", 5);
		wait(&status);
		//fprintf(stderr, "%d \n", status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
		//	write(2, "uno\n", 4);
			if (argv[argc - 2])
			{
		//		write(2, "dos\n", 4);
				return (127);
			}
		}
		else
			k++;
	}
	return (0);
}

//Error opening output file cambiar mensaje de error
